<?php

/**
 * @file
 * This file contains api functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/** @mainpage Bracket API Documentation
 * The following is the documentataion for the Drupal Tournament 
 * Bracket Module API. Click on the links below to view the list
 * of functions available for each function group.
 *
 * - @link bracket Bracket Node Functions @endlink
 * - @link bracket_comp Bracket Competitor Functions @endlink
 * - @link bracket_round Bracket Round Functions @endlink
 * - @link bracket_match Bracket Match Functions @endlink
 * - @link bracket_result Bracket Result Functions @endlink
 */

/**
 * @defgroup bracket Bracket Node API Functions
 * @{
 * Bracket Nodes
 * The bracket module allows for the creation and manipuation of tournament brackets.
 * Brackets are stored as nodes and consist of competitors, matches, rounds, and results.
 * Since there are so many different bracket configurations, each bracket structure is
 * defined and managed by a bracket "design".  The design determines the number of
 * competitors in the bracket, the configuration of the bracket (single-elimination, 
 * double elimination, etc), and produces the bracket displays. 
 * 
 * Bracket Object
 * Internally, bracket information is stored in a Bracket object - as defined in 
 * bracket_class.inc.  Competitor, Round, Match, and Result objects are utilized as 
 * well in order to store information for their respective data types.  The bracket 
 * objects can be manipulated directly and then saved in order to update the bracket.
 * However, the number of Competitor, Round, Match, and Result objects should not be 
 * modified as this may cause problems in the bracket rendering.  The number of objects
 * in the Bracket object is fixed at bracket creation time.
 */
 
/**
 * Return an associative array of the available bracket designs
 *
 * @return
 *   the design array - the key is the design code - the value is the design description
 */
function bracket_api_design_list() {
  
  return bracket_design_list();
}
 
/**
 * Check to see if design files exist
 *
 * @param $design
 *   the design name
 * @return
 *   TRUE if design files exist, FALSE if not
 */
function bracket_api_design_exists($design) {

  $result = FALSE;

  $path = bracket_design_info($design);
  $rpath = realpath($path);
  if (file_exists($rpath)) {
    $path = bracket_design_inc($design);
    $rpath = realpath($path);
    if (file_exists($rpath)) {
      $result = TRUE;
    }
  }

  return $result;
}

/**
 * Create a new bracket node
 *
 * @param $title
 *   the bracket title
 * @param $design
 *   the bracket design
 * @return
 *   the bracket node or FALSE if create failed
 */
function bracket_api_create_bracket($title, $design) {
 
  global $user;

  // if current user has access
  if (node_access('create', 'bracket')) {   
  
    // make a new bracket node
    $node = new Bracket();
    
    // add node fields
    $node->type = 'bracket';
    $node->uid = $user->uid;
    $node->title = $title;
    $node->design = $design;
    
    // generate the bracket, make sure the design exists
    if (bracket_design_load($node->design)) {
      // must have a create function
      $function = $node->design . '_create';
      if (function_exists($function)) {
    
        // insert the node, design_create will be called from there
        node_save($node);
        
        // return the new bracket node
        return node_load($node->nid);
      }
    }
  }
  
  return FALSE;  
}

/**
 * Load a bracket node
 *
 * @param $nid
 *   the node id of the bracket node to be loaded
 * @return
 *   the bracket node or FALSE if load failed
 */
function bracket_api_load_bracket($nid) {

  // load the node
  return node_load($nid);
}

/**
 * Update a bracket node
 *
 * @param $node
 *   the bracket node to be updated
 */
function bracket_api_update_bracket($node) {

  // if current user has access
  if (node_access('update', $node)) {   
    // update the node
    node_save($node);
  }
}
 
/**
 * Delete a bracket node
 *
 * @param $nid
 *   the node id of the bracket node to be deleted
 */
function bracket_api_delete_bracket($nid) {

    // delete the node - access is checked in node_delete()
    node_delete($nid);
}

/**
 * get bracket image
 *
 * @param $node
 *   the bracket node
 * @return
 *   the bracket image or FALSE if failure occurrs
 */
function bracket_api_image($node) {

  $function = $node->design . '_image';

  if (function_exists($function)) {

    $args = array($node);
    return call_user_func_array($function, $args);

  }
  
  return FALSE;
}

