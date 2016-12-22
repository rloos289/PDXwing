<?php

/**
 * @file
 * This file contains the design helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Return a list of valid designs that are found in the designs path in the module directory tree
 *
 * The design must must have a .inc file with the design code and a .info file with the design description
 *
 * @return
 *   a list of designs - key is name, value is design description
 */
function bracket_design_list() {

    $dlist = array();

    $dir = bracket_design_base_path();

    $list = file_scan_directory($dir, '/\.inc$/');

    foreach ($list as $file) {
        $desc = bracket_design_description($file->name);
        if ($desc != '')
            $dlist[$file->name] = $desc;
    }

    // sort by description
    asort($dlist);

    return $dlist;
}

/**
 * Parse info file for bracket design - similar to Drupal's module.info file
 * Uses ini parser provided by php's parse_ini_file().
 *
 * The following values must exist in the design.info file
 * name - the name of the design
 * description - A brief description of the bracket design - ex: Double Elimination 16 Competitor Championship
 *
 * @param $design
 *   the name of the design
 * @return
 *   the design description
 */
function bracket_design_description($design) {

  $desc = '';

  $path = realpath(bracket_design_info($design));

  if (file_exists($path)) {
    $info = parse_ini_file($path);
    $desc = $info['description'];
    $desc .= ' (' . $design . ')';
  }

  return $desc;
}

/**
 * Returns the pathname of the design info file
 *
 * @param $design
 *   the design name
 * @return
 *   the path to the design info file
 */
function bracket_design_info($design) {

  $filename = bracket_design_path($design) . '/' . $design . '.info';
  return $filename;
}

/**
 * Returns the pathname of the design include file
 *
 * @param $design
 *   the design name
 * @return
 *   the path to the design include file
 */
function bracket_design_inc($design) {

  $filename = bracket_design_path($design) . '/' . $design . '.inc';
  return $filename;
}

/**
 * Returns the path to the design directory
 *
 * @param $design
 *   the design name
 * @return
 *   the path to the design directory
 */
function bracket_design_path($design) {

  return bracket_design_base_path() . '/' . $design . '/';
}

/**
 * Returns the path to the designs directory
 *
 * @return
 *   the path to the designs directory
 */
function bracket_design_base_path() {

  return drupal_get_path('module', 'bracket') . '/designs';
}

/**
 * Returns true if design include file was successfully included
 *
 * @param $design
 *   the design name
 * @return
 *   the design description
 */
function bracket_design_load($design) {

  $result = FALSE;

  $path = bracket_design_inc($design);
  $rpath = realpath($path);
  if (file_exists($rpath)) {
    include_once($path);
    $result = TRUE;
  }

  return $result;
}

/**
 * Add the given number of competitors to a bracket
 *
 * @param $node
 *   the bracket node
 * @param $cc
 *   the number of competitors to add
 */
function bracket_design_create_competitors(&$node, $cc) {

  // add competitors
  for ($i=1; $i<=$cc; $i++) {
    $node->comp[$i] = new Bracket_Competitor();
  }
}

/**
 * Add the given number of rounds to a bracket
 *
 * @param $node
 *   the bracket node
 * @param $rounds
 *   the number of rounds to add
 */
function bracket_design_create_winner_rounds(&$node, $rounds = 0) {

  // competitors must already be added
  $cc = count($node->comp);

  // winner round count
  $wrc = log($cc, 2);
  if ($rounds > 0 && $rounds <= $wrc) {
    $wrc = $rounds;
  }

  // init counters
  $mid = 1;
  $compid = 1;

  // add winner rounds
  for ($i=1; $i<=$wrc; $i++) {

    // create a round
    $r = new Bracket_Round();
    $r->id = $i;

    // flag first round
    if ($r->id == 1) {
      $r->first = TRUE;
    }

    // round match count = competitors / 2 ^ round
    $mc = $cc / pow(2, $i);

    // add required matches
    for ($j=1; $j<=$mc; $j++) {

      // create a match
      $m = new Bracket_Match();
      // match id
      $m->id = $mid++;
      // competitors - only add for first round
      if ($r->id == 1) {
        $m->compid[1] = $compid++;
        $m->compid[2] = $compid++;
      }

      // add the match to the round
      $r->match[$j] = $m;
    }

    // add the round to the bracket
    $node->round[$i] = $r;
  }

  // init competitor routing indexes
  $wcomp = 1;

  // assign match routing
  for ($i=1; $i<$wrc; $i++) {

    // get round
    $r = $node->round[$i];

    // iterate though matches
    for ($j=1; $j<=count($r->match); $j++) {

      // get match
      $m = $r->match[$j];

      // next round
      $r2 = $node->round[$i+1];

      // index of next match in winner round
      $j2 = ceil($j / 2);
      $m2 = $r2->match[$j2];

      // route winners to next round
      $m->winner_match = $m2->id;
      $m->winner_comp = $wcomp;

      // winner next competitor index
      $wcomp = ($wcomp == 1) ? 2 : 1;
    }
  }
}

