<?php

/**
 * @file
 * Template for bracket images
 *
 * Available variables:
 *  $node: the node object for the bracket to be rendered.
 */
?>
 
<?php if ($node->logopath) { ?>
  <div id="logo-image" class="bracket-logo-image-block">
    <img src="<?php print bracket_logo_url($node->logopath) ?>" class="bracket-logo-image" />
  </div>
<?php } ?>
<?php if ($node->sponsorlogopath) { ?>
  <div id="sponsorlogo-image" class="bracket-sponsorlogo-image-block">
    <img src="<?php print bracket_logo_url($node->sponsorlogopath) ?>" class="bracket-sponsorlogo-image" />
  </div>
<?php } ?>