/**
 * get bracket pdf
 *
 * @param $node
 *   the bracket node
 * @return
 *   the bracket pdf or FALSE if failure occurrs
 */
function bracket_api_pdf($node) {

  $function = $node->design . '_pdf';

  if (function_exists($function)) {

    $args = array($node);
    return call_user_func_array($function, $args);

  }
  
  return FALSE;
}

/**
 * clone a bracket node
 *
 * @param $node
 *   the bracket node to clone
 * @param $title
 *   the title of the new bracket
 * @return
 *   the new bracket node or FALSE if clone failed
 */
function bracket_api_clone_bracket($node, $title) {

  global $user;
  
  // make a new node and copy some info
  $node2 = new Bracket();
  $node2->type = $node->type;
  $node2->uid = $user->uid;
  $node2->comment = $node->comment;
  $node2->title = $title;
  $node2->subtitle = $node->subtitle;
  $node2->comments = $node->comments;
  $node2->sport = $node->sport;
  $node2->division = $node->division;
  $node2->season = $node->season;
  $node2->brgroup = $node->brgroup;
  $node2->footer = $node->footer;
  $node2->logopath = $node->logopath;
  $node2->sponsorlogopath = $node->sponsorlogopath;
  $node2->design = $node->design;
  $node2->options = $node->options;

  // insert the node - default bracket will be generated
  node_save($node2);

  // copy bracket components from source node
  $node2->comp = $node->comp;
  $node2->round = $node->round;
  $node2->result = $node->result;

  // save the completely cloned node
  node_save($node2);
 
  // return the new bracket node
  return node_load($node2->nid);
}

/**
 * Export the bracket as an xml document
 *
 * @param $node
 *   the node object containing the bracket
 * @param $opt
 *   option - 'bracket' = export entire bracket, 'results' = export results only
 * @return
 *   a string containing an XML document representing the bracket
 */
function bracket_api_xml_export($node, $opt = 'bracket') {

  // include xml code
  require_once 'bracket_xml.inc';
  
  // export the bracket
  return bracket_xml_export($node, $opt);
}

/**
 * Import a bracket from an xml document
 *
 * @param $xml
 *   the xml document containing the bracket to import
 * @param $node
 *   the node object to receive the bracket
 * @param $opt
 *   option - 'bracket' = import entire bracket, 'results' = import competitors from results export matching seeds
 * @return 
 *   TRUE if bracket was imported, FALSE if an error occurred
 */
function bracket_api_xml_import($xml, &$node, $opt = 'bracket') {

  // include xml code
  require_once 'bracket_xml.inc';
  
  // import the bracket
  return bracket_xml_string_import($xml, $node, $opt);
}

/**
 * @}
 */

/**
 * @defgroup bracket_comp Bracket Competitor API Functions
 * @{
 * Competitors and seeding
 *
 * Bracket competitors are numbered from 1 to the number of competitors in the bracket.
 * For instance, in an 8 competitor, single-elimination bracket, competitors
 * are numbered from 1 to 8.  Each competitors entry position into the bracket is 
 * fixed.  For this example bracket, competitors 1 and 2 are placed in match 1; 
 * competitors 3 and 4 are placed in match 2, and so on...
 *
 * @code
 *  (Match 1)
 * Competitor 1--+
 *               |-----+ 
 * Competitor 2--+     |
 *                     |
 *                     +------
 *  (Match 2)          |
 * Competitor 3--+     |
 *               |-----+ 
 * Competitor 4--+
 *
 *  (Match 3)
 * Competitor 5--+
 *               |-----+ 
 * Competitor 6--+     |
 *                     |
 *                     +------
 *  (Match 4)          |
 * Competitor 7--+     |
 *               |-----+ 
 * Competitor 8--+
 * @endcode
 *
 * So, in its simpliest form, in order to seed the bracket, competitors are supplied 
 * in a list in the same order as listed on the bracket.
 *
 * However, in order to provide for more seeding arrangements a seeding "key" is also 
 * available for each competitor.  A unique key is assigned each competitor slot.  
 * Using this key, competitors can be assigned to the correct slot by matching the
 * corresponding key.
 */
 
