<?php
// $Id:

/**
 * @file
 * Template for se16po1 bracket design
 *
 * Available variables:
 * - $node: The node object for the bracket to be rendered.
 */
drupal_add_css(drupal_get_path('module', 'bracket') . '/designs/se16po1/bracket-se16po1.css', array('preprocess' => FALSE));
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
    <div class="bracket-footer"><?php print nl2br(filter_xss_admin($node->footer)) ?></div>
  </div>
  <div id="results" class="bracket-results bracket-results-left">
    <div id="results-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 1, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 2, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 3, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 4, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 5, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 6, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 7, 'orientation' => 'left')) ?>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 8, 'orientation' => 'left')) ?>
  </div>
  <?php print theme('bracket_images', array('node' => $node)) ?>
</div>

