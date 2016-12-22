<?php

/**
 * @file
 * This file contains the image helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

// bracket image globals
global $_bracket_image_fontpath;
global $_bracket_image_font_file;
global $_bracket_image_font_bold_file;
global $_bracket_image_font_italic_file;
global $_bracket_image_font_bolditalic_file;
global $_bracket_image_font;
global $_bracket_image_font_bold;
global $_bracket_image_font_italic;
global $_bracket_image_font_bolditalic;
global $_bracket_image_font_xlarge;
global $_bracket_image_font_large;
global $_bracket_image_font_norm;
global $_bracket_image_font_small;
global $_bracket_image_font_xsmall;

// allocated image colors
global $_bracket_image_bg_color;
global $_bracket_image_fg_color;
global $_bracket_image_bar_bg_color;
global $_bracket_image_bar_fg_color;

// path to font files
$_bracket_image_fontpath = realpath(drupal_get_path('module', 'bracket') . '/fonts');

// default image font files
$_bracket_image_font_file = 'LiberationSans-Regular.ttf';
$_bracket_image_font_bold_file = 'LiberationSans-Bold.ttf';
$_bracket_image_font_italic_file = 'LiberationSans-Italic.ttf';
$_bracket_image_font_bolditalic_file = 'LiberationSans-BoldItalic.ttf';

// default font sizes
$_bracket_image_font_xlarge = 12;
$_bracket_image_font_large = 9;
$_bracket_image_font_norm = 7;
$_bracket_image_font_small = 6.5;
$_bracket_image_font_xsmall = 6;

// setup default font file paths
bracket_image_setup_font_paths();

// allocate default colors
bracket_image_allocate_default_colors();

/**
 * Allocate default image colors to globals
 *
 */
function bracket_image_allocate_default_colors() {

  global $_bracket_image_bg_color;
  global $_bracket_image_fg_color;
  global $_bracket_bg_color_default;
  global $_bracket_fg_color_default;
  global $_bracket_image_bar_bg_color;
  global $_bracket_image_bar_fg_color;
  global $_bracket_bar_bg_color_default;
  global $_bracket_bar_fg_color_default;

  $img = imagecreatetruecolor(10, 10);

  $rgb = bracket_html2rgb($_bracket_bg_color_default);
  $_bracket_image_bg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  $rgb = bracket_html2rgb($_bracket_fg_color_default);
  $_bracket_image_bar_fg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  $rgb = bracket_html2rgb($_bracket_bar_bg_color_default);
  $_bracket_image_bar_bg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  $rgb = bracket_html2rgb($_bracket_bar_fg_color_default);
  $_bracket_image_fg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);

  imagedestroy($img);
}

/**
 * Allocate image colors
 *
 * @param $node
 *   the bracket node
 * @param $img
 *   the image handle
 */
function bracket_image_setup_colors($node, $img) {

  global $_bracket_image_bg_color;
  global $_bracket_image_fg_color;
  global $_bracket_bg_color_default;
  global $_bracket_fg_color_default;

  $color = $node->options['image_options']['bg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
    $_bracket_image_bg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  }

  $color = $node->options['image_options']['fg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
    $_bracket_image_fg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  }
}

/**
 * Allocate image colors for bracket bar
 *
 * @param $node
 *   the bracket node
 * @param $img
 *   the image handle
 */
function bracket_image_setup_bar_colors($node, $img) {

  global $_bracket_image_bar_bg_color;
  global $_bracket_image_bar_fg_color;
  global $_bracket_bar_bg_color_default;
  global $_bracket_bar_fg_color_default;

  $color = $node->options['image_options']['bar_bg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
    $_bracket_image_bar_bg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  }
  $color = $node->options['image_options']['bar_fg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
    $_bracket_image_bar_fg_color = imagecolorallocate($img, $rgb[0], $rgb[1], $rgb[2]);
  }
}

/**
 * Override default font files
 *
 * @param $node
 *   the bracket node
 */
