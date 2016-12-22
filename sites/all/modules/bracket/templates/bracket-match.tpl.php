<?php

/**
 * @file
 * Template for bracket match
 *
 * Available variables:
 *  $node: the node object for the bracket to be rendered.
 *  $round_index: the round index
 *  $match_index: the match index
 *  $orientation: the orientation of the match in the bracket - 'left' or 'right'
 */
?>
<div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>" class="bracket-match round-<?php print $round_index ?>-match-block">
  <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1-block" class="bracket-match-competitor-block">
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1" class="bracket-match-competitor bracket-match-competitor-<?php print $orientation ?><?php if ($node->round[$round_index]->match[$match_index]->win[1]) print ' bracket-match-winner' ?>"><?php print $node->round[$round_index]->match[$match_index]->cname[1] ? filter_xss_admin($node->round[$round_index]->match[$match_index]->cname[1]) : '&nbsp;' ?></div>
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1-score" class="bracket-match-score bracket-match-score-<?php print $orientation ?>"><?php print filter_xss_admin($node->round[$round_index]->match[$match_index]->score[1]) ?></div>
  </div>
  <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-block" class="bracket-match-block bracket-match-block-<?php print $orientation ?> round-<?php print $round_index ?>-match">
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1-comment-block" class="bracket-match-competitor-comment-block">
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1-comment" class="bracket-match-competitor-comment bracket-match-competitor-comment-<?php print $orientation ?>"><?php print $node->round[$round_index]->match[$match_index]->comp_comment[1] ? filter_xss_admin($node->round[$round_index]->match[$match_index]->comp_comment[1]) : '&nbsp;' ?></div>                
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-1-home" class="bracket-match-home bracket-match-home-<?php print $orientation ?>"><?php print $node->round[$round_index]->match[$match_index]->home[1] ? 'H' : '&nbsp;' ?></div>
    </div>
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-comment-block" class="bracket-match-comment-block round-<?php print $round_index ?>-match-comment-block">
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-comment-1" class="bracket-match-comment bracket-match-comment-<?php print $orientation ?>"><?php print filter_xss_admin($node->round[$round_index]->match[$match_index]->comment[1]) ?></div>
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-comment-2" class="bracket-match-comment bracket-match-comment-<?php print $orientation ?>"><?php print filter_xss_admin($node->round[$round_index]->match[$match_index]->comment[2]) ?></div>
    </div>
    <?php if ($node->options['show_match_id']) { ?>
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-id" class="bracket-match-id bracket-match-id-<?php print $orientation ?>">#<?php print $node->round[$round_index]->match[$match_index]->id ?></div>
    <?php } ?>
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2-block" class="bracket-match-competitor-block bracket-match-bottom-competitor-block">
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2" class="bracket-match-competitor bracket-match-competitor-<?php print $orientation ?><?php if ($node->round[$round_index]->match[$match_index]->win[2]) print " bracket-match-winner" ?>"><?php print $node->round[$round_index]->match[$match_index]->cname[2] ? filter_xss_admin($node->round[$round_index]->match[$match_index]->cname[2]) : '&nbsp;' ?></div>
      <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2-score" class="bracket-match-score bracket-match-score-<?php print $orientation ?>"><?php print filter_xss_admin($node->round[$round_index]->match[$match_index]->score[2]) ?></div>
    </div>
  </div>
  <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2-comment-block" class="bracket-match-competitor-comment-block">
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2-score" class="bracket-match-competitor-comment bracket-match-competitor-comment-<?php print $orientation ?>"><?php print $node->round[$round_index]->match[$match_index]->comp_comment[2] ? filter_xss_admin($node->round[$round_index]->match[$match_index]->comp_comment[2]) : '&nbsp;' ?></div>                
    <div id="round-<?php print $round_index ?>-match-<?php print $match_index ?>-competitor-2-home" class="bracket-match-home bracket-match-home-<?php print $orientation ?>"><?php print $node->round[$round_index]->match[$match_index]->home[2] ? 'H' : '&nbsp;' ?></div>
  </div>
</div>
