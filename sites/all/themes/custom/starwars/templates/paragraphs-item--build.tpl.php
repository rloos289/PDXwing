<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */

   switch (($content['field_build_faction']['#items'][0]['value'])) {
     case 'Rebel':
       $faction = 'rebel';
       break;
     case 'Imperial':
       $faction = 'empire';
       break;
     case 'Scum':
       $faction = 'scum';
       break;
   }
?>


 <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
   <div class="content"<?php print $content_attributes; ?>>
    <div class="<?php print render($faction); ?>">
      <?php
      print render($content['field_build_link']);
      ?>
    </div>
   </div>
 </div>