function bracket_image_setup_fonts($node) {

  global $_bracket_image_font_file;
  global $_bracket_image_font_bold_file;
  global $_bracket_image_font_italic_file;
  global $_bracket_image_font_bolditalic_file;

  $font = $node->options['image_options']['image_fonts']['image_font'];
  if (trim($font) != '') {
    $_bracket_image_font_file = $font;
  }

  $font = $node->options['image_options']['image_fonts']['image_font_bold'];
  if (trim($font) != '') {
    $_bracket_image_font_bold_file = $font;
  }

  $font = $node->options['image_options']['image_fonts']['image_font_italic'];
  if (trim($font) != '') {
    $_bracket_image_font_italic_file = $font;
  }

  $font = $node->options['image_options']['image_fonts']['image_font_bolditalic'];
  if (trim($font) != '') {
    $_bracket_image_font_bolditalic_file = $font;
  }

  bracket_image_setup_font_paths();
}

/**
 * Establish font paths
 *
 */
function bracket_image_setup_font_paths() {

  global $_bracket_image_fontpath;
  global $_bracket_image_font_file;
  global $_bracket_image_font_bold_file;
  global $_bracket_image_font_italic_file;
  global $_bracket_image_font_bolditalic_file;
  global $_bracket_image_font;
  global $_bracket_image_font_bold;
  global $_bracket_image_font_italic;
  global $_bracket_image_font_bolditalic;

  $_bracket_image_font = realpath($_bracket_image_fontpath . '/' . $_bracket_image_font_file);
  $_bracket_image_font_bold = realpath($_bracket_image_fontpath . '/' . $_bracket_image_font_bold_file);
  $_bracket_image_font_italic = realpath($_bracket_image_fontpath . '/' . $_bracket_image_font_italic_file);
  $_bracket_image_font_bolditalic = realpath($_bracket_image_fontpath . '/' . $_bracket_image_font_bolditalic_file);
}

/**
 * Draw a bracket set on the given image
 *
 * A bracket set is a vertical set of matches in a round
 *
 * @param $img
 *   the image handle
 * @param $node
 *   the bracket node
 * @param $lr
 *   the left or right edge (x-coord) of the bracket set (depending on orientation)
 * @param $top
 *   the top edge (y-coord) of the bracket set
 * @param $width
 *   the width of the bracket set
 * @param $height
 *   the vertical spacing between bracket lines (competitors)
 * @param $spacing
 *   the vertical spacing between bracket cells (matches)
 * @param $round
 *   the bracket round
 * @param $startmatch
 *   the starting match of this bracket set
 * @param $endmatch
 *   the ending match of this bracket set
 * @param $orient
 *   the orientation of the bracket set - 'L'=left or 'R'=right (optional - default is left)
 * @param $comments
 *   if true, match comments are displayed (optional - default is true)
 * @param $dashed
 *   if true, dashed bracket lines are produced (optional - default is false)
 */
function bracket_image_drawbracketset($img, $node, $lr, $top, $width, $height, $spacing, $round, $startmatch, $endmatch, $orient='L', $comments=TRUE, $dashed=FALSE) {

  $t = $top;
  $matchid = $node->options['show_match_id'];
  for ($m=$startmatch; $m<=$endmatch; $m++) {
    bracket_image_drawcell($img, $lr, $t, $width, $height, $node->round[$round]->match[$m], $orient, $comments, $matchid, $dashed);
    $t += $spacing;
  }
}

/**
 * Draw a bracket cell on the given image
 *
 * A bracket cell is a match
 *
 * @param $img
 *   the img handle
 * @param $lr
 *   the left or right edge (x-coord) of the bracket cell (depending on orientation)
 * @param $top
 *   the top edge (y-coord) of the bracket set
 * @param $width
 *   the width of the bracket set
 * @param $height
 *   the vertical spacing between bracket lines (competitors)
 * @param $match
 *   the match of this bracket cell
 * @param $orient
 *   the orientation of the bracket set - 'L'=left or 'R'=right
 * @param $comments
 *   if true, match comments are displayed (optional - default is true)
 * @param $matchid
 *   if true, match ids are displayed (optional - default is false)
 * @param $dashed
 *   if true, dashed bracket lines are produced (optional - default is false)
 */
