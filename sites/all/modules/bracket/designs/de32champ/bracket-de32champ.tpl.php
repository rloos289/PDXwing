<?php
// $Id:

/**
 * @file
 * Template for de32champ bracket design
 *
 * Available variables:
 * - $node: The node object for the bracket to be rendered.
 */
drupal_add_css(drupal_get_path('module', 'bracket') . '/designs/de32champ/bracket-de32champ.css', array('preprocess' => FALSE));
?>

<div class="bracket-block">
  <?php if ($node->subtitle) { ?>
  <div class="bracket-subtitle"><?php print filter_xss_admin($node->subtitle) ?></div>
  <?php } ?>
  <?php if ($node->comments) { ?>
  <div class="bracket-comments"><?php print nl2br(filter_xss_admin($node->comments)) ?></div>
  <?php } ?>
  <div id="round-1" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[1]->comment ? filter_xss_admin($node->round[1]->comment) : '&nbsp;' ?></div>
    <div id="round-1-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[1]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[1]->match)) print '<div class="bracket-round-1-match-spacer"></div>';
    } ?>
    <div id="round-1-loser-round-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[8]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 8, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[8]->match)) print '<div class="bracket-round-8-match-spacer"></div>';
    } ?>
    <div class="bracket-footer"><?php print nl2br(filter_xss_admin($node->footer)) ?></div>
  </div>
  <div id="round-2" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[2]->comment ? filter_xss_admin($node->round[2]->comment) : '&nbsp;' ?></div>
    <div id="round-2-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[2]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[2]->match)) print '<div class="bracket-round-2-match-spacer"></div>';
    } ?>
    <div id="round-2-loser-round-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[9]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 9, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[9]->match)) print '<div class="bracket-round-9-match-spacer"></div>';
    } ?>
  </div>
  <div id="round-3" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[3]->comment ? filter_xss_admin($node->round[3]->comment) : '&nbsp;' ?></div>
    <div id="round-3-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[3]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[3]->match)) print '<div class="bracket-round-3-match-spacer"></div>';
    } ?>
    <div id="round-3-loser-round-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[10]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 10, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[10]->match)) print '<div class="bracket-round-10-match-spacer"></div>';
    } ?>
  </div>
  <div id="round-4" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[4]->comment ? filter_xss_admin($node->round[4]->comment) : '&nbsp;' ?></div>
    <div id="round-4-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[4]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[4]->match)) print '<div class="bracket-round-4-match-spacer"></div>';
    } ?>
    <div id="round-4-loser-round-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[11]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 11, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[11]->match)) print '<div class="bracket-round-11-match-spacer"></div>';
    } ?>
  </div>
  <div id="round-5" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[5]->comment ? filter_xss_admin($node->round[5]->comment) : '&nbsp;' ?></div>
    <div id="round-5-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 1, 'orientation' => 'left')); ?>
    <div id="round-5-loser-round-spacer"></div>
    <?php for ($i=1; $i<=count($node->round[12]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 12, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[12]->match)) print '<div class="bracket-round-12-match-spacer"></div>';
    } ?>
  </div>
  <div id="round-13" class="bracket-round">
    <div class="bracket-round-comment">&nbsp;</div>
    <div id="round-6-spacer"></div>
    <div class="bracket-match">
      <div class="bracket-match-competitor-block">
        <div class="bracket-match-competitor bracket-match-competitor-left">&nbsp;</div>
      </div>
      <div id="round-13-loser-round-spacer" class="bracket-match-block"></div>
    </div>
    <?php for ($i=1; $i<=count($node->round[13]->match); $i++) {
        print theme('bracket_match', array('node' => $node, 'round_index' => 13, 'match_index' => $i, 'orientation' => 'left'));
        if ($i < count($node->round[13]->match)) print '<div class="bracket-round-13-match-spacer"></div>';
    } ?>
  </div>
  <div id="round-14" class="bracket-round">
    <div class="bracket-round-comment">&nbsp;</div>
    <div id="round-6-spacer"></div>
    <div class="bracket-match">
      <div class="bracket-match-competitor-block">
        <div class="bracket-match-competitor bracket-match-competitor-left">&nbsp;</div>
      </div>
      <div id="round-14-loser-round-spacer" class="bracket-match-block"></div>
    </div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 14, 'match_index' => 1, 'orientation' => 'left')); ?>
  </div>
  <div id="round-15" class="bracket-round">
    <div class="bracket-round-comment">&nbsp;</div>
    <div id="round-6-spacer"></div>
    <div class="bracket-match">
      <div class="bracket-match-competitor-block">
        <div class="bracket-match-competitor bracket-match-competitor-left">&nbsp;</div>
      </div>
      <div id="round-15-loser-round-spacer" class="bracket-match-block"></div>
    </div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 15, 'match_index' => 1, 'orientation' => 'left')); ?>
  </div>
  <div id="round-6" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[6]->comment ? filter_xss_admin($node->round[6]->comment) : '&nbsp;' ?></div>
    <div id="round-6-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 6, 'match_index' => 1, 'orientation' => 'left')); ?>
  </div>
  <div id="round-7" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[7]->comment ? filter_xss_admin($node->round[7]->comment) : '&nbsp;' ?></div>
    <div id="round-7-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 7, 'match_index' => 1, 'orientation' => 'left')); ?>
  </div>
  <div id="results" class="bracket-results bracket-results-left">
    <div id="results-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-result-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 2, 'orientation' => 'left')) ?>
  </div>
  <?php print theme('bracket_images', array('node' => $node)) ?>
</div>