/**
 * Return an associative array of competitors
 *
 * @param $node
 *   the bracket node
 * @return
 *   the array of competitors
 */
function bracket_api_get_competitors($node) {

  $comp = array();
  
  foreach ($node->comp as $ci => $c) {
    $comp[$ci] = array(
      'name' => $c->name,
      'seed' => $c->seedin
    );
  }
  
  return $comp;
}

/**
 * Set the seeding for a competitor
 *
 * @param $node
 *   the bracket node
 * @param $comp_index
 *   the index of the competitor in the bracket
 * @param $seed
 *   the competitor seed key
 * @param $seed_desc
 *   optional - the competitor seed description - stored as the 
 *   competitor comment in the first round of the bracket
 * @return
 *   the array of competitors
 */
function bracket_api_set_seed(&$node, $comp_index, $seed, $seed_desc=FALSE) {

  // make sure competitor index is valid
  if ($comp_index > 0 || $comp_index <= count($node->comp)) {
    // set seed
    $node->comp[$comp_index]->seedin = $seed;
    // set seed description if given
    if ($seed_desc) {
      $r = $node->round[1];
      foreach ($r->match as $m) {
        for ($i=1; $i<=2; $i++) {
          if ($m->compid[$i] == $comp_index) {
            $m->comp_comment[$i] = $seed_desc;
            break;
          }
        }
      }
    }
  }
}

/**
 * Set bracket seeding
 *
 * @param $node
 *   the bracket node
 * @param $seeds
 *   an array of seeding that either contains a list 
 *   of seeds for cooresponding competitors or contains
 *   nested arrays with keys of 'seed' and 'desc' - 
 *   'seed' is the seed key that is used when matching 
 *   competitor seeds. 'desc' is the seed description - 
 *   it is placed in the competitor's match comment slot
 *   in the first round of the bracket.
 */
function bracket_api_set_seeding(&$node, $seeds) {

  $index = 1;
  foreach ($seeds as $seed) {
    // place next competitor
    if (is_array($seed)) {
      $s = '';
      $d = FALSE;
      if (array_key_exists('seed', $seed)) {
         $s = $seed['seed'];  
      }
      if (array_key_exists('desc', $seed)) {
         $d = $seed['desc'];  
      }
      bracket_api_set_seed($node, $index, $s, $d);
    }
    else {
      $node->comp[$index]->seedin = $seed;
    }
    // don't allow any past bracket limit
    if ($index++ == count($node->comp)) {
      break;
    }
  }
}

/**
 * Update bracket competitors
 *
 * @param $node
 *   the bracket node
 * @param $competitors
 *   an array of competitor names - competitors are
 *   placed in the bracket in the same order as given
 */
function bracket_api_set_competitors(&$node, $competitors) {

  $id = 1;
  foreach ($competitors as $comp) {
    // place next competitor
    $node->comp[$id]->name = $comp;
    // don't allow any past bracket limit
    if ($id++ == count($node->comp)) {
      break;
    }
  }
}

/**
 * Seed bracket competitors
 *
 * @param $node
 *   the bracket node
 * @param $comp
 *   an array of competitors where key is seed and value is name
 *   bracket must already contain seed values
 */
function bracket_api_seed_competitors(&$node, $comp) {

  foreach ($comp as $seed => $name) {
    // get seed index
    $i = bracket_api_get_seed_index($node, $seed);
    // set competitor if seed was found
    if ($i > 0) {
      $node->comp[$i]->name = $name;
    }
  }
}

/**
 * Get competitor index with matching seed
 *
 * @param $node
 *   the bracket node
 * @param $seed
 *   the seed key
 * @return
 *   the competitor index or FALSE if seed not found
 */
function bracket_api_get_seed_index(&$node, $seed) {
  
  // find competitor slot with matching seed
  for ($i=1; $i<=count($node->comp); $i++) {
    if ($node->comp[$i]->seedin == $seed) {
      return $i;
    }
  }
  
  // seed not found
  return FALSE;
}

/**
 * Clear bracket competitors
 *
 * @param $node
 *   the bracket node
 */
