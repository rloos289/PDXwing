<?php
// $Id:

/**
 * @file
 * Template for se64champlr bracket design
 *
 * Available variables:
 * - $node: The node object for the bracket to be rendered.
 */
drupal_add_css(drupal_get_path('module', 'bracket') . '/designs/se64champlr/bracket-se64champlr.css', array('preprocess' => FALSE));
?>

<div class="bracket-block">
  <?php if ($node->subtitle) { ?>
  <div class="bracket-subtitle"><?php print filter_xss_admin($node->subtitle) ?></div>
  <?php } ?>
  <?php if ($node->comments) { ?>
  <div class="bracket-comments"><?php print nl2br(filter_xss_admin($node->comments)) ?></div>
  <?php } ?>
  <div id="round-1-left" class="bracket-round">
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
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 9, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 10, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 11, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 12, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 13, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 14, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 15, 'orientation' => 'left')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 16, 'orientation' => 'left')) ?>
    <div class="bracket-footer"><?php print nl2br(filter_xss_admin($node->footer)) ?></div>
  </div>
  <div id="round-2-left" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[2]->comment ? filter_xss_admin($node->round[2]->comment) : '&nbsp;' ?></div>
    <div id="round-2-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 4, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 5, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 6, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 7, 'orientation' => 'left')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 8, 'orientation' => 'left')) ?>
  </div>
  <div id="round-3-left" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[3]->comment ? filter_xss_admin($node->round[3]->comment) : '&nbsp;' ?></div>
    <div id="round-3-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 2, 'orientation' => 'left')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 3, 'orientation' => 'left')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 4, 'orientation' => 'left')) ?>
  </div>
  <div id="round-4-left" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[4]->comment ? filter_xss_admin($node->round[4]->comment) : '&nbsp;' ?></div>
    <div id="round-4-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-round-4-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => 2, 'orientation' => 'left')) ?>
  </div>
  <div id="round-5-left" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[5]->comment ? filter_xss_admin($node->round[5]->comment) : '&nbsp;' ?></div>
    <div id="round-5-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 1, 'orientation' => 'left')) ?>
  </div>
  <div id="round-6" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[6]->comment ? filter_xss_admin($node->round[6]->comment) : '&nbsp;' ?></div>
    <div id="round-6-spacer"></div>
    <?php print theme('bracket_match_lr', array('node' => $node, 'round_index' => 6, 'match_index' => 1)) ?>
  </div>
  <div id="round-5-right" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[5]->comment ? filter_xss_admin($node->round[5]->comment) : '&nbsp;' ?></div>
    <div id="round-5-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 5, 'match_index' => 2, 'orientation' => 'right')) ?>
  </div>
  <div id="round-4-right" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[4]->comment ? filter_xss_admin($node->round[4]->comment) : '&nbsp;' ?></div>
    <div id="round-4-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => 3, 'orientation' => 'right')) ?>
    <div class="bracket-round-4-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 4, 'match_index' => 4, 'orientation' => 'right')) ?>
  </div>
  <div id="round-3-right" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[3]->comment ? filter_xss_admin($node->round[3]->comment) : '&nbsp;' ?></div>
    <div id="round-3-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 5, 'orientation' => 'right')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 6, 'orientation' => 'right')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 7, 'orientation' => 'right')) ?>
    <div class="bracket-round-3-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 3, 'match_index' => 8, 'orientation' => 'right')) ?>
  </div>
  <div id="round-2-right" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[2]->comment ? filter_xss_admin($node->round[2]->comment) : '&nbsp;' ?></div>
    <div id="round-2-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 9, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 10, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 11, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 12, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 13, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 14, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 15, 'orientation' => 'right')) ?>
    <div class="bracket-round-2-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 2, 'match_index' => 16, 'orientation' => 'right')) ?>
  </div>
  <div id="round-1-right" class="bracket-round">
    <div class="bracket-round-comment"><?php print $node->round[1]->comment ? filter_xss_admin($node->round[1]->comment) : '&nbsp;' ?></div>
    <div id="round-1-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 17, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 18, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 19, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 20, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 21, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 22, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 23, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 24, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 25, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 26, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 27, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 28, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 29, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 30, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 31, 'orientation' => 'right')) ?>
    <div class="bracket-round-1-match-spacer"></div>
    <?php print theme('bracket_match', array('node' => $node, 'round_index' => 1, 'match_index' => 32, 'orientation' => 'right')) ?>
  </div>
  <?php print theme('bracket_images', array('node' => $node)) ?>
  <div id="results" class="bracket-results">
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 1, 'orientation' => 'left')) ?>
    <div class="bracket-result-spacer"></div>
    <?php print theme('bracket_result', array('node' => $node, 'result_index' => 2, 'orientation' => 'left')) ?>
  </div>
</div>

