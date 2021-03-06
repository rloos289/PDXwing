<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
<div class="profile"<?php print $attributes; ?>>
  <div class="avatar col-md-4">
    <?php
    print render($user_profile['user_picture']);
    ?>
  </div>
  <div class="col-md-8">
    <div class="profile_info">
      <?php
      print render($user_profile['field_preferred_faction']);
      print render($user_profile['field_favorite_ship']);
      print render($user_profile['field_favorite_pilot']);
       ?>
    </div>
    <div class="ships_builds">
      <div class="col-md-6 ships">
        <?php
        print render($user_profile['field_ships']);
        ?>
      </div>
      <div class="col-md-6 builds">
        <?php
        print render($user_profile['field_builds_paragraph_']);
        ?>
      </div>
    </div>
  </div>
</div>
