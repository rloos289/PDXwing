<?php

/**
 * @file
 * This file contains the round helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */
 
 
/**
 * Display list of rounds for the given bracket node
 */
function bracket_round_list_form($form, $form_state, $node) {

  $header = array(
    t('Round'),
    t('Matches'), 
    t('Matches Decided'), 
    array('data' => t('Operations'), 'colspan' => '2')
  );

  $rows = array();
  foreach ($node->round as $r) {

    $link = 'node/'. $node->nid . '/edit/round/' . $r->id;
    
    $dc = 0;
    foreach ($r->match as $m) {
      if ($m->win[1] || $m->win[2]) {
        $dc++;
      }
    }
    
    $rows[] = array(
      l($r->name, $link),
      count($r->match),
      $dc,
      l(t('Edit'), $link),
    );
  }

  $form = array();
  $form['round_list'] = array(
    '#type' => 'markup',
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows))
  );
  
  return $form;
}
 

/**
 * Round edit form
 */
function bracket_round_edit_form($form, $form_state, $node, $id) {

  $form = array();
  $r = $node->round[$id];

  drupal_set_title($r->name . ' - ' . check_plain($node->title));

  $form['head']['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid
  );

  $form['head']['roundid'] = array(
    '#type' => 'value',
    '#value' => $id
  );

  $form['head']['help'] = array(
    '#type' => 'markup',
    '#markup' => t('Use this form to enter and view bracket competitors, comments, select winners and enter scores.')
  );

  $form['head']['rname'] = array(
    '#type' => 'textfield',
    '#title' => t('Round'),
    '#size' => 50,
    '#maxlength' => 50,
    '#default_value' => $node->round[$id]->name
  );

  $form['head']['rcomment'] = array(
    '#type' => 'textfield',
    '#title' => t('Round Comment'),
    '#size' => 50,
    '#maxlength' => 50,
    '#default_value' => $node->round[$id]->comment
  );

  for ($i=1; $i<=count($r->match); $i++) {

    $m = $r->match[$i];

    // generate match fieldset
    $match = 'match' . $i;

    $form['round'][$match] = array(
      '#type' => 'fieldset',
      '#title' => '<strong>' . t('Match') . ' #' . $m->id . '</strong>',
      '#tree' => TRUE
    );

    // for first round, allow the competitor to be entered
    if ($r->first) {
      $form['round'][$match]['comp1'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #1',
        '#size' => 50,
        '#maxlength' => 50,
        '#default_value' => $m->cname[1],
      );
      $form['round'][$match]['seed1'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #1 ' . t('Seed'),
        '#size' => 10,
        '#maxlength' => 50,
        '#default_value' => $node->comp[$m->compid[1]]->seedin,
      );
    }
    // otherwise, just show the competitor
    else {
      $form['round'][$match]['comp1'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #1',
        '#size' => 50,
        '#maxlength' => 50,
        '#default_value' => $m->cname[1],
        '#attributes' => array('readonly' => 'readonly'),
      );
    }

    // competitor #1, winner indicator
    $form['round'][$match]['win1'] = array(
      '#type' => 'checkbox',
      '#title' => t('Winner'),
      '#default_value' => $m->win[1],
    );

    // competitor #1, score
    $form['round'][$match]['score1'] = array(
      '#type' => 'textfield',
      '#title' => t('Score'),
      '#size' => 10,
      '#maxlength' => 10,
      '#default_value' => $m->score[1],
    );

    $form['round'][$match]['comp1_comment'] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #1 - ' . t('Comment'),
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $m->comp_comment[1],
    );

    // competitor #1 home indicator
    $form['round'][$match]['home1'] = array(
      '#type' => 'checkbox',
      '#title' => t('Home'),
      '#default_value' => $m->home[1],
    );

    // match comments
    $form['round'][$match]['comment1'] = array(
      '#type' => 'textfield',
      '#title' => t('Match Comment') . ' 1',
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $m->comment[1],
    );

    $form['round'][$match]['comment2'] = array(
      '#type' => 'textfield',
      '#title' => t('Match Comment') . ' 2',
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $m->comment[2],
    );

    // repeat for competitor #2
    // for first round, allow the competitor to be entered
    if ($r->first) {
      $form['round'][$match]['comp2'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #2',
        '#size' => 50,
        '#maxlength' => 50,
        '#default_value' => $m->cname[2],
      );
      $form['round'][$match]['seed2'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #2 ' . t('Seed'),
        '#size' => 10,
        '#maxlength' => 50,
        '#default_value' => $node->comp[$m->compid[2]]->seedin,
      );
    }
    // otherwise, just show the competitor
    else {
      $form['round'][$match]['comp2'] = array(
        '#type' => 'textfield',
        '#title' => t('Competitor') . ' #2',
        '#size' => 50,
        '#maxlength' => 50,
        '#default_value' => $m->cname[2],
        '#attributes' => array('readonly' => 'readonly'),
      );
    }

    // competitor #2 home indicator
    $form['round'][$match]['home2'] = array(
      '#type' => 'checkbox',
      '#title' => t('Home'),
      '#default_value' => $m->home[2],
    );

    // competitor #2, winner indicator
    $form['round'][$match]['win2'] = array(
      '#type' => 'checkbox',
      '#title' => t('Winner'),
      '#default_value' => $m->win[2],
    );

    // competitor #2, score
    $form['round'][$match]['score2'] = array(
      '#type' => 'textfield',
      '#title' => t('Score'),
      '#size' => 10,
      '#maxlength' => 10,
      '#default_value' => $m->score[2],
    );

    $form['round'][$match]['comp2_comment'] = array(
      '#type' => 'textfield',
      '#title' => t('Competitor') . ' #2 - ' . t('Comment'),
      '#size' => 50,
      '#maxlength' => 50,
      '#default_value' => $m->comp_comment[2],
    );

  }   // end - for ($i=1; $i<=count($r->match); $i++)...

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#weight' => 45,
  );

  return $form;
}

