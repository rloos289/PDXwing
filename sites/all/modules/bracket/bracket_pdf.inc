<?php

/**
 * @file
 * This file contains the pdf helper functions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

// check if FPDF is used by another module before including
if (!class_exists('FPDF')) {
  require_once 'FPDF/fpdf.php';
}

// incoporate the FPDF alpha channel fix from: http://staff.dasdeck.de/valentin/fpdf/fpdf_alpha/
if (!class_exists('PDF_ImageAlpha')) {
  require_once 'FPDF/fpdf_alpha.php';
}

// extend FPDF class to try and insulate us from future FPDF updates
class PDF extends PDF_ImageAlpha {
}

// bracket pdf globals
global $_bracket_pdf_font_name;
global $_bracket_pdf_font_xlarge;
global $_bracket_pdf_font_large;
global $_bracket_pdf_font_norm;
global $_bracket_pdf_font_small;
global $_bracket_pdf_font_xsmall;

// bracket pdf default values
$_bracket_pdf_font_name = 'Helvetica';
$_bracket_pdf_font_xlarge = 14;
$_bracket_pdf_font_large = 10;
$_bracket_pdf_font_norm = 8;
$_bracket_pdf_font_small = 7;
$_bracket_pdf_font_xsmall = 6;

/**
 * Setup pdf colors
 *
 * @param $node
 *   the bracket node
 * @param $pdf
 *   the pdf object
 */
function bracket_pdf_setup_colors($node, $pdf) {

  global $_bracket_bg_color_default;
  global $_bracket_fg_color_default;

  $color = $node->options['image_options']['fg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
  }
  else {
    $rgb = bracket_html2rgb($_bracket_fg_color_default);
  }
  $pdf->setTextColor($rgb[0], $rgb[1], $rgb[2]);
  $pdf->setDrawColor($rgb[0], $rgb[1], $rgb[2]);
}

/**
 * Setup pdf colors for bracket bar
 *
 * @param $node
 *   the bracket node
 * @param $pdf
 *   the pdf object
 */
function bracket_pdf_setup_bar_colors($node, $pdf) {

  global $_bracket_bar_bg_color_default;
  global $_bracket_bar_fg_color_default;

  $color = $node->options['image_options']['bar_fg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
  }
  else {
    $rgb = bracket_html2rgb($_bracket_bar_fg_color_default);
  }
  $pdf->setTextColor($rgb[0], $rgb[1], $rgb[2]);
  $pdf->setDrawColor($rgb[0], $rgb[1], $rgb[2]);

  $color = $node->options['image_options']['bar_bg_color'];
  if (bracket_validate_color($color)) {
    $rgb = bracket_html2rgb($color);
  }
  else {
    $rgb = bracket_html2rgb($_bracket_bar_bg_color_default);
  }
  $pdf->setFillColor($rgb[0], $rgb[1], $rgb[2]);
}

/**
 * Return the pdf font options
 *
 * @return
 *   the current pdf font options
 */
function bracket_pdf_font_options() {

  return array('Courier' => 'Courier', 'Helvetica' => 'Helvetica', 'Times' => 'Times');
}

/**
 * Set the pdf font
 *
 * @param $node
 *   the bracket node
 */
function bracket_pdf_setup_font($node) {

  global $_bracket_pdf_font_name;

  $font = $node->options['image_options']['pdf_font'];
  if (trim($font) != '') {
    $_bracket_pdf_font_name = $font;
  }
}

/**
 * Draw a bracket set on the given pdf
 *
 * A bracket set is a vertical set of matches in a round
 *
 * @param $pdf
 *   the pdf object
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
function bracket_pdf_drawbracketset($pdf, $node, $lr, $top, $width, $height, $spacing, $round, $startmatch, $endmatch, $orient='L', $comments=TRUE, $dashed=FALSE) {

  $t = $top;
  $matchid = $node->options['show_match_id'];
  for ($m=$startmatch; $m<=$endmatch; $m++) {
    bracket_pdf_drawcell($pdf, $lr, $t, $width, $height, $node->round[$round]->match[$m], $orient, $comments, $matchid, $dashed);
    $t += $spacing;
  }
}

/**
 * Draw a bracket cell on the given pdf
 *
 * A bracket cell is a match
 *
 * @param $pdf
 *   the pdf object
 * @param $lr
 *   the left or right edge (x-coord) of the bracket cell (depending on orientation)
 * @param $top
 *   the top edge (y-coord) of the bracket set
 * @param $width
 *   the width of the bracket set
 * @param $height
 *   the vertical spacing between bracket lines (competitors)
 * @param $match
 *   the match object to draw on this bracket cell
 * @param $orient
 *   the orientation of the bracket set - 'L'=left or 'R'=right
 * @param $comments
 *   if true, match comments are displayed (optional - default is true)
 * @param $matchid
 *   if true, match ids are displayed (optional - default is false)
 * @param $dashed
 *   if true, dashed bracket lines are produced (optional - default is false)
 */
