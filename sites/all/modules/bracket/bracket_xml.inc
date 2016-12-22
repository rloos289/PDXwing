<?php

/**
 * @file
 * This file contains the xml helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */


/**
 * Format the bracket as an xml document
 *
 * @param $node
 *   the node object containing the bracket
 * @param $opt
 *   option - 'bracket' = export entire bracket, 'results' = export results only
 * @return
 *   a string containing an XML document representing the bracket
 */
function bracket_xml_export($node, $opt = 'bracket') {

  $output = '<?xml version="1.0"?>' . "\n";
  $output .= "<bracket>\n";

  // export bracket info
  $output .= '  <title>' . check_plain($node->title) . '</title>' . "\n";
  $output .= '  <subtitle>' . check_plain($node->subtitle) . '</subtitle>' . "\n";
  $output .= '  <comments>' . check_plain($node->comments) . '</comments>' . "\n";
  $output .= '  <sport>' . check_plain($node->sport) . '</sport>' . "\n";
  $output .= '  <division>' . check_plain($node->division) . '</division>' . "\n";
  $output .= '  <season>' . check_plain($node->season) . '</season>' . "\n";
  $output .= '  <brgroup>' . check_plain($node->brgroup) . '</brgroup>' . "\n";
  $output .= '  <footer>' . check_plain($node->footer) . '</footer>' . "\n";
  $output .= '  <logopath>' . $node->logopath . '</logopath>' . "\n";
  $output .= '  <sponsorlogopath>' . $node->sponsorlogopath . '</sponsorlogopath>' . "\n";
  $output .= '  <design>' . $node->design . '</design>' . "\n";
  $output .= '  <display>' . $node->options['display'] . '</display>' . "\n";
  $output .= '  <hide_pdf>' . $node->options['hide_pdf'] . '</hide_pdf>' . "\n";
  $output .= '  <show_match_id>' . $node->options['show_match_id'] . '</show_match_id>' . "\n";
  $output .= '  <fg_color>' . $node->options['image_options']['fg_color'] . '</fg_color>' . "\n";
  $output .= '  <bg_color>' . $node->options['image_options']['bg_color'] . '</bg_color>' . "\n";
  $output .= '  <show_bracket_bar>' . $node->options['image_options']['show_bracket_bar'] . '</show_bracket_bar>' . "\n";
  $output .= '  <bar_fg_color>' . $node->options['image_options']['bar_fg_color'] . '</bar_fg_color>' . "\n";
  $output .= '  <bar_bg_color>' . $node->options['image_options']['bar_bg_color'] . '</bar_bg_color>' . "\n";
  $output .= '  <image_font>' . $node->options['image_options']['image_fonts']['image_font'] . '</image_font>' . "\n";
  $output .= '  <image_font_bold>' . $node->options['image_options']['image_fonts']['image_font_bold'] . '</image_font_bold>' . "\n";
  $output .= '  <image_font_italic>' . $node->options['image_options']['image_fonts']['image_font_italic'] . '</image_font_italic>' . "\n";
  $output .= '  <image_font_bolditalic>' . $node->options['image_options']['image_fonts']['image_font_bolditalic'] . '</image_font_bolditalic>' . "\n";
  $output .= '  <pdf_font>' . $node->options['image_options']['pdf_font'] . '</pdf_font>' . "\n";

  // export competitors
  for ($i=1; $i<=count($node->comp); $i++) {
    $output .= '  <competitor id="' . $i . '">' . "\n";
    $output .= '    <name>' . check_plain($node->comp[$i]->name) . '</name>' . "\n";
    $output .= '    <seedin>' . check_plain($node->comp[$i]->seedin) . '</seedin>' . "\n";
    $output .= "  </competitor>\n";
  }

  if ($opt == 'bracket') {

    // export rounds
    for ($i=1; $i<=count($node->round); $i++) {
      $r = $node->round[$i];
      $output .= '  <round id="' . $i . '">' . "\n";
      $output .= '    <name>' . check_plain($r->name) . '</name>' . "\n";
      $output .= '    <loser>' . $r->loser . '</loser>' . "\n";
      $output .= '    <comment>' . check_plain($r->comment) . '</comment>' . "\n";

      // export matches
      for ($j=1; $j<=count($r->match); $j++) {
        $m = $r->match[$j];
        $output .= '    <match seq="' . $j . '">' . "\n";
        $output .= '      <id>' . $m->id . '</id> ' . "\n";
        $output .= '      <comment1>' . check_plain($m->comment[1]) . '</comment1>' . "\n";
        $output .= '      <comment2>' . check_plain($m->comment[2]) . '</comment2>' . "\n";
        $output .= '      <winner_match>' . $m->winner_match . '</winner_match>' . "\n";
        $output .= '      <winner_comp>' . $m->winner_comp . '</winner_comp>' . "\n";
        $output .= '      <loser_match>' . $m->loser_match . '</loser_match>' . "\n";
        $output .= '      <loser_comp>' . $m->loser_comp . '</loser_comp>' . "\n";
        $output .= '      <winner_result>' . $m->winner_result . '</winner_result>' . "\n";
        $output .= '      <loser_result>' . $m->loser_result . '</loser_result>' . "\n";
        $output .= '      <win_use_result>' . $m->win_use_result . '</win_use_result>' . "\n";
        for ($k=1; $k<=2; $k++) {
          $output .= '      <match-competitor id="' . $k . '"> ' . "\n";
          $output .= '        <compid>' . $m->compid[$k] . '</compid>' . "\n";
          $output .= '        <comp_comment>' . check_plain($m->comp_comment[$k]) . '</comp_comment>' . "\n";
          $output .= '        <score>' . check_plain($m->score[$k]) . '</score>' . "\n";
          $output .= '        <home>' . $m->home[$k] . '</home>' . "\n";
          $output .= '        <win>' . $m->win[$k] . '</win>' . "\n";
          $output .= '      </match-competitor> ' . "\n";
        }
        $output .= "    </match>\n";
      }
      $output .= "  </round>\n";
    }
  }

  // export results
  for ($i=1; $i<=count($node->result); $i++) {
    $s = $node->result[$i];
    $output .= '  <result place="' . $i . '">' . "\n";
    $output .= '    <compid>' . $s->compid . '</compid>' . "\n";
    $output .= '    <comment>' . check_plain($s->comment) . '</comment>' . "\n";
    $output .= '    <seedout>' . check_plain($s->seedout) . '</seedout>' . "\n";
    $output .= "  </result>\n";
  }

  $output .= "</bracket>\n";

  return $output;
}

