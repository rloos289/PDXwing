<?php

namespace Pantheon\Terminus\Commands\Env;

use Pantheon\Terminus\Commands\TerminusCommand;
use Pantheon\Terminus\Site\SiteAwareInterface;
use Pantheon\Terminus\Site\SiteAwareTrait;

/**
 * Class CommitCommand
 * @package Pantheon\Terminus\Commands\Env
 */
class CommitCommand extends TerminusCommand implements SiteAwareInterface
{
    use SiteAwareTrait;

    /**
     * Commits code changes on the development environment.
     * Note: The environment's connection mode must be set to SFTP.
     *
     * @authorize
     *
     * @command env:commit
     *
     * @param string $site_env Site & environment in the format `site-name.env`
     * @option string $message Commit message
     *
     * @usage terminus env:commit <site>.<env>
     *   Commits code changes to <site>'s <env> environment with the default message.
     * @usage terminus env:commit <site>.<env> --message=<message>
     *   Commits code changes to <site>'s <env> environment with the message <message>.
     */
    public function commit($site_env, $options = ['message' => 'Terminus commit.'])
    {
        list(, $env) = $this->getUnfrozenSiteEnv($site_env, 'dev');

        $change_count = count((array)$env->diffstat());
        if ($change_count === 0) {
            $this->log()->warning('There is no code to commit.');
            return;
        }

        $workflow = $env->commitChanges($options['message']);
        while (!$workflow->checkProgress()) {
            // @TODO: Add Symfony progress bar to indicate that something is happening.
        }
        $this->log()->notice('Your code was committed.');
    }
}