function bracket_api_clear_competitors(&$node) {

    for ($i=1; $i<=count($node->comp); $i++) {
      $node->comp[$i]->name = '';
    }
}

/**
 * Clear bracket competitor seeding
 *
 * @param $node
 *   the bracket node
 */
function bracket_api_clear_competitor_seeding(&$node) {

    for ($i=1; $i<=count($node->comp); $i++) {
      $node->comp[$i]->seedin = '';
    }
}

/**
 * Locate a competitor by name
 *
 * @param $node
 *   the bracket node
 * @param $name
 *   the competitor name to locate
 * @return
 *   the index or the competitor or FALSE if not found
 */
function bracket_api_locate_competitor($node, $name) {

  foreach ($node->comp as $ci => $c) {
    if ($c->name == $name) {
      return $ci;
    }
  }
  
  return FALSE;
}

/**
 * @}
 */
 
/**
 * @defgroup bracket_round Bracket Round API Functions
 * @{
 * Rounds
 *
 * Bracket matches are organized under rounds.  The number of rounds is
 * established at bracket creation time and is determined by the number
 * of competitors and the type of bracket - which is governed by the 
 * bracket design.  In the case of double-elimination bracket designs, 
 * rounds are separated into winner and loser rounds.
 *
 * An example of round and match indexing:
 *
 * @code
 *  (Winner Rounds)
 *
 *  (Round 1)   (Round 2)   (Round 3)        (Round 4)    (Round 5)
 * -----------+
 *  (Match 1) |-----------+ 
 * -----------+           |
 *              (Match 1) +-----------+
 * -----------+           |           |
 *  (Match 2) |-----------+           |
 * -----------+                       |
 *                          (Match 1) +----------------+
 * -----------+                       |                |  
 *  (Match 3) |-----------+           |                |
 * -----------+           |           |                | 
 *              (Match 2) +-----------+                |
 * -----------+           |                            |
 *  (Match 4) |-----------+                  (Match 1) |--------------+ 
 * -----------+                                        |              |
 *                                                     |              
 *  (Loser Rounds)                                     |              |
 *                                                     |               
 *  (Round 6)   (Round 7)   (Round 8)   (Round 9)      |              |
 *                                     -----------+    |  (Match 1)   + - - - -
 *             -----------+                       |    |              |
 * -----------+ (Match 1) |-----------+ (Match 1) +----+              
 *  (Match 1) |-----------+           |           |                   |
 * -----------+             (Match 1) +-----------+                   
 *             -----------+           |                               |
 * -----------+ (Match 2) |-----------+                 - - - - - - - +
 *  (Match 2) |-----------+           
 * -----------+                       
 * @endcode
 */
 
/**
 * Return an associative array of all rounds in the bracket
 *
 * @param $node
 *   the bracket node
 * @return
 *   the array of rounds
 */
function bracket_api_get_rounds($node) {

  $round = array();
  
  foreach ($node->round as $ri => $r) {
    
    $round[$ri] = bracket_api_get_round($node, $ri);
  }
  
  return $round;
}

/**
 * Return an array containing the information in the round object at the given index
 *
 * @param $node
 *   the bracket node
 * @param $round_index
 *   the index of the round to return
 * @return
 *   an array containing round information or FALSE if round index does not exist
 */
function bracket_api_get_round($node, $round_index) {

  if ($round_index >= 1 && $round_index <= count($node->round)) {
  
    $r = $node->round[$round_index];
  
    $round = array(
      'name' => $r->name,
      'comment' => $r->comment,
      'first' => $r->first,
      'loser' => $r->loser
    );
    
    foreach ($r->match as $mi => $m) {
      $round['match'][$mi] = bracket_api_get_match($node, $round_index, $mi);
    }
    
    return $round;
  }

  return FALSE;
}

/**
 * Locate a round by name
 *
 * @param $node
 *   the bracket node
 * @param $name
 *   the name of the round to locate
 * @return
 *   the index or the round or FALSE if not found
 */
function bracket_api_locate_round($node, $name) {
  
  foreach ($node->round as $ri => $r) {
    if ($r->name == $name) {
      return $ri;
    }
  }
  
  return FALSE;
}

