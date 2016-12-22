<?php

/**
 * @file
 * This file contains the database helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Load a bracket node into this bracket object
 *
 * @param $node
 *   the node to contain the bracket
 * @return
 *   the loaded bracket object, if it exists
 */
function bracket_db_load($node) {

  $bracket = new Bracket();
  
  // try to load from the db
  $result = db_query(
    "SELECT * FROM {bracket} WHERE nid = :nid", 
    array(':nid' => $node->nid)
  );
  if ($record = $result->fetchObject()) {

    // copy info
    $bracket->subtitle = $record->subtitle;
    $bracket->comments = $record->comments;
    $bracket->sport = $record->sport;
    $bracket->division = $record->division;
    $bracket->season = $record->season;
    $bracket->brgroup = $record->brgroup;
    $bracket->footer = $record->footer;
    $bracket->logopath = $record->logopath;
    $bracket->sponsorlogopath = $record->sponsorlogopath;
    $bracket->design = $record->design;
    $bracket->options = unserialize($record->options);

    // convert options to new format if needed    
    if (!isset($bracket->options['image_options'])) {
      $bracket->options['image_options']['image_fonts'] = $bracket->options['image_fonts'];
      $bracket->options['image_options']['bg_color'] = $bracket->options['bg_color'];
      $bracket->options['image_options']['fg_color'] = $bracket->options['fg_color'];
      $bracket->options['image_options']['bar_bg_color'] = $bracket->options['bar_bg_color'];
      $bracket->options['image_options']['bar_fg_color'] = $bracket->options['bar_fg_color'];
      $bracket->options['image_options']['show_bracket_bar'] = $bracket->options['show_bracket_bar'];
      $bracket->options['image_options']['pdf_font'] = $bracket->options['pdf_font'];
      unset($bracket->options['image_fonts']);
      unset($bracket->options['bg_color']);
      unset($bracket->options['fg_color']);
      unset($bracket->options['bar_bg_color']);
      unset($bracket->options['bar_fg_color']);
      unset($bracket->options['show_bracket_bar']);
      unset($bracket->options['pdf_font']);
    }

    // load competitors
    $result = db_query(
      "SELECT * FROM {bracket_comp} WHERE nid = :nid ORDER BY id", 
      array(':nid' => $node->nid)
    );
    while($record = $result->fetchObject()) {
      $c = new Bracket_Competitor();
      $c->name = $record->name;
      $c->seedin = $record->seedin;
      $bracket->comp[$record->id] = $c;
    }

    // load rounds
    $result = db_query(
      "SELECT * FROM {bracket_round} WHERE nid = :nid ORDER BY id", 
      array(':nid' => $node->nid)
    );
    while($record = $result->fetchObject()) {

      // add round
      $r = new Bracket_Round();
      $r->id = $record->id;
      $r->name = $record->round;
      $r->loser = $record->loser;
      $r->first = $record->first;
      $r->comment = $record->comment;
      $bracket->round[$record->id] = $r;
      
      // load matches for this round
      $result2 = db_query(
        "SELECT m.*, r.loser
         FROM {bracket_match} m
         JOIN {bracket_round} r on r.id = m.roundid
         WHERE m.nid = :nid AND m.roundid = :roundid
         ORDER BY m.seq", 
        array(':nid' => $node->nid, ':roundid' => $record->id)
      );
      while($record2 = $result2->fetchObject()) {

        // add the match
        $m = new Bracket_Match();
        $m->id = $record2->id;
        $m->compid[1] = $record2->compid1;
        if ($m->compid[1] > 0) {
          $m->cname[1] = $bracket->comp[$m->compid[1]]->name;
        }
        $m->score[1] = $record2->score1;
        $m->home[1] = $record2->home1;
        $m->win[1] = $record2->win1;
        $m->comp_comment[1] = $record2->comp1_comment;
        $m->compid[2] = $record2->compid2;
        if ($m->compid[2] > 0)
          $m->cname[2] = $bracket->comp[$m->compid[2]]->name;
        $m->score[2] = $record2->score2;
        $m->home[2] = $record2->home2;
        $m->win[2] = $record2->win2;
        $m->comp_comment[2] = $record2->comp2_comment;
        $m->roundid = $record2->roundid;
        $m->comment[1] = $record2->match_comment1;
        $m->comment[2] = $record2->match_comment2;
        $m->winner_match = $record2->winner_match;
        $m->winner_comp = $record2->winner_comp;
        $m->loser_match = $record2->loser_match;
        $m->loser_comp = $record2->loser_comp;
        $m->winner_result = $record2->winner_result;
        $m->loser_result = $record2->loser_result;
        $m->win_use_result = $record2->win_use_result;

        $bracket->round[$r->id]->match[$record2->seq] = $m;
      }
    }

    // load results
    $result = db_query(
      "SELECT * FROM {bracket_result} WHERE nid = :nid ORDER BY id", 
      array(':nid' => $node->nid)
    );
    while($record = $result->fetchObject()) {
      $s = new Bracket_Result();
      $s->compid = $record->compid;
      if ($s->compid > 0) {
        $s->cname = $bracket->comp[$s->compid]->name;
      }
      $s->comment = $record->comment;
      $s->seedout = $record->seedout;
      $bracket->result[$record->id] = $s;
    }
  }

  // load the design if set
  if ($bracket->design != '') {
    bracket_design_load($bracket->design);
  }

  // return the bracket
  return $bracket;
}