function bracket_image_drawcell($img, $lr, $top, $width, $height, $match, $orient='L', $comments=TRUE, $matchid=FALSE, $dashed=FALSE) {

  global $_bracket_image_fg_color;
  global $_bracket_image_font;
  global $_bracket_image_font_norm;
  global $_bracket_image_font_small;
  global $_bracket_image_font_xsmall;

  // font cell width and height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = $bbox[2] - $bbox[0];

  // font cell width and height
  $bbox = imagettfbbox($_bracket_image_font_small, 0, $_bracket_image_font, 'Q');
  $hs = $bbox[1] - $bbox[7];
  $ws = $bbox[2] - $bbox[0];

  // comment orientation - opposite of cell orientation
  $co = 'L';
  if ($orient == 'L') $co = 'R';

  // draw bracket cell lines
  if ($orient == 'L') {
    imageline($img, $lr, $top, $lr+$width, $top, $_bracket_image_fg_color);
    if ($dashed) {
      bracket_image_imagedashedline($img, $lr+$width, $top, $lr+$width, $top+$height, $_bracket_image_fg_color);
      bracket_image_imagedashedline($img, $lr, $top+$height, $lr+$width, $top+$height, $_bracket_image_fg_color);
    }
    else {
      imageline($img, $lr+$width, $top, $lr+$width, $top+$height, $_bracket_image_fg_color);
      imageline($img, $lr, $top+$height, $lr+$width, $top+$height, $_bracket_image_fg_color);
    }
  }
  else {
    imageline($img, $lr, $top, $lr-$width, $top, $_bracket_image_fg_color);
    if ($dashed) {
      bracket_image_imagedashedline($img, $lr-$width, $top, $lr-$width, $top+$height, $_bracket_image_fg_color);
      bracket_image_imagedashedline($img, $lr, $top+$height, $lr-$width, $top+$height, $_bracket_image_fg_color);
    }
    else {
      imageline($img, $lr-$width, $top, $lr-$width, $top+$height, $_bracket_image_fg_color);
      imageline($img, $lr, $top+$height, $lr-$width, $top+$height, $_bracket_image_fg_color);
    }
  }

  // text coordinates
  $over = $top - 2;
  $under = $top + $hs - 1;
  if ($orient == 'L') {
    $lrx = $lr + 2;
  }
  else {
    $lrx = $lr - $width;
  }

  // draw top competitor
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $lrx, $over, $width, $match->cname[1], $_bracket_image_fg_color, $orient);
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx, $under, $width, $match->comp_comment[1], $_bracket_image_fg_color, $orient);

  // draw top competitor score
  if ($orient == 'L') {
    bracket_image_imagetextalign($img, $_bracket_image_font_small, $lr + $width - ($w * 2) - 1, $over, $w*2, $match->score[1], $_bracket_image_fg_color, 'R');
    if ($match->home[1]) {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $lr + $width - $w - 1, $under, $w, 'H', $_bracket_image_fg_color, 'R');
    }
  }
  else {
    bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx + 2, $over, $w * 2, $match->score[1], $_bracket_image_fg_color, 'L');
    if ($match->home[1]) {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx + 2, $under, $w, 'H', $_bracket_image_fg_color, 'L');
    }
  }

  // draw bracket cell comments
  if ($comments && ($match->comment[1] != '' || $match->comment[2] != '')) {

    // comment left position
    $clrx = $lrx;
    // adjust right comments slightly to the right
    if ($co == 'L') {
      $clrx = $lrx + 5;
    }

    // comment top position
    $ct = $top + ($height / 2);

    // adjust for two comments
    if ($match->comment[1] != '' && $match->comment[2] != '') {
      $ct -= ($hs / 4);
    }

    // draw comments
    if ($match->comment[1] != '') {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $clrx, $ct, $width-5, $match->comment[1], $_bracket_image_fg_color, $orient);
      $ct += $hs;
    }

    if ($match->comment[2] != '') {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $clrx, $ct, $width-5, $match->comment[2], $_bracket_image_fg_color, $orient);
    }
  }

  // draw match id
  if ($matchid) {
    // match number left position
    if ($orient == 'L') {
      $clrx = $lrx + $width - $w;
    }
    else {
      $clrx = $lrx + 2;
    }
    // match number top position
    $ct = $top + ($height / 2);
    bracket_image_imageTextAlign($img, $_bracket_image_font_xsmall, $clrx, $ct, $w, '#' . $match->id, $_bracket_image_fg_color, $co);
  }

  // text coordinates
  $over = $top + $height - 2;
  $under = $top + $height + $hs - 1;

  // draw bottom competitor
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $lrx, $over, $width, $match->cname[2], $_bracket_image_fg_color, $orient);
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx, $under, $width, $match->comp_comment[2], $_bracket_image_fg_color, $orient);

  // draw bottom competitor score
  if ($orient == 'L') {
    bracket_image_imagetextalign($img, $_bracket_image_font_small, $lr + $width - ($w * 2) - 1, $over, $w*2, $match->score[2], $_bracket_image_fg_color, 'R');
    if ($match->home[2]) {
        bracket_image_imagetextalign($img, $_bracket_image_font_small, $lr + $width - $w - 1, $under, $w, 'H', $_bracket_image_fg_color, 'R');
    }
  }
  else {
    bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx + 2, $over, ($w * 2), $match->score[2], $_bracket_image_fg_color, 'L');
    if ($match->home[2]) {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $lrx + 2, $under, $w, 'H', $_bracket_image_fg_color, 'L');
    }
  }
}