/**
 * Set a round name
 *
 * @param $node
 *   the bracket node
 * @param $index
 *   the round index to update
 * @param $name
 *   the new name of the round
 */
function bracket_api_set_round_name(&$node, $index, $name) {

  if ($index >= 1 && $index <= count($node->round)) {
    $node->round[$index]->name = $name;
  }
}

/**
 * Set a round comment
 *
 * @param $node
 *   the bracket node
 * @param $index
 *   the round index to update
 * @param $comment
 *   the new comment for the round
 */
function bracket_api_set_round_comment(&$node, $index, $comment) {

  if ($index >= 1 && $index <= count($node->round)) {
    $node->round[$index]->comment = $comment;
  }
}

/**
 * @}
 */
 
/**
 * @defgroup bracket_match Bracket Match API Functions
 * @{
 * Matches
 *
 * Bracket matches are organized under bracket rounds, but each match 
 * also has a unique id.  The routing of match winners and losers is
 * established at bracket creation time.
 *
 * An example of match id numbering:
 *
 * @code
 * -----------+
 *  (Match 1) |-----------+ 
 * -----------+           |
 *              (Match 5) +-----------+
 * -----------+           |           |
 *  (Match 2) |-----------+           |
 * -----------+                       |
 *                          (Match 7) +----------------+
 * -----------+                       |                |  
 *  (Match 3) |-----------+           |                |
 * -----------+           |           |                | 
 *              (Match 6) +-----------+                |
 * -----------+           |                            |
 *  (Match 4) |-----------+                  (Match 8) |--------------+ 
 * -----------+                                        |              |
 *                                                     |              
 *                                                     |              |
 *                                                     |               
 *                                                     |              |
 *                                     -----------+    |  (Match 9)   + - - - -
 *             -----------+                       |    |              |
 * -----------+ (Match 12)|-----------+ (Match 15)+----+              
 *  (Match 10)|-----------+           |           |                   |
 * -----------+             (Match 14)+-----------+                   
 *             -----------+           |                               |
 * -----------+ (Match 13)|-----------+                 - - - - - - - +
 *  (Match 11)|-----------+           
 * -----------+                       
 * @endcode
 */
 
/**
 * Return an associative array of all matches in the bracket
 *
 * @param $node
 *   the bracket node
 * @return
 *   the array of matches
 */
function bracket_api_get_matches($node) {

  $match = array();
  
  foreach ($node->round as $ri => $r) {
  
    foreach ($r->match as $mi => $m) {
    
      $match[$m->id] = bracket_api_get_match_by_index($node, $ri, $mi);
    }
  }
  
  return $match;
}

/**
 * Return an array containing the round and match index of the given match id
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the id of the match to return
 * @return
 *   an array containing match indexes (key 'round' contains the round index
 *   and key 'match' contains the  match index) or FALSE if match id does not exist
 */
function bracket_api_get_match_index($node, $matchid) {

  return bracket_round_get_match_index($node, $matchid);
}

/**
 * Return an array containing the information in the match object with the given id
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the id of the match to return
 * @return
 *   an array containing match information or NULL if match id does not exist
 */
function bracket_api_get_match($node, $matchid) {

  if ($mindex = bracket_api_get_match_index($node, $matchid)) {
  
    return bracket_api_get_match_by_index($node, $mindex['round'], $mindex['match']);    
  }
  
  return FALSE;
}

/**
 * Return an array containing the information in the match object at the given index
 *
 * @param $node
 *   the bracket node
 * @param $round_index
 *   the index of the round that contains the match
 * @param $match_index
 *   the index of the match
 * @return
 *   an array containing match information or FALSE if round or match index does not exist
 */