function theme_bracket_round_edit_form($variables) {

  $form = $variables['form'];

  // Format each match fieldset into a table to better arrange the fields
  foreach (element_children($form['round']) as $match) {

    $table = '<table>';
    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comp1']) . '</td>';
    if (isset($form['round'][$match]['seed1'])) {
      $table .= '<td>' . drupal_render($form['round'][$match]['seed1']) . '</td>';
      unset($form['round'][$match]['seed1']);
    }
    $table .= '<td>' . drupal_render($form['round'][$match]['win1']) .  '</td>';
    $table .= '<td>' . drupal_render($form['round'][$match]['score1']) . '</td>';
    unset($form['round'][$match]['comp1']);
    unset($form['round'][$match]['win1']);
    unset($form['round'][$match]['score1']);
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td colspan="4"><hr /></td>';
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comp1_comment']) . '</td>';
    $table .= '<td>' . drupal_render($form['round'][$match]['home1']) . '</td>';
    unset($form['round'][$match]['comp1_comment']);
    unset($form['round'][$match]['home1']);
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comment1']) . '</td>';
    unset($form['round'][$match]['comment1']);
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comment2']) . '</td>';
    unset($form['round'][$match]['comment2']);
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comp2']) . '</td>';
    if (isset($form['round'][$match]['seed2'])) {
      $table .= '<td>' . drupal_render($form['round'][$match]['seed2']) . '</td>';
      unset($form['round'][$match]['seed2']);
    }
    $table .= '<td>' . drupal_render($form['round'][$match]['win2']) . '</td>';
    $table .= '<td>' . drupal_render($form['round'][$match]['score2']) . '</td>';
    unset($form['round'][$match]['comp2']);
    unset($form['round'][$match]['win2']);
    unset($form['round'][$match]['score2']);
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td colspan="4"><hr /></td>';
    $table .= '</tr>';

    $table .= '<tr>';
    $table .= '<td>' . drupal_render($form['round'][$match]['comp2_comment']) . '</td>';
    $table .= '<td>' . drupal_render($form['round'][$match]['home2']) . '</td>';
    unset($form['round'][$match]['comp2_comment']);
    unset($form['round'][$match]['home2']);
    $table .= '</tr>';

    $table .= '</table>';

    // Create the table inside the fieldset
    $form['round'][$match]['table'] = array(
      '#markup' => $table
    );
  }
  
  return drupal_render_children($form);
}

