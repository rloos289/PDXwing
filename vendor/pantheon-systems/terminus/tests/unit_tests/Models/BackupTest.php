<?php

namespace Pantheon\Terminus\UnitTests\Models;

use Pantheon\Terminus\Collections\Workflows;
use Pantheon\Terminus\Models\Backup;
use Pantheon\Terminus\Models\Environment;
use Pantheon\Terminus\Models\Workflow;
use Pantheon\Terminus\Exceptions\TerminusException;

/**
 * Class BackupTest
 * Testing class for Pantheon\Terminus\Models\Backup
 * @package Pantheon\Terminus\UnitTests\Models
 */
class BackupTest extends ModelTestCase
{
    protected $environment;

    public function setUp()
    {
        parent::setUp();
    }

    protected function _getBackup($attr = [])
    {
        if (empty($attr['id'])) {
            $attr['id'] = 'scheduledfor_archivetype_type';
        }
        $this->workflow = $this->getMockBuilder(Workflow::class)
            ->disableOriginalConstructor()
            ->getMock();
        $this->workflows = $this->getMockBuilder(Workflows::class)
            ->disableOriginalConstructor()
            ->getMock();
        $this->environment = $this->getMockBuilder(Environment::class)
            ->disableOriginalConstructor()
            ->getMock();
        $this->environment->method('getWorkflows')->willReturn($this->workflows);

        $this->environment->site = (object)['id' => 'abc'];
        $this->environment->id = 'dev';

        $backup = new Backup((object)$attr, ['collection' => (object)['environment' => $this->environment]]);

        $backup->setConfig($this->config);
        $backup->setRequest($this->request);
        return $backup;
    }

    public function testBackupIsFinished()
    {
        $backup = $this->_getBackup(['size' => 12345, 'finish_time' => 123456]);
        $this->assertTrue($backup->backupIsFinished());

        $backup = $this->_getBackup(['size' => 12345, 'timestamp' => 123456]);
        $this->assertTrue($backup->backupIsFinished());

        $backup = $this->_getBackup(['size' => 12345]);
        $this->assertFalse($backup->backupIsFinished());

        $backup = $this->_getBackup(['finish_time' => 12345]);
        $this->assertFalse($backup->backupIsFinished());

        $backup = $this->_getBackup(['timestamp' => 12345]);
        $this->assertFalse($backup->backupIsFinished());
    }

    public function testGetBucket()
    {
        $backup = $this->_getBackup();

        $expected = 'pantheon-backups';
        $actual = $backup->getBucket();
        $this->assertEquals($expected, $actual);

        $this->configSet(['host' => 'onebox']);
        $expected = 'onebox-pantheon-backups';
        $actual = $backup->getBucket();
        $this->assertEquals($expected, $actual);
    }

    public function testGetDate()
    {
        $this->configSet(['date_format' => 'Y-m-d']);
        $expected = '2016-11-21';

        $backup = $this->_getBackup(['finish_time' => 1479742685]);
        $actual = $backup->getDate();
        $this->assertEquals($expected, $actual);


        $backup = $this->_getBackup(['timestamp' => 1479742685]);
        $actual = $backup->getDate();
        $this->assertEquals($expected, $actual);

        $backup = $this->_getBackup([]);
        $expected = 'Pending';
        $actual = $backup->getDate();
        $this->assertEquals($expected, $actual);
    }

    public function testGetInitiator()
    {
        $backup = $this->_getBackup(['folder' => 'xyz_automated']);
        $expected = 'automated';
        $actual = $backup->getInitiator();
        $this->assertEquals($expected, $actual);

        $backup = $this->_getBackup(['folder' => 'xyz_manual']);
        $expected = 'manual';
        $actual = $backup->getInitiator();
        $this->assertEquals($expected, $actual);
    }

    public function testGetSizeInMb()
    {
        $backup = $this->_getBackup(['size' => 0]);
        $expected = '0';
        $actual = $backup->getSizeInMb();
        $this->assertEquals($expected, $actual);


        $backup = $this->_getBackup(['size' => 200]);
        $expected = '0.1MB';
        $actual = $backup->getSizeInMb();
        $this->assertEquals($expected, $actual);


        $backup = $this->_getBackup(['size' => 4508876]);
        $expected = '4.3MB';
        $actual = $backup->getSizeInMb();
        $this->assertEquals($expected, $actual);
    }

    public function testGetUrl()
    {
        $expected = '**URL**';
        $this->request->expects($this->once())
            ->method('request')
            ->with(
                'sites/abc/environments/dev/backups/catalog/xyz_manual/type/s3token',
                ['method' => 'post', 'form_params' => ['method' => 'get',],]
            )
            ->willReturn(['data' => (object)['url' => $expected]]);

        $backup = $this->_getBackup(['folder' => 'xyz_manual']);
        $this->assertEquals($expected, $backup->getUrl());
    }

    public function testRestore()
    {
        $workflow = $this->getMockBuilder(Workflow::class)
            ->disableOriginalConstructor()
            ->getMock();

        $backup = $this->_getBackup(['id' => 'scheduledfor_archivetype_code', 'filename' => 'def.tgz']);

        $this->workflows->expects($this->once())
            ->method('create')
            ->with(
                'restore_code',
                [
                    'params' => [
                        'key' => "abc/dev/scheduledfor_archivetype/def.tgz",
                        'bucket' => 'pantheon-backups',
                    ]
                ]
            )
            ->willReturn($workflow);
        $this->assertEquals($workflow, $backup->restore());

        $backup = $this->_getBackup(['id' => 'scheduledfor_archivetype_files', 'filename' => 'def.tgz']);
        $this->workflows->expects($this->once())
            ->method('create')
            ->with(
                'restore_files',
                [
                    'params' => [
                        'key' => "abc/dev/scheduledfor_archivetype/def.tgz",
                        'bucket' => 'pantheon-backups',
                    ]
                ]
            )
            ->willReturn($workflow);
        $this->assertEquals($workflow, $backup->restore());

        $backup = $this->_getBackup(['id' => 'scheduledfor_archivetype_database', 'filename' => 'def.tgz']);
        $this->workflows->expects($this->once())
            ->method('create')
            ->with(
                'restore_database',
                [
                    'params' => [
                        'key' => "abc/dev/scheduledfor_archivetype/def.tgz",
                        'bucket' => 'pantheon-backups',
                    ]
                ]
            )
            ->willReturn($workflow);
        $this->assertEquals($workflow, $backup->restore());

        $backup = $this->_getBackup(['id' => 'scheduledfor_archivetype_xyz', 'filename' => 'def.tgz']);
        $this->setExpectedException(TerminusException::class, 'This backup has no archive to restore.');
        $this->assertNull($backup->restore());
    }

    public function testSerialize()
    {
        $this->configSet(['date_format' => 'Y-m-d']);
        $backup = $this->_getBackup([
            'size' => 4508876,
            'finish_time' => 1479742685,
            'folder' => 'xyz_automated',
            'filename' => 'test.tar.gz',
        ]);

        $expected = [
            'file' => 'test.tar.gz',
            'size' => '4.3MB',
            'date' => '2016-11-21',
            'initiator' => 'automated',
        ];
        $actual = $backup->serialize();
        $this->assertEquals($expected, $actual);
    }
}