function bracket_api_get_match_by_index($node, $round_index, $match_index) {

  if ($round_index >= 1 && $round_index <= count($node->round)) {
  
    if ($match_index >= 1 && $match_index <= count($node->round[$round_index])) {
  
      $match = array();

      $m = $node->round[$round_index]->match[$match_index];
  
      $match['id'] = $m->id;
        
      for ($i=1; $i<=2; $i++) {
          
        $match['comment'][$i] = $m->comment[$i];
            
        $match['competitor'][$i]['comment'] = $m->comp_comment[$i];
        $match['competitor'][$i]['id'] = $m->compid[$i];
        if ($m->compid[$i] != 0) {
          $match['competitor'][$i]['name'] = $node->comp[$m->compid[$i]]->name;
          $match['competitor'][$i]['seed'] = $node->comp[$m->compid[$i]]->seedin;
        }
        else {
          $match['competitor'][$i]['name'] = '';
          $match['competitor'][$i]['seed'] = '';
        }
        $match['competitor'][$i]['score'] = $m->score[$i];
        $match['competitor'][$i]['home'] = $m->home[$i];
        $match['competitor'][$i]['win'] = $m->win[$i];
      }
    
      return $match;
    }
  }
  
  return FALSE;
}

/**
 * Set a match comment
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the match id to update
 * @param $comment_index
 *   the comment index that should be updated (1 or 2)
 * @param $comment
 *   the new comment for the match
 */
function bracket_api_set_match_comment(&$node, $matchid, $comment_index, $comment) {

  if (($mindex = bracket_api_get_match_index($node, $matchid)) && $comment_index >= 1 && $comment_index <= 2) {
    $node->round[$mindex['round']]->match[$mindex['match']]->comment[$comment_index] = $comment;
  }
}

/**
 * Set a match competitor comment
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the match id to update
 * @param $comp_index
 *   the competitor index that should be updated (1 or 2)
 * @param $comment
 *   the new comment for the competitor
 */
function bracket_api_set_match_competitor_comment(&$node, $matchid, $comp_index, $comment) {

  if (($mindex = bracket_api_get_match_index($node, $matchid)) && $comp_index >= 1 && $comp_index <= 2) {
    $node->round[$mindex['round']]->match[$mindex['match']]->comp_comment[$comp_index] = $comment;
  }
}

/**
 * Set a match home competitor 
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the match id to update
 * @param $comp_index
 *   the competitor index that should be updated (1 or 2)
 */
function bracket_api_set_match_home_competitor(&$node, $matchid, $comp_index) {

  if (($mindex = bracket_api_get_match_index($node, $matchid)) && $comp_index >= 1 && $comp_index <= 2) {
    $node->round[$mindex['round']]->match[$mindex['match']]->home[$comp_index] = TRUE;
    $index = ($comp_index == 1) ? 2 : 1;
    $node->round[$mindex['round']]->match[$mindex['match']]->home[$index] = FALSE;
  }
}

/**
 * Set a match winner 
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the match id to update
 * @param $winner_index
 *   the competitor index that should be indicated as the winner (1 or 2)
 *   or 0 to reset results
 * @param $winner_score
 *   the winning score of the match (optional)
 * @param $loser_score
 *   the losing score of the match (optional)
 */