/**
 * Import a bracket from an xml document
 *
 * @param $path
 *   the path to the xml document
 * @param $node
 *   the node object to receive the bracket
 * @param $opt
 *   option - 'bracket' = import entire bracket, 'results' = import competitors from results export matching seeds
 * @return 
 *   TRUE if bracket was imported, FALSE if an error occurred
 */
function bracket_xml_import($file, &$node, $opt = 'bracket') {

  // read the contents of the file
  $xml = file_get_contents($file->uri);
  // do the import
  return bracket_xml_string_import($xml, $node, $opt);
}

/**
 * Import a bracket from an xml string
 *
 * @param $xml
 *   the xml document to import
 * @param $node
 *   the node object to receive the bracket
 * @param $opt
 *   option - 'bracket' = import entire bracket, 'results' = import competitors from results export matching seeds
 * @return 
 *   TRUE if bracket was imported, FALSE if an error occurred
 */
function bracket_xml_string_import($xml, &$node, $opt = 'bracket') {

  // parse the xml
  $parser = xml_parser_create();
  xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
  xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);

  $ok = xml_parse_into_struct($parser, $xml, $values, $tags);
  xml_parser_free($parser);

  if ($ok) {

    if ($opt == 'bracket') {
      bracket_xml_import_bracket($node, $values);
    }
    elseif ($opt == 'results') {
      bracket_xml_import_results($node, $values);
    }

    return TRUE;
  }   // end - if ($ok)...

  else {
    return FALSE;
  }
}

/**
 * Import a complete bracket
 *
 * @param $node
 *   the node object to receive the bracket
 * @param $values
 *   the values from xml_parse_into_struct()
 */