/**
 * Add championship results to a bracket
 *
 * @param $node
 *   the bracket node
 */
function bracket_design_create_championship_results(&$node) {

  // get final round
  $rc = count($node->round);

  // final round results
  $r = $node->round[$rc];
  $m = $r->match[1];
  $m->winner_result = 1;
  $m->loser_result = 2;

  // add results - champion and runner-up
  for ($i=1; $i<=2; $i++) {
    $s = new Bracket_Result();
    if ($i == 1) {
      $s->comment = t('Champion');
    }
    else {
      $s->comment = t('Runner-Up');
    }

    $node->result[$i] = $s;
  }
}

/**
 * Add playoff results to a bracket
 *
 * @param $node
 *   the bracket node
 */
function bracket_design_create_playoff_results(&$node) {

  // get final round
  $rc = count($node->round);
  // add a result for each final round match
  $r = $node->round[$rc];
  for ($i=1; $i<=count($r->match); $i++) {
    $m = $r->match[$i];
    // route winner to cooresponding result
    $m->winner_result = $i;
    // add the result
    $node->result[$i] = new Bracket_Result();
  }
}

/**
 * Add loser rounds to a bracket
 *
 * @param $node
 *   the bracket node
 * @param $modified
 *   indicates if the bracket is a modified double elimination bracket
 *   where the loser bracket competes for consolidation places
 */