function bracket_api_set_match_winner(&$node, $matchid, $winner_index, $winner_score='', $loser_score='') {

  if ($mindex = bracket_api_get_match_index($node, $matchid)) {
  
    // get match
    $m = $node->round[$mindex['round']]->match[$mindex['match']];

    // save previous win flags
    $win1 = $m->win[1];
    $win2 = $m->win[2];
        
    // reset results if index = 0    
    if ($winner_index == 0) {

      $m->win[1] = FALSE;
      $m->win[2] = FALSE;
      
      $m->score[1] = '';
      $m->score[2] = '';
      
      $wcompid = 0;
      $lcompid = 0;
    }
    
    // set match winner
    if ($winner_index >= 1 && $winner_index <= 2) {

      // winning competitor must be set
      if ($m->win[$winner_index] && $m->compid[$winner_index] == 0) {
        return;
      }

      // update match winner flags
      $m->win[$winner_index] = TRUE;
      $loser_index = ($winner_index == 1) ? 2 : 1;
      $m->win[$loser_index] = FALSE;
      
      $m->score[$winner_index] = $winner_score;
      $m->score[$loser_index] = $loser_score;
  
      $wcompid = $m->compid[$winner_index];    
      $lcompid = $m->compid[$loser_index];   
    }
      
    // route to results
    if ($m->winner_result > 0 || $m->loser_result > 0) {
    
      // clear previous results
      if ($m->winner_result > 0) {
        $node->result[$m->winner_result]->compid = 0;
      }
      if ($m->loser_result > 0) {
        $node->result[$m->loser_result]->compid = 0;
      }

      // make sure it is appropriate
      if ($m->win_use_result == 0 || ($m->win_use_result > 0 && $m->win[$m->win_use_result])) {

        // place winner
        if ($m->winner_result > 0) {
          $node->result[$m->winner_result]->compid = $wcompid;
          }
        // place loser
        if ($m->loser_result > 0) {
          $node->result[$m->loser_result]->compid = $lcompid;
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

            // propogate competitor through the rest of the tree
            bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->winner_comp);
          }
        } // end - if ($m->winner_match > 0 && $m->winner_comp > 0)...

        // route loser
        if ($m->loser_match > 0 && $m->loser_comp > 0) {

          if ($mindex = bracket_round_get_match_index($node, $m->loser_match)) {

            $m2 = $node->round[$mindex['round']]->match[$mindex['match']];
            $m2->compid[$m->loser_comp] = $lcompid;

            bracket_round_check_tree($node, $mindex['round'], $mindex['match'], $m->loser_comp);
          }
        }   // end - if ($m->loser_match > 0 && $m->loser_comp > 0)...
        
      }   // end - if ($m->win_use_result == 0 || ($m->win_use_result > 0 && !$m->win[$m->win_use_result])...
      
    }   // end - if ($m->winner_match > 0 || $m->loser_match > 0)...
    
  }   // end -   if ($mindex = bracket_api_get_match_index($node, $matchid))...
  
}

/**
 * Get a match competitor index given competitor name
 *
 * @param $node
 *   the bracket node
 * @param $matchid
 *   the match id to search
 * @param $comp_name
 *   the competitor name to location
 * @return
 *   the index of the competitor in the given match or FALSE if competitor was not found
 */
function bracket_api_locate_match_competitor($node, $matchid, $comp_name) {

  if ($mindex = bracket_api_get_match_index($node, $matchid)) {
    for ($i=1; $i<=2; $i++) {
      $compid = $node->round[$mindex['round']]->match[$mindex['match']]->compid[$i];
      if ($compid > 0) {
        $cname = $node->comp[$compid]->name;
        if ($cname == $comp_name) {
          return $i;  
        }
      }
    }
  }
  return FALSE;
}

/**
 * Clear bracket results
 *
 * @param $node
 *   the bracket node
 */
function bracket_api_clear_results(&$node) {

  // clear match results
  for ($i=1; $i<=count($node->round); $i++) {
    for ($j=1; $j<=count($node->round[$i]->match); $j++) {
      for ($k=1; $k<=2; $k++) {
        $node->round[$i]->match[$j]->win[$k] = FALSE;
        $node->round[$i]->match[$j]->score[$k] = '';
      }
    }
  }
  // clear results
  for ($i=1; $i<=count($node->result); $i++) {
    $node->result[$i]->compid = 0;
  }
}

/**
 * @} 
 */
 
/**
 * @defgroup bracket_result Bracket Result API Functions
 * @{
 * Results
 *
 * Bracket results contain the ultimate winner and runner(s)-up of the bracket.
 * They are updated by the results of the final round(s).
 */
 
/**
 * Return an associative array of all bracket results
 *
 * @param $node
 *   the bracket node
 * @return
 *   the array of results
 */
function bracket_api_get_results($node) {

  $result = array();
  
  foreach ($node->result as $ri => $r) {

    $cname = '';
    if ($r->compid > 0) {
      $cname = $node->comp[$r->compid]->name;
    }
    
    $result[$ri] = array(
      'compid' => $r->compid,
      'cname' => $cname,
      'comment' => $r->comment,
      'seedout' => $r->seedout
    );
  }
  
  return $result;
}

/**
 * Set a result comment
 *
 * @param $node
 *   the bracket node
 * @param $result_index
 *   the result index that should be updated
 * @param $comment
 *   the new comment for the round
 */
function bracket_api_set_result_comment(&$node, $result_index, $comment) {

  if ($result_index >= 1 && $result_index <= count($node->result)) {
    $node->result[$result_index]->comment = $comment;
  }
}

/**
 * @} 
 */