function bracket_xml_import_bracket(&$node, $values) {

  // init stack to hold current open tag
  $stack = array();
  $otag = '';

  // init variable to hold certain values during the xml parse
  $c = NULL;
  $r = NULL;
  $m = NULL;
  $s = NULL;
  $mcid = 0;

  // iterate through values
  foreach ($values as $e) {

    // open tag - set the current open object
    if ($e['type'] == 'open') {

      $tag = $e['tag'];
      if ($tag == 'competitor') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['id'];
        $c = $node->comp[$id];
      }

      elseif ($tag == 'round') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['id'];
        $r = $node->round[$id];
        $r->id = $id;
      }

      elseif ($tag == 'match') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['seq'];
        if ($r != NULL) {
          $m = $r->match[$id];
        }
      }

      elseif ($tag == 'match-competitor') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $mcid = $e['attributes']['id'];
      }

      elseif ($tag == 'result') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['place'];
        $s = $node->result[$id];
      }

      else {
        continue;
      }
    }   // end - if ($e['type'] == 'open')...

    // complete tag - set a value
    elseif ($e['type'] == 'complete' && array_key_exists('value', $e)) {

      $tag = $e['tag'];

      if ($tag == 'subtitle') {
        $node->subtitle = $e['value'];
      }

      elseif ($tag == 'comments') {
        $node->comments = $e['value'];
      }

      elseif ($tag == 'sport') {
        $node->sport = $e['value'];
      }

      elseif ($tag == 'division') {
        $node->division = $e['value'];
      }

      elseif ($tag == 'season') {
        $node->season = $e['value'];
      }

      elseif ($tag == 'brgroup') {
        $node->brgroup = $e['value'];
      }

      elseif ($tag == 'footer') {
        $node->footer = $e['value'];
      }

      elseif ($tag == 'logopath') {
        $node->logopath = $e['value'];
      }

      elseif ($tag == 'sponsorlogopath') {
        $node->sponsorlogopath = $e['value'];
      }

      elseif ($tag == 'design') {
        $d = $e['value'];
        if ($node->design != $d) {
          drupal_set_message(t('Imported bracket design - @d - does not match current bracket design - @c.
                                Bracket could not be imported.',
                               array('@d' => $d, '@c' => $node->design)), 'error');
          return;
        }
      }

      elseif ($tag == 'show_match_id') {
        $node->options['show_match_id'] = $e['value'];
      }

      elseif ($tag == 'display') {
        $node->options['display'] = $e['value'];
      }

      elseif ($tag == 'hide_pdf') {
        $node->options['hide_pdf'] = $e['value'];
      }

      elseif ($tag == 'fg_color') {
        $node->options['image_options']['fg_color'] = $e['value'];
      }

      elseif ($tag == 'bg_color') {
        $node->options['image_options']['bg_color'] = $e['value'];
      }

      elseif ($tag == 'show_bracket_bar') {
        $node->options['image_options']['show_bracket_bar'] = $e['value'];
      }

      elseif ($tag == 'bar_fg_color') {
        $node->options['image_options']['bar_fg_color'] = $e['value'];
      }

      elseif ($tag == 'bar_bg_color') {
        $node->options['image_options']['bar_bg_color'] = $e['value'];
      }

      elseif ($tag == 'image_font') {
        $node->options['image_options']['image_fonts']['image_font'] = $e['value'];
      }

      elseif ($tag == 'image_font_bold') {
        $node->options['image_options']['image_fonts']['image_font_bold'] = $e['value'];
      }

      elseif ($tag == 'image_font_italic') {
        $node->options['image_options']['image_fonts']['image_font_italic'] = $e['value'];
      }

      elseif ($tag == 'image_font_bolditalic') {
        $node->options['image_options']['image_fonts']['image_font_bolditalic'] = $e['value'];
      }

      elseif ($tag == 'pdf_font') {
        $node->options['image_options']['pdf_font'] = $e['value'];
      }

      elseif ($tag == 'id') {
        if ($otag == 'match' && $m != NULL) {
          $m->id = $e['value'];
        }
      }
      
      elseif ($tag == 'name') {
        if ($otag == 'competitor' && $c != NULL) {
          $c->name = $e['value'];
        }
        if ($otag == 'round' && $r != NULL) {
          $r->name = $e['value'];
        }
      }

      elseif ($tag == 'seedin') {
        if ($otag == 'competitor' && $c != NULL) {
          $c->seedin = $e['value'];
        }
      }

      elseif ($tag == 'seedout') {
        if ($otag == 'result' && $s != NULL) {
          $s->seedout = $e['value'];
        }
      }

      elseif ($tag == 'loser') {
        if ($otag == 'round' && $r != NULL) {
          $r->loser = $e['value'];
        }
      }

      elseif ($tag == 'comment') {
        if ($otag == 'round' && $r != NULL) {
          $r->comment = $e['value'];
        }
        if ($otag == 'result' && $s != NULL) {
          $s->comment = $e['value'];
        }
      }

      elseif ($tag == 'comment1') {
        if ($otag == 'match' && $m != NULL) {
          $m->comment[1] = $e['value'];
        }
      }

      elseif ($tag == 'comment2') {
        if ($otag == 'match' && $m != NULL) {
          $m->comment[2] = $e['value'];
        }
      }

      elseif ($tag == 'compid') {
        if ($otag == 'match-competitor' && $m != NULL && $mcid > 0) {
          $m->compid[$mcid] = $e['value'];
        }
        if ($otag == 'result' && $s != NULL) {
          $s->compid = $e['value'];
        }
      }

      elseif ($tag == 'comp_comment') {
        if ($otag == 'match-competitor' && $m != NULL && $mcid > 0) {
          $m->comp_comment[$mcid] = $e['value'];
        }
      }

      elseif ($tag == 'score') {
        if ($otag == 'match-competitor' && $m != NULL && $mcid > 0) {
          $m->score[$mcid] = $e['value'];
        }
      }

      elseif ($tag == 'win') {
        if ($otag == 'match-competitor' && $m != NULL && $mcid > 0) {
          $m->win[$mcid] = $e['value'];
        }
      }

      elseif ($tag == 'home') {
        if ($otag == 'match-competitor' && $m != NULL && $mcid > 0) {
          $m->home[$mcid] = $e['value'];
        }
      }

      elseif ($tag == 'winner_match') {
        if ($otag == 'match' && $m != NULL) {
          $m->winner_match = $e['value'];
        }
      }

      elseif ($tag == 'winner_comp') {
        if ($otag == 'match' && $m != NULL) {
          $m->winner_comp = $e['value'];
        }
      }

      elseif ($tag == 'loser_match') {
        if ($otag == 'match' && $m != NULL) {
          $m->loser_match = $e['value'];
        }
      }

      elseif ($tag == 'loser_comp') {
        if ($otag == 'match' && $m != NULL) {
          $m->loser_comp = $e['value'];
        }
      }

      elseif ($tag == 'winner_result') {
        if ($otag == 'match' && $m != NULL) {
          $m->winner_result = $e['value'];
        }
      }

      elseif ($tag == 'loser_result') {
        if ($otag == 'match' && $m != NULL) {
          $m->loser_result = $e['value'];
        }
      }

      elseif ($tag == 'win_use_result') {
        if ($otag == 'match' && $m != NULL) {
          $m->win_use__result = $e['value'];
        }
      }

      else {
        continue;
      }
    }   // end - elseif ($e['type'] == 'complete')...

    // close the open object and pop the previous open object
    elseif ($e['type'] == 'close') {

      $tag = $e['tag'];

      if ($tag == 'competitor') {
        $otag = array_pop($stack);
        $c = NULL;
      }

      elseif ($tag == 'round') {
        $otag = array_pop($stack);
        $r = NULL;
      }

      elseif ($tag == 'match') {
        $otag = array_pop($stack);
        $m = NULL;
      }

      elseif ($tag == 'match-competitor') {
        $otag = array_pop($stack);
        $mcid = 0;
      }

      elseif ($tag == 'result') {
        $otag = array_pop($stack);
        $s = NULL;
      }

      else {
        continue;
      }
    }   // end - elseif ($e['type'] == 'close')...

    else {
      continue;
    }
  }   // end - foreach ($values as $e)...
}