function bracket_design_create_loser_rounds(&$node, $modified = FALSE) {

  // competitors must already be added
  $cc = count($node->comp);
  if ($cc <= 2) {
    return;
  }

  // winner round count
  $wrc = count($node->round);
  if ($wrc <= 1) {
    return;
  }

  // next round id
  $rid = $wrc + 1;

  // next match id
  $mid = $cc;

  // winner rounds must be added
  if (!$modified) {

    // reset final round results
    $node->round[$wrc]->match[1]->winner_result = 0;
    $node->round[$wrc]->match[1]->loser_result = 0;

    // create two final rounds
    $r = new Bracket_Round();
    $r->id = $rid++;
    $m = new Bracket_Match();
    $m->id = $mid++;
    // this match has match routing and result routing
    // since a competitor must lose twice to be eliminated
    $m->winner_match = $mid;
    $m->winner_comp = 1;
    $m->loser_match = $mid;
    $m->loser_comp = 2;
    $m->winner_result = 1;
    $m->loser_result = 2;
    // this indicates that if competitor 1 wins this match,
    // competitor 1 is routed to the results - final 2 is not necessary
    // if competitor 2 wins, competitors are routed to final 2
    $m->win_use_result = 1;
    $r->match[1] = $m;
    $node->round[$r->id] = $r;

    // save final match for later
    $finalmid = $m->id;

    // route semifinal winner to final
    $node->round[$wrc]->match[1]->winner_match = $finalmid;
    $node->round[$wrc]->match[1]->winner_comp = 1;

    // add if necessary final match
    $r = new Bracket_Round();
    $r->id = $rid++;
    $m = new Bracket_Match();
    $m->id = $mid++;
    $m->winner_result = 1;
    $m->loser_result = 2;
    $r->match[1] = $m;
    $node->round[$r->id] = $r;
  }

  // loser round index - for naming
  $lri = 1;

  // winner round index
  $wri = 1;

  // init flag
  $rdone = FALSE;

  // save first loser round id
  $first_lrnd = $rid;

  // alternate rounds that contain
  // losers from winner rounds and
  // rounds that contain only previous
  // loser round winners
  $ralt = TRUE;

  // add loser rounds
  while (!$rdone) {

    // create loser round
    $lr = new Bracket_Round();
    $lr->id = $rid++;
    $lr->loser = TRUE;

    // add competitors from winner round
    // and previous loser round, except for
    // first loser round where all competitors
    // are losers from first round
    if ($ralt) {

      // get winner round
      $wr = $node->round[$wri];

      // init match controls
      $lmi = 0;
      $malt = TRUE;
      $comp = 1;
      $wmi = 1;
      $mdone = FALSE;

      // add required matches
      while (!$mdone) {

        // create a match, every other winner match
        if ($malt) {
          // bump match index
          $lmi++;
          // create loser match
          $lm = new Bracket_Match();
          // match id
          $lm->id = $mid++;
          // add the match to the round
          $lr->match[$lmi] = $lm;
        }
        $malt = !$malt;

        // route winner match loser to this match
        if ($comp == 1 || !isset($plr)) {
          $wm = $wr->match[$wmi];
          $wm->loser_match = $lm->id;
          $wm->loser_comp = $comp;
          $lm->comp_comment[$comp] = t('Loser') . ' #' . $wm->id;
        }

        // route previous loser round winners to this round
        if ($comp == 2 && isset($plr)) {
          // get corresponding previous round match
          $plm = $plr->match[$lmi];
          // route winner to this match
          $plm->winner_match = $lm->id;
          $plm->winner_comp = $comp;
        }

        // next competitor index
        $comp = ($comp == 1) ? 2 : 1;

        // if no previous loser round, bump winner match index
        if (!isset($plr)) {
          $wmi++;
        }
        // if previous loser round, bump winner match index
        // every other time through
        else {
          if ($malt) {
            $wmi++;
          }
        }
        // check for end of winner matches
        if ($wmi > count($wr->match)) {
          $mdone = TRUE;
        }
      }   // end - while (!$mdone)...
    }   // end - if ($ralt)...

    // add only competitors from previous loser round
    else {
      // init controls
      $comp = 1;
      $lmi = 0;
      $malt = TRUE;

      // add matches for previous round winners
      for ($i=1; $i<=count($plr->match); $i++) {

        // create a match, every other loser match
        if ($malt) {
          $lmi++;
          $lm = new Bracket_Match();
          // match id
          $lm->id = $mid++;
          // add the match to the round
          $lr->match[$lmi] = $lm;
        }
        $malt = !$malt;

        // get corresponding previous round match
        $plm = $plr->match[$i];
        // route winner to this match
        $plm->winner_match = $lm->id;
        $plm->winner_comp = $comp;

        // next competitor index
        $comp = ($comp == 1) ? 2 : 1;
      }
    }

    // add the round to the bracket
    $node->round[$lr->id] = $lr;

    // save previous loser round
    $plr = $lr;

    // bump loser round counter
    $lri++;
    
    // start alternating rounds after first two rounds
    if ($wri >= 2) {
      $ralt = !$ralt;
    }
    // bump winner round every other loser round
    if ($ralt) {
      $wri++;
    }

    // see if we are done
    if ($modified) {
      // must be a minimum of 2 loser rounds
      if ($wri >= $wrc && $lri > 2) {
        $rdone = TRUE;
      }
    }
    else {
      if ($wri >= $wrc && !$ralt) {
        $rdone = TRUE;
      }
    }
  }   // while (!$rdone)...

  if (!$modified) {

    // route semifinal loser to loser round
    $node->round[$wrc]->match[1]->loser_match = $lm->id;
    $node->round[$wrc]->match[1]->loser_comp = 1;

    // route loser bracket "winner" to final
    $lm->winner_match = $finalmid;
    $lm->winner_comp = 2;
  }

  // flip 2nd round loser routes to loser bracket,
  // so competitors from winner round will not compete
  // against the same competitors that were in Round 1
  $r = $node->round[2];
  $mc = count($r->match);
  for ($i=1; $i<=$mc/2; $i++) {
    $tmp = $r->match[$i]->loser_match;
    $r->match[$i]->loser_match = $r->match[$mc-($i-1)]->loser_match;
    $r->match[$mc-($i-1)]->loser_match = $tmp;
  }
  // flip loser match comments as well
  $r = $node->round[$first_lrnd + 1];
  $mc = count($r->match);
  for ($i=1; $i<=$mc/2; $i++) {
    $tmp = $r->match[$i]->comp_comment[1];;
    $r->match[$i]->comp_comment[1] = $r->match[$mc-($i-1)]->comp_comment[1];
    $r->match[$mc-($i-1)]->comp_comment[1] = $tmp;
  }

}