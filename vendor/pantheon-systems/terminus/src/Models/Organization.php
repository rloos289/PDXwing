<?php

namespace Pantheon\Terminus\Models;

use League\Container\ContainerAwareInterface;
use League\Container\ContainerAwareTrait;
use Pantheon\Terminus\Collections\OrganizationSiteMemberships;
use Pantheon\Terminus\Collections\OrganizationUserMemberships;
use Pantheon\Terminus\Collections\Workflows;

/**
 * Class Organization
 * @package Pantheon\Terminus\Models
 */
class Organization extends TerminusModel implements ContainerAwareInterface
{
    use ContainerAwareTrait;

    /**
     * @var OrganizationSiteMemberships
     */
    public $site_memberships;
    /**
     * @var OrganizationUserMemberships
     */
    public $user_memberships;
    /**
     * @var Workflows
     */
    public $workflows;
    /**
     * @var array
     */
    private $features;

    /**
     * Returns a specific organization feature value
     *
     * @param string $feature Feature to check
     * @return mixed|null Feature value, or null if not found
     */
    public function getFeature($feature)
    {
        if (!isset($this->features)) {
            $response = $this->request->request("organizations/{$this->id}/features");
            $this->features = (array)$response['data'];
        }
        if (isset($this->features[$feature])) {
            return $this->features[$feature];
        }
        return null;
    }

    /**
     * Get the human-readable name of the organization.
     *
     * @return string
     */
    public function getName()
    {
        return $this->get('profile')->name;
    }

    /**
     * @return OrganizationSiteMemberships
     */
    public function getSiteMemberships()
    {
        if (!$this->site_memberships) {
            $this->site_memberships = $this->getContainer()
                ->get(OrganizationSiteMemberships::class, [['organization' => $this]]);
        }
        return $this->site_memberships;
    }

    /**
     * Retrieves organization sites
     *
     * @return Site[]
     */
    public function getSites()
    {
        $site_memberships = $this->getSiteMemberships()->all();
        $sites = array_combine(
            array_map(
                function ($membership) {
                    return $membership->getSite()->id;
                },
                $site_memberships
            ),
            array_map(
                function ($membership) {
                    return $membership->getSite();
                },
                $site_memberships
            )
        );
        return $sites;
    }

    /**
     * @return OrganizationUserMemberships
     */
    public function getUserMemberships()
    {
        if (empty($this->user_memberships)) {
            $this->user_memberships = $this->getContainer()
                ->get(OrganizationUserMemberships::class, [['organization' => $this,],]);
        }
        return $this->user_memberships;
    }

    /**
     * Retrieves organization users
     *
     * @return User[]
     */
    public function getUsers()
    {
        $user_memberships = $this->getUserMemberships()->all();
        $users = array_combine(
            array_map(
                function ($membership) {
                    return $membership->getUser()->id;
                },
                $user_memberships
            ),
            array_map(
                function ($membership) {
                    return $membership->getUser();
                },
                $user_memberships
            )
        );
        return $users;
    }

    /**
     * @return Workflows
     */
    public function getWorkflows()
    {
        if (empty($this->workflows)) {
            $this->workflows = $this->getContainer()
                ->get(Workflows::class, [['organization' => $this,],]);
        }
        return $this->workflows;
    }

    /**
     * Formats the Organization object into an associative array for output
     *
     * @return array Associative array of data for output
     *         string id   The UUID of the organization
     *         string name The name of the organization
     */
    public function serialize()
    {
        return ['id' => $this->id, 'name' => $this->getName(),];
    }
}
