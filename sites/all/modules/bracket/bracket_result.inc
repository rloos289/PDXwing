<?php

/**
 * @file
 * This file contains the result helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Results form functions
 */
function bracket_result_edit($node) {

  return drupal_get_form('bracket_result_edit_form', $node);
}

function bracket_result_edit_form($form, $form_state, $node) {

  drupal_set_title(t('Results') . ' - ' . check_plain($node->title));
  
  $form = array();

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid
  );

  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => t('Use this form to view the bracket results and update comments that appear on the bracket for top placers.
                   Seeds are used for exporting competitors into the next bracket - they are optional and do not appear on the bracket.')
  );

  for ($i=1; $i<=count($node->result); $i++) {

    $s = $node->result[$i];

    // generate match fieldset
    $result = 'result' . $i;

    $form[$result] = array(
      '#type' => 'fieldset',
      '#title' => '<strong>' . t('Place') . ' #' . $i . '</strong>',
      '#tree' => TRUE
    );

    // competitor
    $form[$result]['comp'] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor'),
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $s->cname,
      '#attributes' => array('readonly' => 'readonly'),
    );

    $form[$result]['hr'] = array(
      '#type' => 'markup',
      '#markup' => '<hr />',
    );

    $form[$result]['comment'] = array(
      '#type' => 'textfield',
      '#title' => t('Comment'),
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $s->comment,
    );

    $form[$result]['seedout'] = array(
      '#type' => 'textfield',
      '#title' => t('Seed'),
      '#size' => 10,
      '#maxlength' => 50,
      '#default_value' => $s->seedout,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function bracket_result_edit_form_submit($form_id, &$form_state) {

  // get id's
  $nid = $form_state['values']['nid'];

  // load the node
  $node = node_load($nid);

  // update all matches in the round
  for ($i=1; $i<=count($node->result); $i++) {

    $result = 'result' . $i;

    $s = $node->result[$i];

    // update result info
    $s->comment = $form_state['values'][$result]['comment'];
    $s->seedout = $form_state['values'][$result]['seedout'];
  }

  // save the node
  node_save($node);
  drupal_set_message(t('Bracket has been updated'));
}