function bracket_round_edit_form_validate($form_id, &$form_state) {

  // iterate through matches
  foreach (array_filter(array_keys($form_state['values']), 'bracket_round_edit_form_match_key') as $match) {

    $msg = t('There can only be one home competitor, please select one home competitor only.');
    if ($form_state['values'][$match]['home1'] == 1 && $form_state['values'][$match]['home2'] == 1 ) {
      form_set_error($match . '][home1' , $msg);
      form_set_error($match . '][home2' , $msg);
      return;
    }

    $msg = t('There can only be one winner, please select one winner only.');
    if ($form_state['values'][$match]['win1'] == 1 && $form_state['values'][$match]['win2'] == 1 ) {
      form_set_error($match .'][win1', $msg);
      form_set_error($match .'][win2', $msg);
      return;
    }
  }
}

function bracket_round_edit_form_match_key($key) {
  // return true if string (key) begins with 'match'
  return (substr($key, 0, 5) == 'match');
}

function bracket_round_edit_form_submit($form_id, &$form_state) {

  // get ids
  $nid = $form_state['values']['nid'];
  $rid = $form_state['values']['roundid'];

  // load the node
  $node = node_load($nid);

  // get the round
  $r = $node->round[$rid];

  // update round info
  $r->name = $form_state['values']['rname'];
  $r->comment = $form_state['values']['rcomment'];

  // update all matches in the round
  for ($i=1; $i<= count($r->match); $i++) {

    $match = 'match' . $i;

    $m = $r->match[$i];

    // save previous win flags
    $win1 = $m->win[1];
    $win2 = $m->win[2];

    // update match info
    $m->home[1] = $form_state['values'][$match]['home1'];
    $m->win[1] = $form_state['values'][$match]['win1'];
    $m->score[1] = trim($form_state['values'][$match]['score1']);
    $m->comp_comment[1] = $form_state['values'][$match]['comp1_comment'];
    $m->home[2] = $form_state['values'][$match]['home2'];
    $m->win[2] = $form_state['values'][$match]['win2'];
    $m->score[2] = trim($form_state['values'][$match]['score2']);
    $m->comp_comment[2] = $form_state['values'][$match]['comp2_comment'];
    $m->comment[1] = $form_state['values'][$match]['comment1'];
    $m->comment[2] = $form_state['values'][$match]['comment2'];

    // update competitors if round 1
    if ($rid == 1) {
      $node->comp[$m->compid[1]]->name = $form_state['values'][$match]['comp1'];
      $node->comp[$m->compid[1]]->seedin = $form_state['values'][$match]['seed1'];
      $node->comp[$m->compid[2]]->name = $form_state['values'][$match]['comp2'];
      $node->comp[$m->compid[2]]->seedin = $form_state['values'][$match]['seed2'];
    }

    // see if winner has changed
    if ($win1 != $m->win[1] || $win2 != $m->win[2]) {

      // get winner and loser
      if ($m->win[1]) {
        // winner must be a valid competitor - loser can be nil
        if ($m->compid[1] == 0) {
          drupal_set_message(t('Competitor #1 has not been determined for Match @mid and cannot be selected as the winner',
                                   array('@mid' => $m->id)), 'error');
          return;
        }
        $wcompid = $m->compid[1];
        $lcompid = $m->compid[2];
      }
      elseif ($m->win[2]) {
        if ($m->compid[2] == 0) {
          drupal_set_message(t('Competitor #2 has not been determined for Match @mid and cannot be selected as the winner',
                                   array('@mid' => $m->id)), 'error');
          return;
        }
        $wcompid = $m->compid[2];
        $lcompid = $m->compid[1];
      }
      else {
        $wcompid = 0;
        $lcompid = 0;
      }

      // route to results
      if ($m->winner_result > 0 || $m->loser_result > 0) {

        // check for previous winners put into results
        if ($m->win_use_result > 0) {
          if ((($win1 && $m->win_use_result == 1) && ($win1 != $m->win[1])) ||
              (($win2 && $m->win_use_result == 2) && ($win2 != $m->win[2]))) {
            $node->result[$m->winner_result]->compid = 0;
            $node->result[$m->loser_result]->compid = 0;
          }
        }

        // make sure it is appropriate
        if ($m->win_use_result == 0 || ($m->win_use_result > 0 && $m->win[$m->win_use_result])) {

          // place winner
          if ($m->winner_result > 0) {
            $s = $node->result[$m->winner_result];
            $s->compid = $wcompid;
            if ($wcompid > 0) {
              drupal_set_message(t('Winner of Match @mid (@name) has been placed in Results Place #@place',
                                    array('@mid' => $m->id, '@name' => $node->comp[$wcompid]->name, '@place' => $m->winner_result)));
            }
            else {
              drupal_set_message(t('Match @mid results were reset.', array('@mid' => $m->id)));
            }
          }

          // place loser
          if ($m->loser_result > 0) {
            $s = $node->result[$m->loser_result];
            $s->compid = $lcompid;
            if ($lcompid > 0) {
              drupal_set_message(t('Loser of Match @mid (@name) has been placed in Results Place #@place',
                                    array('@mid' => $m->id, '@name' => $node->comp[$lcompid]->name, '@place' => $m->loser_result)));
            }
            else {
              drupal_set_message(t('Match @mid results were reset.', array('@mid' => $m->id)));
            }
          }
        }
      }

      // route to next match
      if ($m->winner_match > 0 || $m->loser_match > 0) {

        // make sure it is apporpriate
        if ($m->win_use_result == 0 || ($m->win_use_result > 0 && !$m->win[$m->win_use_result])) {

          // route winner
          if ($m->winner_match > 0 && $m->winner_comp > 0) {

            // get match index
            if ($mindex = bracket_round_get_match_index($node, $m->winner_match)) {

              // get match
              $m2 = $node->round[$mindex['round']]->match[$mindex['match']];

              // update competitor in next match
              $m2->compid[$m->winner_comp] = $wcompid;

              // tell user what was done
              if ($wcompid > 0) {
                drupal_set_message(t('Winner of Match @mid (@name) has been placed in @round,
                                      Match @match, Competitor @comp',
                                      array('@mid' => $m->id, '@name' => $node->comp[$wcompid]->name, '@round' => $node->round[$mindex['round']]->name,
                                            '@match' => $m->winner_match, '@comp' => $m->winner_comp)));
              }
              else {
                drupal_set_message(t('Match @mid results were reset.', array('@mid' => $m->id)));
              }

              // propogate competitor through the rest of the tree
              bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->winner_comp);
            }
          } // end - if ($m->winner_match > 0 && $m->winner_comp > 0)...

          // route loser
          if ($m->loser_match > 0 && $m->loser_comp > 0) {

            if ($mindex = bracket_round_get_match_index($node, $m->loser_match)) {

              $m2 = $node->round[$mindex['round']]->match[$mindex['match']];
              $m2->compid[$m->loser_comp] = $lcompid;

              if ($lcompid > 0) {
                drupal_set_message(t('Loser of Match @mid (@name) has been placed in @round,
                                      Match @match, Competitor @comp',
                                      array('@mid' => $m->id, '@name' => $node->comp[$lcompid]->name, '@round' => $node->round[$mindex['round']]->name,
                                            '@match' => $m->loser_match, '@comp' => $m->loser_comp)));
              }
              else {
                drupal_set_message(t('Match @mid results were reset.', array('@mid' => $m->id)));
              }

              bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->loser_comp);
            }
          }   // end - if ($m->loser_match > 0 && $m->loser_comp > 0)...
        }   // end - if ($m->win_use_result == 0 || ($m->win_use_result > 0 && !$m->win[$m->win_use_result])...
      }   // end - if ($m->winner_match > 0 || $m->loser_match > 0)...
    }   // end - if ($win1 != $m->win[1] || $win2 != $m->win[2])...
  }   // end - for ($i=1; $i<= count($r->match); $i++)...

  // save the node
  node_save($node);
  drupal_set_message(t('Bracket has been updated'));
}

