<?php

/**
 * @file
 * This file contains the seed helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Seed form functions
 */
function bracket_seed_edit($node) {

  return drupal_get_form('bracket_seed_edit_form', $node);
}

function bracket_seed_edit_form($form, $form_state, $node) {

  drupal_set_title(t('Seeding') . ' - ' . check_plain($node->title));

  $form = array();

  // save the nodeid
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid
  );

  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => t('Use this form to assign competitors and seeds to bracket slots.
                   This is actually just a trimmed down version of the Round 1 form.
                   Seeds are used for importing competitors - they are optional and do not appear on the bracket.')
  );

  for ($i=1; $i<=count($node->comp); $i+=2) {

    $m = bracket_seed_get_match($node, $i, $i+1);

    // generate match fieldset
    $match = 'match' . $m->id;

    $form[$match] = array(
      '#type' => 'fieldset',
      '#title' => '<strong>' . t('Match') . ' #' . $m->id . '</strong>',
      '#tree' => FALSE
    );

    $c = $node->comp[$i];

    $form[$match]['comp' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #1',
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $c->name,
    );

    $form[$match]['seed' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #1' . ' ' . t('Seed'),
      '#size' => 10,
      '#maxlength' => 50,
      '#default_value' => $c->seedin,
    );

    $c = $node->comp[$i+1];

    $form[$match]['comp' . ($i+1)] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #2',
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $c->name,
    );

    $form[$match]['seed' . ($i+1)] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #2' . ' ' . t('Seed'),
      '#size' => 10,
      '#maxlength' => 50,
      '#default_value' => $c->seedin,
    );

  }   // end - for ($i=1; $i<=count($r->match); $i++)...

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

// return match with given competitors
function bracket_seed_get_match($node, $compid1, $compid2) {

  // only look at winner rounds
  for ($i=1; $i<=bracket_round_last_winner_round($node); $i++) {
    $r = $node->round[$i];
    // look at all matches
    for ($j=1; $j<=count($r->match); $j++) {
      $m = $r->match[$j];
      // return match if competitors match
      if ($m->compid[1] == $compid1 && $m->compid[2] == $compid2)
        return $m;
    }
  }

  return NULL;
}

function bracket_seed_edit_form_submit($form_id, &$form_state) {

  $nid = $form_state['values']['nid'];
  $node = node_load($nid);

  for ($i=1; $i<=count($node->comp); $i++) {

    $c = $node->comp[$i];

    $c->name = $form_state['values']['comp' . $i];
    $c->seedin = $form_state['values']['seed' . $i];
  }

  node_save($node);
  drupal_set_message(t('Bracket has been updated'));
}