function bracket_pdf_drawcell($pdf, $lr, $top, $width, $height, $match, $orient, $comments=TRUE, $matchid=FALSE, $dashed=FALSE) {

  global $_bracket_pdf_font_name;
  global $_bracket_pdf_font_norm;
  global $_bracket_pdf_font_small;
  global $_bracket_pdf_font_xsmall;

  // cell height
  $h = 0.125;
  if ($_bracket_pdf_font_norm <= 6.0) {
    $h = 0.0625;
  }  
  
  // comment orientation - opposite of cell orientation
  $co = 'L';
  if ($orient == 'L') {
    $co = 'R';
  }

  // draw bracket cell lines
  if ($orient == 'L') {
    $pdf->line($lr, $top, $lr+$width, $top);
    if ($dashed) {
      bracket_pdf_drawdashedline($pdf, $lr+$width, $top, $lr+$width, $top+$height);
      bracket_pdf_drawdashedline($pdf, $lr, $top+$height, $lr+$width, $top+$height);
    }
    else {
      $pdf->line($lr+$width, $top, $lr+$width, $top+$height);
      $pdf->line($lr, $top+$height, $lr+$width, $top+$height);
    }
  }
  else {
    $pdf->line($lr, $top, $lr-$width, $top);
    if ($dashed) {
      bracket_pdf_drawdashedline($pdf, $lr-$width, $top, $lr-$width, $top+$height);
      bracket_pdf_drawdashedline($pdf, $lr, $top+$height, $lr-$width, $top+$height);
    }
    else {
      $pdf->line($lr-$width, $top, $lr-$width, $top+$height);
      $pdf->line($lr, $top+$height, $lr-$width, $top+$height);
    }
  }

  // draw top competitor
  if ($orient == 'L') {
    $lrx = $lr;
  }
  else {
    $lrx = $lr - $width;
  }
  $pdf->setXY($lrx, $top-$h);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, $h, $match->cname[1], 0, 0, $orient);
  $pdf->setXY($lrx, $top);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->cell($width, $h, $match->comp_comment[1], 0, 0, $orient);

  // draw top competitor score
  if ($orient == 'L') {
    $pdf->setXY($lr+$width-0.25+0.03125, $top-$h);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $pdf->cell(0.25, $h, $match->score[1], 0, 0, 'R');
    if ($match->home[1]) {
      $pdf->setXY($lr+$width-0.150, $top);
      $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
      $pdf->cell(0.150, $h, 'H');
    }
  }
  else {
    $pdf->setXY($lrx, $top-$h);
    $pdf->cell(0.25, $h, $match->score[1], 0, 0, 'L');
    if ($match->home[1]) {
      $pdf->setXY($lrx, $top);
      $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
      $pdf->cell(0.25, $h, 'H');
    }
  }

  // draw comments
  if ($comments && ($match->comment[1] != '' || $match->comment[2] != '')) {
    // draw bracket cell comments
    $t2 = $top + ($height / 2);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
    if ($match->comment[1] != '' && $match->comment[2] != '') {
      $t2 -= $h;
    }
    else {
      $t2 -= ($h / 2);
    }
    $pdf->setXY($lrx, $t2);
    if ($match->comment[1] != '') {
      $pdf->setXY($lrx, $t2);
      $pdf->cell($width, $h, $match->comment[1], 0, 0, $orient);
      $t2 += $h;
    }
    if ($match->comment[2] != '') {
      $pdf->setXY($lrx, $t2);
      $pdf->cell($width, $h, $match->comment[2], 0, 0, $orient);
    }
  }

  // draw match id
  if ($matchid) {
    // match number position
    if ($orient == 'L') {
      $pdf->setXY($lrx + $width - $h, $top + ($height / 2) - ($h / 2));
    }
    else {
      $pdf->setXY($lrx, $top + ($height / 2) - ($h / 2));
    }
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_xsmall);
    $pdf->cell($h, $h, '#' . $match->id, 0, 0, $co);
  }

  // draw bottom competitor
  $pdf->setXY($lrx, $top+$height-$h);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, $h, $match->cname[2], 0, 0, $orient);
  $pdf->setXY($lrx, $top+$height);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->cell($width, $h, $match->comp_comment[2], 0, 0, $orient);

  // draw bottom competitor score
  if ($orient == 'L') {
    $pdf->setXY($lr+$width-0.25+0.03125, $top+$height-$h);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $pdf->cell(0.25, $h, $match->score[2], 0, 0, 'R');
    if ($match->home[2]) {
      $pdf->setXY($lr+$width-0.150, $top+$height);
      $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
      $pdf->cell(0.150, $h, 'H');
    }
  }
  else {
    $pdf->setXY($lrx, $top+$height-$h);
    $pdf->cell(0.25, $h, $match->score[2], 0, 0, 'L');
    if ($match->home[2]) {
      $pdf->setXY($lrx, $top+$height);
      $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
      $pdf->cell(0.25, $h, 'H');
    }
  }
}