/**
 * Import bracket results matching seeds
 *
 * @param $node
 *   the node object to receive the bracket
 * @param $values
 *   the values from xml_parse_into_struct()
 */
function bracket_xml_import_results(&$node, $values) {

  // init stack to hold current open tag
  $stack = array();
  $otag = '';

  // create a temporary bracket to hold imported results
  $b = new Bracket();

  // init variable to hold certain values during the xml parse
  $c = NULL;
  $s = NULL;

  // iterate through values
  foreach ($values as $e) {

    // open tag - set the current open object
    if ($e['type'] == 'open') {

      $tag = $e['tag'];

      if ($tag == 'competitor') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['id'];
        $c = new Bracket_Competitor();
        $b->comp[$id] = $c;
      }

      elseif ($tag == 'result') {
        if ($otag) array_push($stack, $otag);
        $otag = $tag;
        $id = $e['attributes']['place'];
        $s = new Bracket_Result();
        $b->result[$id] = $s;
      }

      else {
        continue;
      }
    }   // end - if ($tag == 'competitor')...

    // complete tag - set a value
    elseif ($e['type'] == 'complete') {

      $tag = $e['tag'];

      if ($tag == 'name') {
        if ($otag == 'competitor' && $c != NULL) {
          $c->name = $e['value'];
        }
      }

      elseif ($tag == 'compid') {
        if ($otag == 'result' && $s != NULL) {
          $s->compid = $e['value'];
        }
      }

      elseif ($tag == 'seedout') {
        if ($otag == 'result' && $s != NULL) {
          $s->seedout = $e['value'];
        }
      }

      else {
        continue;
      }
    }   // end - elseif ($e['type'] == 'complete')...

    // close the open object and pop the previous open object
    elseif ($e['type'] == 'close') {

      $tag = $e['tag'];

      if ($tag == 'competitor') {
        $otag = array_pop($stack);
        $c = NULL;
      }

      elseif ($tag == 'result') {
        $otag = array_pop($stack);
        $s = NULL;
      }

      else {
        continue;
      }
    }   // end - elseif ($e['type'] == 'close')...

    else {
      continue;
    }
  }   // end - foreach ($values as $e)...

  // now match seedouts to seedins in the given node
  for ($i=1; $i<=count($b->result); $i++) {
    $s = $b->result[$i];
    // try to find matching seedin in competitors
    for ($j=1; $j<=count($node->comp); $j++) {
      $c = $node->comp[$j];
      // if match
      if ($s->seedout == $c->seedin) {
        // get seedout competitor
        $c2 = $b->comp[$s->compid];
        $c->name = $c2->name;
        break;
      }
    }
  }
}