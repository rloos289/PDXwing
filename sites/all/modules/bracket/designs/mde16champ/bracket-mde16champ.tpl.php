<?php
// $Id:

/**
 * @file
 * Template for mde16champ bracket design
 *
 * Available variables:
 * - $node: The node object for the bracket to be rendered.
 */
drupal_add_css(drupal_get_path('module', 'bracket') . '/designs/mde16champ/bracket-mde16champ.css', array('preprocess' => FALSE));
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
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 4, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 5, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 6, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 7, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 8, 'orientation' => 'left')) ?>
    <div id="round-1-loser-round-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-5-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-5-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-5-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 4, 'orientation' => 'left')) ?>
    <div class="bracket-footer"><?php print nl2br(filter_xss_admin($node->footer)) ?></div>
  </div>
  <div id="round-2" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[2]->comment ? filter_xss_admin($node->round[2]->comment) : '&nbsp;' ?></div>
    <div id="round-2-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 4, 'orientation' => 'left')) ?>
    <div id="round-2-loser-round-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 6, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-6-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 6, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-6-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 6, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-6-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 6, 'match_index' => 4, 'orientation' => 'left')) ?>
  </div>
  <div id="round-3" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[3]->comment ? filter_xss_admin($node->round[3]->comment) : '&nbsp;' ?></div>
    <div id="round-3-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div id="round-3-loser-round-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 7, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-7-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 7, 'match_index' => 2, 'orientation' => 'left')) ?>
  </div>
  <div id="round-4" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[4]->comment ? filter_xss_admin($node->round[4]->comment) : '&nbsp;' ?></div>
    <div id="round-4-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div id="round-4-loser-round-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 8, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-8-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 8, 'match_index' => 2, 'orientation' => 'left')) ?>
  </div>
  <div id="round-9" class="bracket-round">
    <div id="results-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-result-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 2, 'orientation' => 'left')) ?>
    <div id="round-9-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 9, 'match_index' => 1, 'orientation' => 'left')) ?>
  </div>
  <div id="loser-results" class="bracket-results bracket-results-left">
    <div id="loser-results-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-result-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 4, 'orientation' => 'left')) ?>
  </div>
  <?php print theme('bracket_images', array('node' => $node)) ?>
</div>

