<?php
/**
 * @file
 * new_user.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function new_user_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_collection'.
  $field_bases['field_collection'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_collection',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'X-wing Core Set' => 'X-wing Core Set',
        'Force Awakens Core Set' => 'Force Awakens Core Set',
        '<span class="rebel">X-wing</span>' => '<span class="rebel">X-wing</span>',
        '<span class="rebel">Y-wing</span>' => '<span class="rebel">Y-wing</span>',
        '<span class="rebel">Millenium Falcon</span>' => '<span class="rebel">Millenium Falcon</span>',
        '<span class="rebel">A-wing</span>' => '<span class="rebel">A-wing</span>',
        '<span class="rebel">HWK-290</span>' => '<span class="rebel">HWK-290</span>',
        '<span class="rebel">B-Wing</span>' => '<span class="rebel">B-Wing</span>',
        '<span class="rebel">Rebel Transport</span>' => '<span class="rebel">Rebel Transport</span>',
        '<span class="rebel">Tantive IV</span>' => '<span class="rebel">Tantive IV</span>',
        '<span class="rebel">Z-95 Headhunter</span>' => '<span class="rebel">Z-95 Headhunter</span>',
        '<span class="rebel">E-wing</span>' => '<span class="rebel">E-wing</span>',
        '<span class="rebel">Rebel Aces</span>' => '<span class="rebel">Rebel Aces</span>',
        '<span class="rebel">YT-2400</span>' => '<span class="rebel">YT-2400</span>',
        '<span class="rebel">K-wing</span>' => '<span class="rebel">K-wing</span>',
        '<span class="rebel">T-70 X-Wing</span>' => '<span class="rebel">T-70 X-Wing</span>',
        '<span class="rebel">Ghost</span>' => '<span class="rebel">Ghost</span>',
        '<span class="rebel">Heroes of the Resistance</span>' => '<span class="rebel">Heroes of the Resistance</span>',
        '<span class="rebel">Arc-170</span>' => '<span class="rebel">Arc-170</span>',
        '<span class="rebel">Sabine\'s TIE Fighter</span>' => '<span class="rebel">Sabine\'s TIE Fighter</span>',
        '<span class="rebel">U-wing</span>' => '<span class="rebel">U-wing</span>',
        '<span class="empire">Tie Fighter</span>' => '<span class="empire">Tie Fighter</span>',
        '<span class="empire">Tie Advanced</span>' => '<span class="empire">Tie Advanced</span>',
        '<span class="empire">Slave I</span>' => '<span class="empire">Slave I</span>',
        '<span class="empire">Tie Interceptor</span>' => '<span class="empire">Tie Interceptor</span>',
        '<span class="empire">Lambda-Class Shuttle</span>' => '<span class="empire">Lambda-Class Shuttle</span>',
        '<span class="empire">Tie Bomber</span>' => '<span class="empire">Tie Bomber</span>',
        '<span class="empire">Imperial Aces</span>' => '<span class="empire">Imperial Aces</span>',
        '<span class="empire">Tie Defender</span>' => '<span class="empire">Tie Defender</span>',
        '<span class="empire">Tie Phantom</span>' => '<span class="empire">Tie Phantom</span>',
        '<span class="empire">VT-49 Decimator</span>' => '<span class="empire">VT-49 Decimator</span>',
        '<span class="empire">Imperial Raider</span>' => '<span class="empire">Imperial Raider</span>',
        '<span class="empire">Tie Punisher</span>' => '<span class="empire">Tie Punisher</span>',
        '<span class="empire">Imperial Assault Carrier</span>' => '<span class="empire">Imperial Assault Carrier</span>',
        '<span class="empire">Tie/fo Fighter</span>' => '<span class="empire">Tie/fo Fighter</span>',
        '<span class="empire">Inquisitor\'s Tie</span>' => '<span class="empire">Inquisitor\'s Tie</span>',
        '<span class="empire">Imperial Veterans</span>' => '<span class="empire">Imperial Veterans</span>',
        '<span class="empire">Special Forces Tie</span>' => '<span class="empire">Special Forces Tie</span>',
        '<span class="empire">Upsilon-class Shuttle</span>' => '<span class="empire">Upsilon-class Shuttle</span>',
        '<span class="empire">Tie Striker</span>' => '<span class="empire">Tie Striker</span>',
        '<span class="scum">StarViper</span>' => '<span class="scum">StarViper</span>',
        '<span class="scum">M3-A Interceptor</span>' => '<span class="scum">M3-A Interceptor</span>',
        '<span class="scum">IG-2000</span>' => '<span class="scum">IG-2000</span>',
        '<span class="scum">Most Wanted</span>' => '<span class="scum">Most Wanted</span>',
        '<span class="scum">Hound\'s Tooth</span>' => '<span class="scum">Hound\'s Tooth</span>',
        '<span class="scum">Kihraxz Fighter</span>' => '<span class="scum">Kihraxz Fighter</span>',
        '<span class="scum">Mist Hunter</span>' => '<span class="scum">Mist Hunter</span>',
        '<span class="scum">Punishing One</span>' => '<span class="scum">Punishing One</span>',
        '<span class="scum">Protectorate Starfighter</span>' => '<span class="scum">Protectorate Starfighter</span>',
        '<span class="scum">Shadow Caster</span>' => '<span class="scum">Shadow Caster</span>',
        '<span class="scum">QuadJumper</span>' => '<span class="scum">QuadJumper</span>',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