/**
 * Draw a dashed line on the given pdf
 *
 * @param $pdf
 *   the pdf object
 * @param $x1
 *   the starting x-coord
 * @param $y1
 *   the starting y-coord
 * @param $x2
 *   the ending x-coord
 * @param $y2
 *   the ending y-coord
 */
function bracket_pdf_drawdashedline($pdf, $x1, $y1, $x2, $y2) {

  $ii = 0.125;
  if ($x1 == $x2) {
    for ($i=$y1; $i<=$y2; $i+=($ii*2)) {
      $j = $i+$ii;
      if ($j > $y2) $j = $y2;
      $pdf->line($x1, $i, $x2, $j);
    }
  }
  elseif ($y1 == $y2) {
    for ($i=$x1; $i<=$x2; $i+=($ii*2)) {
      $j = $i+$ii;
      if ($j > $x2) $j = $x2;
      $pdf->line($i, $y1, $j, $y2);
    }
  }
}

/**
 * Insert an image into the given pdf
 *
 * @param $pdf
 *   the pdf object
 * @param $imgpath
 *   the path to the image
 * @param $x
 *   the x coordinate of the pdf at which to insert the image
 * @param $y
 *   the y coordinate of the pdf at which to insert the image
 * @param $w
 *   scale the image to this width (optional - default is no scaling)
 * @param $center
 *   center the image over the coordinates (optional - default is FALSE)
 */
function bracket_pdf_insert_image($pdf, $imgpath, $x, $y, $w=0, $center = FALSE) {

  // use a real path if possible
  $path = drupal_realpath($imgpath);
  if (!$path) {
    $path = bracket_logo_url($imgpath);
  }
  $ftype = strrchr($path, '.');
  if ($ftype == '.png' || $ftype == '.jpg' || $ftype == '.jpeg') {
    $size = getimagesize($path);
    if ($size) {      
      $h = $size[1] / 72;
      if ($w > 0) {
        $w2 = $size[0] / 72;
        $h = ($w / $w2) * $h;
        if ($center) {
          $x -= ($w / 2);
          $y -= ($h / 2);
        }
        $pdf->image($path, $x, $y, $w);
      }
      else {
        $w = $size[0] / 72;
        $h = $size[1] / 72;
        if ($center) {
          $x -= ($w / 2);
          $y -= ($h / 2);
        }
        $pdf->image($path, $x, $y);
      }
    }
  }
}

/**
 * Draw a result cell on the given image
 *
 * A result cell is a single match result result
 *
 * @param $pdf
 *   the pdf object
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
function bracket_pdf_draw_result($pdf, $lr, $top, $width, $result, $orient='L') {

  global $_bracket_pdf_font_name;
  global $_bracket_pdf_font_norm;
  
  if ($orient == 'L') {
    $lrx = $lr;
  }
  else {
    $lrx = $lr - $width;
  }

  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->line($lrx, $top, $lrx + $width, $top);
  $pdf->setXY($lrx, $top-0.125);
  $pdf->cell($width, 0.125, $result->cname, 0, 0, $orient);
  $pdf->setXY($lrx, $top);
  $pdf->cell($width, 0.125, $result->comment, 0, 0, $orient);
}