/**
 * insert a new bracket node to the db
 *
 * @param $node
 *   the node containing the bracket
 */
function bracket_db_insert($node) {

  bracket_db_update_tree($node);

  db_insert('bracket')
    ->fields(array(
      'nid' => $node->nid,
      'subtitle' => $node->subtitle,
      'comments' => $node->comments,
      'sport' => $node->sport,
      'division' => $node->division,
      'season' => $node->season,
      'brgroup' => $node->brgroup,
      'footer' => $node->footer,
      'design' => $node->design,
      'logopath' => $node->logopath,
      'sponsorlogopath' => $node->sponsorlogopath,
      'options' => serialize($node->options),
    ))
    ->execute();
}

/**
 * update a bracket node to the db
 *
 * @param $node
 *   the node containing the bracket
 */
function bracket_db_update($node) {

  bracket_db_update_tree($node);

  db_update('bracket')
    ->fields(array(
      'subtitle' => $node->subtitle,
      'comments' => $node->comments,
      'sport' => $node->sport,
      'division' => $node->division,
      'season' => $node->season,
      'brgroup' => $node->brgroup,
      'footer' => $node->footer,
      'logopath' => $node->logopath,
      'sponsorlogopath' => $node->sponsorlogopath,
      'options' => serialize($node->options),
    ))
    ->condition('nid', $node->nid)
    ->execute();
}

/**
 * update the db bracket tree from the node
 *
 * @param $node
 *   the node containing the bracket
 */
function bracket_db_update_tree($node) {

  // clear the bracket tree
  bracket_db_delete_tree($node);

  // insert competitors
  for ($i=1; $i<=count($node->comp); $i++) {
    $c = $node->comp[$i];

    db_insert('bracket_comp')
      ->fields(array(
        'nid' => $node->nid,
        'id' => $i,
        'name' => $c->name,
        'seedin' => $c->seedin,
    ))
    ->execute();
  }

  // insert rounds
  for ($i=1; $i<=count($node->round); $i++) {
    $r = $node->round[$i];

    db_insert('bracket_round')
      ->fields(array(
        'nid' => $node->nid,
        'id' => $i,
        'round' => $r->name,
        'loser' => $r->loser ? 1 : 0,
        'first' => $r->first ? 1 : 0,
        'comment' => $r->comment,
    ))
    ->execute();

    // insert matches for this round
    for ($j=1; $j<=count($r->match); $j++) {
      $m = $r->match[$j];

    db_insert('bracket_match')
      ->fields(array(
        'nid' => $node->nid,
        'id' => $m->id,
        'roundid' => $i,
        'seq' => $j,
        'compid1' => $m->compid[1],
        'score1' => $m->score[1],
        'home1' => $m->home[1] ? 1 : 0,
        'win1' => $m->win[1] ? 1 : 0,
        'comp1_comment' => $m->comp_comment[1],
        'compid2' => $m->compid[2],
        'score2' => $m->score[2],
        'home2' => $m->home[2] ? 1 : 0,
        'win2' => $m->win[2] ? 1 : 0,
        'comp2_comment' => $m->comp_comment[2],
        'match_comment1' => $m->comment[1],
        'match_comment2' => $m->comment[2],
        'winner_match' => $m->winner_match,
        'winner_comp' => $m->winner_comp,
        'loser_match' => $m->loser_match,
        'loser_comp' => $m->loser_comp,
        'winner_result' => $m->winner_result,
        'loser_result' => $m->loser_result,
        'win_use_result' => $m->win_use_result,
      ))
      ->execute();
    }
  }
  // insert results
  for ($i=1; $i<=count($node->result); $i++) {
    $s = $node->result[$i];

    db_insert('bracket_result')
      ->fields(array(
        'nid' => $node->nid,
        'id' => $i,
        'compid' => $s->compid,
        'comment' => $s->comment,
        'seedout' => $s->seedout,
      ))
      ->execute();
  }
}

/**
 * delete a bracket node from the db
 *
 * @param $node
 *   the node containing the bracket
 */
function bracket_db_delete($node) {

  bracket_db_delete_tree($node);

  db_delete('bracket')
    ->condition('nid', $node->nid)
    ->execute();
}

/**
 * delete the db bracket tree
 *
 * @param $node
 *   the node containing the bracket
 */
function bracket_db_delete_tree($node) {

  db_delete('bracket_comp')
    ->condition('nid', $node->nid)
    ->execute();
  db_delete('bracket_match')
    ->condition('nid', $node->nid)
    ->execute();
  db_delete('bracket_round')
    ->condition('nid', $node->nid)
    ->execute();
  db_delete('bracket_result')
    ->condition('nid', $node->nid)
    ->execute();
}