/**
 * Draw text on an image with a given alignment
 *
 * @param $img
 *   the image handle
 * @param $fontsize
 *   the font size to draw the text
 * @param $x
 *   the x-coord of the text
 * @param $y
 *   the y-coord of the text
 * @param $w
 *   the width of the text cell
 * @param $text
 *   the text to draw
 * @param $color
 *   the color to draw the text
 * @param $align
 *   the alignment of the text - 'C'=center,'L'=left,'R'=right (optional - default is left)
 */
function bracket_image_imagetextalign($img, $fontsize, $x, $y, $w, $text, $color, $align='L') {

  global $_bracket_image_font;

  if ($text != '') {

    $x = round($x, 0);
    $y = round($y, 0);
    $w = round($w, 0);

    // calculate width of string
    $bbox = imagettfbbox($fontsize, 0, $_bracket_image_font, $text);
    $textwidth = $bbox[2] - $bbox[0];

    // plot text based on alignment
    if ($align == 'L') {
      imagettftext($img, $fontsize, 0, $x, $y, $color, $_bracket_image_font, $text);
    }
    elseif ($align == 'R') {
      imagettftext($img, $fontsize, 0, ($x + $w - $textwidth - 2), $y, $color, $_bracket_image_font, $text);
    }
    else {
      imagettftext($img, $fontsize, 0, ($x + ($w / 2) - ($textwidth / 2)), $y, $color, $_bracket_image_font, $text);
    }
  }
}

/**
 * Word wrap text so it fits into a given width
 *
 * @param $text
 *   the text to split
 * @param $width
 *   the maximum width of the text
 * @param $fontsize
 *   the font size to use
 * @param $font
 *   the font to use
 * @return
 *   an array containing:
 *    - the height of each line as it would be rendered
 *    - an array containt the word wrapped text
 *    - the height of the text as it would be rendered
 */
function bracket_image_imagewordwrapbbox($text, $width, $fontsize = 10, $font = '') {

  $words = explode(' ', $text);
  $lines = array();
  $line = '';

  foreach ($words as $word ) {

    // check for new line and split line there
    $word2 = '';
    $p = strpos($word, "\n");
    if ($p) {
      $word2 = trim(substr($word, $p));
      $word = trim(substr($word, 0, $p));
      $line .= $word;
      $lines[] = trim($line);
      $line = '';
      $word = $word2;
    }
    $box = imagettfbbox($fontsize, 0, $font, $line . $word);
    $size = $box[4] - $box[0];
    if ($size > $width ) {
      $lines[] = trim($line);
      $line = '';
    }
    $line .= $word . ' ';
  }
  $lines[] = trim($line);

  $dimensions = imagettfbbox($fontsize, 0, $font, 'AJLMYabdfghjklpqry019`@$^&*(,' );
  $lineheight = $dimensions[1] - $dimensions[5];

  return array($lineheight, $lines, $lineheight * count($lines));
}

/**
 * draw text on the given image restricted to a given with and with a given alignment
 *
 * @param $img
 *   the image handle
 * @param $fontsize
 *   the font size to use
 * @param $
 *   the maximum width of the text
 * @param $fontsize
 *   the font size to use
 * @param $x
 *   the x-coord of the text
 * @param $y
 *   the y-coord of the text
 * @param $w
 *   the width of the text
 * @param $text
 *   the text to draw
 * @param $color
 *   the color to draw the text
 * @param $align
 *   the alignment of the text - 'L'=left or 'R'=right (optional - default is left)
 */
