<?php

/**
 * @file
 * Template for bracket result
 *
 * Available variables:
 *  $node: the node object for the bracket to be rendered.
 *  $result_index: the round index
 *  $orientation: the orientation of the result in the bracket - 'left' or 'right'
 */
?>
<div id="result-<?php print $result_index ?>" class="bracket-result-block">
  <div id="result-<?php print $result_index ?>-competitor" class="bracket-result bracket-result-<?php print $orientation ?>"><?php print $node->result[$result_index]->cname ? $node->result[$result_index]->cname : '&nbsp;' ?></div>
  <div id="result-<?php print $result_index ?>-separator" class="bracket-result-separator">
    <div id="result-<?php print $result_index ?>-comment" class="bracket-result-comment bracket-result-comment-<?php print $orientation ?>"><?php print $node->result[$result_index]->comment ?></div>
  </div>
</div>
 