/**
 * Check bracket tree starting at given match and competitor
 * Make sure competitor id is properly propagated in bracket tree
 *
 * @param $node
 *   the node object
 * @param $ri
 *   the round index
 * @param $mi
 *   the match index
 * @param $comp
 *   the competitor index
 */
function bracket_round_check_tree(&$node, $ri, $mi, $comp) {

  // get match
  $m = $node->round[$ri]->match[$mi];

  // no routing or results, done
  if ($m->winner_match == 0 && $m->loser_match == 0 && $m->winner_result == 0 && $m->loser_result == 0) {
    return;
  }

  // adjust results, if needed
  if (($m->winner_result > 0 || $m->loser_result > 0) && 
      ($m->win_use_result == 0 || ($m->win_use_result > 0 && $m->win[$m->win_use_result]))) {
    // if winner is marked
    if ($m->win[1] || $m->win[2]) {
      if ($m->win[$comp] && $m->winner_result > 0 ) {
        $node->result[$m->winner_result]->compid = $m->compid[$comp];
      }
      elseif (!$m->win[$comp] && $m->loser_result > 0) {
        $node->result[$m->loser_result]->compid = $m->compid[$comp];
      }
    }
  }

  // check routing, if needed
  if ($m->winner_match > 0 && ($m->win_use_result == 0 || ($m->win_use_result > 0 && !$m->win[$m->win_use_result]))) {
    // competitor won, check winner chain
    if ($m->win[$comp] && $m->winner_match > 0) {
      if ($mindex = bracket_round_get_match_index($node, $m->winner_match)) {
        $m2 = $node->round[$mindex['round']]->match[$mindex['match']];
        if ($m2->compid[$m->winner_comp] != $m->compid[$comp]) {
          $m2->compid[$m->winner_comp] = $m->compid[$comp];
          bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->winner_comp);
        }
      }
    }
    // competitor did not win, check loser chain
    elseif ($m->loser_match > 0 && ($m->win[1] || $m->win[2])) {
      if ($mindex = bracket_round_get_match_index($node, $m->loser_match)) {
        $m2 = $node->round[$mindex['round']]->match[$mindex['match']];
        if ($m2->compid[$m->loser_comp] != $m->compid[$comp]) {
          $m2->compid[$m->loser_comp] = $m->compid[$comp];
          bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->loser_comp);
        }
      }
    }
  }
}

