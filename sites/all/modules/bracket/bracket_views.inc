<?php

/**
 * @file
 * This file contains the functions required for views integration
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Inform views V2 module of our table
 *
 * @return
 *   views data
 */
function bracket_views_data() {

  // tables
  $data['bracket']['table']['group'] = t('Bracket');
  
  $data['bracket']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Tournament Bracket'),
    'help' => t('Tournament Brackets for organizing competitions.'),
  );

  // joins  
  $data['bracket']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  
  // fields
  $data['bracket']['nid'] = array(
    'title' => t('Bracket Node'),
    'help' => t('Bracket Node.'),
    'relationship' => array(
      'base' => 'node',
       'field' => 'nid',
       'handler' => 'views_handler_relationship',
       'label' => t('Bracket node'),
    ),
  );
  
  $data['bracket']['sport'] = array(
    'title' => t('Sport'),
    'help' => t('Sport or Activity.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['bracket']['division'] = array(
    'title' => t('Division'),
    'help' => t('Division.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['bracket']['season'] = array(
    'title' => t('Season'),
    'help' => t('Season.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['bracket']['brgroup'] = array(
    'title' => t('Group'),
    'help' => t('Group.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  return $data;
}


