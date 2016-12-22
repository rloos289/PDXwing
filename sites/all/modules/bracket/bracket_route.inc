<?php

/**
 * @file
 * This file contains the route helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Route form functions
 */
function bracket_route_edit($node) {

  return drupal_get_form('bracket_route_edit_form', $node);
}

function bracket_route_edit_form($form, $form_state, $node) {

  drupal_set_title(t('Routing') . ' - ' . check_plain($node->title));

  $form = array();

  // save the nodeid
  $form['head']['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid
  );

  $form['head']['help'] = array(
    '#type' => 'markup',
    '#markup' => t('Use this form to change match ids and competitor routing through the bracket.
                   <strong>Use With Caution</strong> - in most cases this will not be necessary, especially for single-elimination brackets.
                   The form has been provided since some customization may be required for double-elimination brackets.')
  );

  // number of matches in bracket
  $last = 0;
  for ($i=1; $i<=count($node->round); $i++) {
    $last += count($node->round[$i]->match);
  }

  // generate options array of matches
  $options = array();
  $options[0] = '';
  for ($i=1; $i<=$last; $i++) {
    $options[$i] = t('Match') . ' #' . $i;
  }

  // competitor index options
  $comp_opt = array();
  $comp_opt[0] = '';
  $comp_opt[1] = 'Comp #1';
  $comp_opt[2] = 'Comp #2';

  $lrnd = bracket_round_first_loser_round($node);

  // insert the winner matches
  $wfinalrnd = bracket_round_last_winner_round($node);
  for ($i=1; $i<=$wfinalrnd; $i++) {
    bracket_route_edit_form_matches($node->round[$i], $form, $options, $comp_opt, $lrnd > 0);
  }

  // if loser matches present, insert the loser matches
  if ($lrnd > 0) {
    // insert the loser matches
    $lfinalrnd = bracket_round_last_loser_round($node);
    for ($i=$lrnd; $i<=$lfinalrnd; $i++) {
      bracket_route_edit_form_matches($node->round[$i], $form, $options, $comp_opt, FALSE);
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function bracket_route_edit_form_matches($r, &$form, $options, $comp_opt, $loserto) {

  $round = 'round' . $r->id;

  $rtype = 'winner';
  if ($r->loser) {
    $rtype = 'loser';
  }

  $form[$rtype][$round] = array(
    '#type' => 'fieldset',
    '#title' => $r->name,
    '#tree' => TRUE,
  );

  for ($i=1; $i<=count($r->match); $i++) {

    $match = 'match' . $i;
    $m = $r->match[$i];

    $form[$rtype][$round][$match]['matchid'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $m->id,
    );

    // don't attach winner/loser routing if result routing is set
    if ($m->winner_result == 0 || $m->win_use_result > 0) {

      $form[$rtype][$round][$match]['winner_match'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $m->winner_match,
      );
      $form[$rtype][$round][$match]['winner_comp'] = array(
        '#type' => 'select',
        '#options' => $comp_opt,
        '#default_value' => $m->winner_comp,
      );

      if ($loserto) {
        $form[$rtype][$round][$match]['loser_match'] = array(
          '#type' => 'select',
          '#options' => $options,
          '#default_value' => $m->loser_match,
        );
        $form[$rtype][$round][$match]['loser_comp'] = array(
          '#type' => 'select',
          '#options' => $comp_opt,
          '#default_value' => $m->loser_comp,
        );
      }   // end - if ($loserto)...
    }   // end - if ($isfinal)...

    // attach result routing, if present
    if ($m->winner_result > 0) {
      $form[$rtype][$round][$match]['winner_result'] = array(
        '#type' => 'markup',
        '#markup' => t('Winner Result: ') . $m->winner_result
      );
    }

    if ($m->loser_result > 0) {
      $form[$rtype][$round][$match]['loser_result'] = array(
        '#type' => 'markup',
        '#markup' => t('Loser Result: ') . $m->loser_result
      );
    }

    if ($m->win_use_result > 0) {
      $form[$rtype][$round][$match]['win_use_result'] = array(
        '#type' => 'markup',
        '#markup' => t('Win Use Result: ') . $m->win_use_result
      );
      $form[$rtype][$round][$match]['win_use_result_comment'] = array(
        '#type' => 'markup',
        '#markup' => t(' (If this competitor wins, result is used, not match routing - no next match)')
      );
    }

  }   // end - for($i=1; $i<=count($r->match); $i++)...
  
}

function theme_bracket_route_edit_form($variables) {

  $form = $variables['form'];

  $output = drupal_render($form['head']);

  $wr = element_children($form['winner']);
  if (isset($form['loser'])) {
    $lr = element_children($form['loser']);
  }
  else {
    $lr = array();
  }

  // if loser matches, generate header for winner matches
  if (count($lr) > 0) {
    $output .= '<p><h2>' . t('Winner Matches') . '</h2></p>';
  }

  $output .= "<!--winner_table_begin-->\n<table><tr>";

  $rtype = 'winner';

  foreach ($wr as $round) {

    $table = '<table>';

    $first = TRUE;

    foreach (element_children($form[$rtype][$round]) as $match) {

      // add a spacer between matches
      if ($first) {
        $first = FALSE;
      }
      else {
        $table .= '<tr><td>&nbsp;</td></tr>';
      }

      $hasloserroute = isset($form[$rtype][$round][$match]['loser_match']);

      $table .= "\n<!--match_begin-->\n<tr><td";
      if ($hasloserroute) {
        $table .= ' rowspan="2"';
      }
      $table .= '>';

      $table .= drupal_render($form[$rtype][$round][$match]['matchid']);
      unset($form[$rtype][$round][$match]['matchid']);

      $table .= '</td>';

      if (isset($form[$rtype][$round][$match]['winner_match'])) {

        $table .= '<td nowrap><strong>' . t('Winner') .'</strong></td>';

        $table .= '<td>';
        $table .= drupal_render($form[$rtype][$round][$match]['winner_match']);
        unset($form[$rtype][$round][$match]['winner_match']);
        $table .= '</td>';

        $table .= '<td>';
        $table .= drupal_render($form[$rtype][$round][$match]['winner_comp']);
        unset($form[$rtype][$round][$match]['winner_match']);
        $table .= '</td>';
      }

      if ($hasloserroute) {

        $table .= '</tr><tr><td nowrap><strong>' . t('Loser') .'</strong></td>';

        $table .= '<td>';
        $table .= drupal_render($form[$rtype][$round][$match]['loser_match']);
        unset($form[$rtype][$round][$match]['loser_match']);
        $table .= '</td>';

        $table .= '<td>';
        $table .= drupal_render($form[$rtype][$round][$match]['loser_comp']);
        unset($form[$rtype][$round][$match]['loser_match']);
        $table .= '</td>';
      }

      if (isset($form[$rtype][$round][$match]['winner_result']) ||
          isset($form[$rtype][$round][$match]['loser_result']) ||
          isset($form[$rtype][$round][$match]['win_use_result'])) {

        if (isset($form[$rtype][$round][$match]['winner_result'])) {
          $table .= '</tr><tr><td colspan="4" nowrap>';
          $table .= drupal_render($form[$rtype][$round][$match]['winner_result']);
          unset($form[$rtype][$round][$match]['winner_result']);
          $table .= '</td>';
        }
        if (isset($form[$rtype][$round][$match]['loser_result'])) {
          $table .= '</tr><tr><td colspan="4" nowrap>';
          $table .= drupal_render($form[$rtype][$round][$match]['loser_result']);
          unset($form[$rtype][$round][$match]['loser_result']);
          $table .= '</td></tr>';
        }
        if (isset($form[$rtype][$round][$match]['win_use_result'])) {
          $table .= '</tr><tr><td colspan="4" nowrap>';
          $table .= drupal_render($form[$rtype][$round][$match]['win_use_result']);
          unset($form[$rtype][$round][$match]['win_use_result']);
          $table .= '</td>';
          $table .= '</tr><tr><td colspan="4">';
          $table .= drupal_render($form[$rtype][$round][$match]['win_use_result_comment']);
          unset($form[$rtype][$round][$match]['win_use_result_comment']);
          $table .= '</td>';
        }
      }

      $table .= "</tr>\n<!--match_end-->\n";
    }   // end - foreach (element_children($form[$rtype][$round]) as $match)...

    $table .= '</table>';

    // Create the table inside the fieldset
    $form[$rtype][$round]['table'] = array(
      '#markup' => $table
    );

    $output .= "\n<!--round_begin-->\n<td>";
    $output .= drupal_render($form[$rtype][$round]);
    $output .= "</td>\n<!--round_end-->\n";

  }   // end - foreach ($wm as $round)...

  $output .= "</tr></table>\n<!--winner_table_end-->\n";

  if (count($lr) > 0) {

    $rtype = 'loser';

    // header for loser matches
    $output .= '<hr /><p><h2>' . t('Loser Matches') . '</h2></p>';

    $output .= "\n<!--loser_table_begin-->\n<table><tr>";

    foreach ($lr as $round) {

      $table = '<table>';

      $first = TRUE;

      foreach (element_children($form[$rtype][$round]) as $match) {

        // add a spacer between matches
        if ($first) {
          $first = FALSE;
        }
        else {
          $table .= '<tr><td>&nbsp;</td></tr>';
        }

        $table .= "\n<!--match_begin-->\n<tr><td>";

        $table .= drupal_render($form[$rtype][$round][$match]['matchid']);
        unset($form[$rtype][$round][$match]['matchid']);

        $table .= '</td>';

        if (isset($form[$rtype][$round][$match]['winner_match'])) {

          $table .= '<td nowrap><strong>' . t('Winner') .'</strong></td>';

          $table .= '<td>';
          $table .= drupal_render($form[$rtype][$round][$match]['winner_match']);
          unset($form[$rtype][$round][$match]['winner_match']);
          $table .= '</td>';

          $table .= '<td>';
          $table .= drupal_render($form[$rtype][$round][$match]['winner_comp']);
          unset($form[$rtype][$round][$match]['winner_match']);
          $table .= '</td>';
        }

        if (isset($form[$rtype][$round][$match]['winner_result']) ||
            isset($form[$rtype][$round][$match]['loser_result']) ||
            isset($form[$rtype][$round][$match]['win_use_result'])) {

          if (isset($form[$rtype][$round][$match]['winner_result'])) {
            $table .= '</tr><tr><td colspan="4" nowrap>';
            $table .= drupal_render($form[$rtype][$round][$match]['winner_result']);
            unset($form[$rtype][$round][$match]['winner_result']);
            $table .= '</td>';
          }
          if (isset($form[$rtype][$round][$match]['loser_result'])) {
            $table .= '</tr><tr><td colspan="4" nowrap>';
            $table .= drupal_render($form[$rtype][$round][$match]['loser_result']);
            unset($form[$rtype][$round][$match]['loser_result']);
            $table .= '</td></tr>';
          }
          if (isset($form[$rtype][$round][$match]['win_use_result'])) {
            $table .= '</tr><tr><td colspan="4" nowrap>';
            $table .= drupal_render($form[$rtype][$round][$match]['win_use_result']);
            unset($form[$rtype][$round][$match]['win_use_result']);
            $table .= '</td>';
            $table .= '</tr><tr><td colspan="4">';
            $table .= drupal_render($form[$rtype][$round][$match]['win_use_result_comment']);
            unset($form[$rtype][$round][$match]['win_use_result_comment']);
            $table .= '</td>';
          }
        }

        $table .= "</tr>\n<!--match_end-->\n";
      }

      $table .= '</table>';

      $form[$rtype][$round]['table'] = array(
        '#type' => 'markup',
        '#markup' => $table
      );

      $output .= "\n<!--round_begin-->\n<td>";
      $output .= drupal_render($form[$rtype][$round]);
      $output .= "</td>\n<!--round_end-->\n";
    }

    $output .= "</tr></table>\n<!--loser_table_end-->\n";

  }   // end - if (count($lr) > 0)...

  $output .= drupal_render_children($form);

  return $output;
}

function bracket_route_edit_form_validate($form_id, &$form_state) {

  $nid = $form_state['values']['nid'];
  $node = node_load($nid);

  $ma = array();

  // make sure a match number is only selected once
  for ($i=1; $i<=count($node->round); $i++) {

    $round = 'round' . $i;
    $r = $node->round[$i];

    for ($j=1; $j<=count($r->match); $j++) {

      $match = 'match' . $j;
      $m = $r->match[$j];

      $id = $form_state['values'][$round][$match]['matchid'];

      if (isset($ma[$id])) {
        form_set_error($round .']['. $match .'][matchid',
                        t('Match #@id is selected more than once.', array('@id' => $id)));
      }
      $ma[$id] = TRUE;
    }
  }

  unset($ma);
  $ma = array();

  // make sure each match competitor is only routed once
  for ($i=1; $i<=count($node->round); $i++) {

    $round = 'round' . $i;
    $r = $node->round[$i];

    for ($j=1; $j<=count($r->match); $j++) {

      $match = 'match' . $j;
      $m = $r->match[$j];

      $wm = isset($form_state['values'][$round][$match]['winner_match']) ? $form_state['values'][$round][$match]['winner_match'] : 0;
      $wc = isset($form_state['values'][$round][$match]['winner_comp']) ? $form_state['values'][$round][$match]['winner_comp'] : 0;
      $lm = isset($form_state['values'][$round][$match]['loser_match']) ? $form_state['values'][$round][$match]['loser_match'] : 0;
      $lc = isset($form_state['values'][$round][$match]['loser_comp']) ? $form_state['values'][$round][$match]['loser_comp'] : 0;

      if ($wm > 0 && $wc == 0) {
        form_set_error($round .']['. $match . '][winner_comp',
                        t('Match #@id, No Competitor selected.', array('@id' => $wm)));
      }
      if ($lm > 0 && $wc == 0) {
        form_set_error($round .']['. $match . '][loser_comp',
                        t('Match #@id, No Competitor selected.', array('@id' => $lm)));
      }
      if ($wm > 0 && $wc > 0 && isset($ma[$wm][$wc])) {
        form_set_error($round .']['. $match . '][winner_match',
                        t('Match #@id, Competitor #@cn is routed more than once.', array('@id' => $wm, '@cn' => $wc)));
      }
      if ($lm > 0 && $lc > 0 && isset($ma[$lm][$lc])) {
        form_set_error($round .']['. $match . '][loser_match',
                        t('Match #@id, Competitor #@cn is routed more than once.', array('@id' => $lm, '@cn' => $lc)));
      }
      if ($wm > 0 && $wc > 0) {
        $ma[$wm][$wc] = TRUE;
      }
      if ($lm > 0 && $lc > 0) {
        $ma[$lm][$lc] = TRUE;
      }
    }
  }
}

function bracket_route_edit_form_submit($form_id, &$form_state) {

  $nid = $form_state['values']['nid'];
  $node = node_load($nid);

  for ($i=1; $i<=count($node->round); $i++) {

    $round = 'round' . $i;
    $r = $node->round[$i];

    for ($j=1; $j<=count($r->match); $j++) {

      $match = 'match' . $j;
      $m = $r->match[$j];

      // update the match id
      $m->id = $form_state['values'][$round][$match]['matchid'];

      // update the routing
      $m->winner_match = isset($form_state['values'][$round][$match]['winner_match']) ? $form_state['values'][$round][$match]['winner_match'] : 0;
      $m->winner_comp = isset($form_state['values'][$round][$match]['winner_comp']) ? $form_state['values'][$round][$match]['winner_comp'] : 0;
      $m->loser_match = isset($form_state['values'][$round][$match]['loser_match']) ? $form_state['values'][$round][$match]['loser_match'] : 0;
      $m->loser_comp = isset($form_state['values'][$round][$match]['loser_comp']) ? $form_state['values'][$round][$match]['loser_comp'] : 0;
     }
  }

  node_save($node);

  drupal_set_message(t('Bracket has been updated'));
}