/**
 * Return the first winner match in the bracket - always one (1)
 *
 * @param $node
 *   the node object
 * @return
 *   the index of first winner round
 */
function bracket_round_first_winner_round($node) {

  return 1;
}

/**
 * return the last winner round in the bracket
 *
 * @param $node
 *   the node object
 * @return
 *   the index of last winner round
 */
function bracket_round_last_winner_round($node) {

  // last winner round is the round before the first loser round
  $lr = bracket_round_first_loser_round($node);
  if ($lr > 0) {
    return $lr - 1;
  }
  return count($node->round);
}

/**
 * return the first loser round in the bracket
 *
 * @param $node
 *   the node object
 * @return
 *   the index of first loser round
 */
function bracket_round_first_loser_round($node) {

  // iterate through rounds until a loser round is encountered
  for ($i=1; $i<=count($node->round); $i++) {
    if ($node->round[$i]->loser) {
      return $i;
    }
  }
  // no loser rounds
  return 0;
}

/**
 * return the last loser round in the bracket
 *
 * @param $node
 *   the node object
 * @return
 *   the index of last loser round
 */
function bracket_round_last_loser_round($node) {

  // if a loser round exists, the last loser round is the last round
  if (bracket_round_first_loser_round($node) > 0) {
    return count($node->round);
  }
  // no loser rounds
  return 0;
}

/**
 * return the indexes to the given match id
 *
 * @param $node
 *   the node object
 * @param $matchid
 *   the match id to search for
 * @return
 *   round and match indexes as an associative 
 *   array if the match id was found, otherwise false
 */
function bracket_round_get_match_index($node, $matchid) {

  // iterate through rounds and matches until match id is found
  for ($i=1; $i<=count($node->round); $i++) {
    $r = $node->round[$i];
    for ($j=1; $j<=count($r->match); $j++) {
      $m = $r->match[$j];
      if ($m->id == $matchid) {
        // match id was found, return indexes
        return array('round' => $i, 'match' => $j);
      }
    }
  }
  // match id was not found
  return FALSE;
}