function bracket_image_imagetextwordwrap($img, $fontsize, $x, $y, $w, $text, $color, $align='L') {

  global $_bracket_image_font;

  $data = bracket_image_imagewordwrapbbox($text, $w, $fontsize, $_bracket_image_font);

  foreach ($data[1] as $key => $line ) {
    $locx = $x;
    $locy = $y + ($key * $data[0]);
    bracket_image_imagetextalign($img, $fontsize, $locx, $locy, $w, $line, $color, $align);
  }
}

/**
 * Insert an image into the given image
 *
 * @param $img
 *   the image handle
 * @param $imgpath
 *   the path to the image
 * @param $x
 *   the x coordinate of the image at which to insert the image
 * @param $y
 *   the y coordinate of the image at which to insert the image
 * @param $w
 *   scale the image to this width (optional - default is no scaling)
 * @param $center
 *   center the image over the coordinates (optional - default is FALSE)
 */
function bracket_image_insert_image($img, $imgpath, $x, $y, $w = 0, $center = FALSE) {

  // use a real path if possible
  $path = drupal_realpath($imgpath);
  if (!$path) {
    $path = bracket_logo_url($imgpath);
  }
  $size = getimagesize($path);
  if ($size) {
    $ftype = strrchr($path, '.');
    if ($ftype == '.jpg' || $ftype == '.jpeg') {
      $img2 = imagecreatefromjpeg($path);
    }
    if ($ftype == '.png') {
      $img2 = imagecreatefrompng($path);
    }
    if ($img2) {
      if ($w > 0) {
        $dsth = ($size[1] / $size[0]) * $w;
        if ($center) {
          $x = $x - ($w / 2);
          $y = $y - ($dsth / 2);
        }
        imagecopyresampled($img, $img2, $x, $y, 0, 0, $w, $dsth, $size[0], $size[1]);
      }
      else  {
        if ($center) {
          $x = $x - ($size[0] / 2);
          $y = $y - ($size[1] / 2);
        }
        imagecopyresampled($img, $img2, $x, $y, 0, 0, $size[0], $size[1], $size[0], $size[1]);
      }
      imagedestroy($img2);
    }
  }
}

/**
 * Draw a dashed line on the image
 *
 * @param $img
 *   the image handle
 * @param $x1
 *   the starting x coordinate of the line
 * @param $y1
 *   the starting y coordinate of the line
 * @param $x2
 *   the ending x coordinate of the line
 * @param $y2
 *   the ending y coordinate of the line
 * @param $color
 *   the color of the line
 */
function bracket_image_imagedashedline($img, $x1, $y1, $x2, $y2, $color) {

  $style = array($color,
                 $color,
                 $color,
                 $color,
                 IMG_COLOR_TRANSPARENT,
                 IMG_COLOR_TRANSPARENT,
                 IMG_COLOR_TRANSPARENT,
                 IMG_COLOR_TRANSPARENT);

  imagesetstyle($img, $style);

  imageline($img, $x1, $y1, $x2, $y2, IMG_COLOR_STYLED);
}

/**
 * Output an image stream
 *
 * @param $img
 *   the image handle
 * @return 
 *   png image stream
 */
function bracket_image_output_png($img) {

  ob_start();
  imagepng($img);
  $image_data = ob_get_contents();
  ob_end_clean();
  
  return $image_data;
}

/**
 * Draw a result cell on the given image
 *
 * A result cell is a single match result result
 *
 * @param $img
 *   the img handle
 * @param $lr
 *   the left or right edge (x-coord) of the result cell (depending on orientation)
 * @param $top
 *   the top edge (y-coord) of the result set
 * @param $width
 *   the width of the result set
 * @param $result
 *   the result to draw
 * @param $orient
 *   the orientation of the bracket set - 'L'=left or 'R'=right
 */
function bracket_image_draw_result($img, $lr, $top, $width, $result, $orient='L') {

  global $_bracket_image_fg_color;
  global $_bracket_image_font_norm;

  if ($orient == 'L') {
    $lrx = $lr + 2;
  }
  else {
    $lrx = $lr - $width;
  }

  imageline($img, $lrx, $top, $lrx+$width, $top, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $lrx, $top-5, $width, $result->cname, $_bracket_image_fg_color, $orient);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $lrx, $top+10, $width, $result->comment, $_bracket_image_fg_color, $orient);

}


