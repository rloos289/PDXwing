<?php

/**
 * @file
 * This file contains the required functions for the se24po2lr bracket design
 *
 * This design consists of 24 competitors in a single elimination playoff bracket
 *
 * The bracket is formatted as a left and right bracket with 12 competitors each
 *
 * competing for 2 rounds only
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function se24po2lr_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 24);
  // add 2 rounds
  bracket_design_create_winner_rounds($node, 2);
  // add results
  bracket_design_create_playoff_results($node);
  // name the rounds
  $node->round[1]->name = 'Round 1';
  $node->round[2]->name = 'Round 2';
}

/**
 * Produce a png image for the requested bracket object
 *
 * @param $b
 *   the bracket object
 * @return
 *   the png image
 */
function se24po2lr_image($node) {

  global $_bracket_image_font;
  global $_bracket_image_font_bold;
  global $_bracket_image_font_xlarge;
  global $_bracket_image_font_large;
  global $_bracket_image_font_norm;
  global $_bracket_image_font_small;
  global $_bracket_image_font_xsmall;
  global $_bracket_image_bg_color;
  global $_bracket_image_fg_color;
  global $_bracket_image_bar_bg_color;
  global $_bracket_image_bar_fg_color;

  // setup positions and spacing
  $top = 25;
  $left = 15;
  $width = 100;
  $height = 45;
  $spacing = $height * 1.75;

  // spacing between top and bottom brackets
  $tb = $spacing * 6.5;

  // setup image
  $iwidth = 900;
  $iheight = 500;
  $img = imagecreatetruecolor($iwidth, $iheight);

  // allocate colors
  bracket_image_setup_colors($node, $img);

  // setup fonts
  bracket_image_setup_fonts($node);

  // fill in background
  imagefill($img, 0, 0, $_bracket_image_bg_color);

  // font sizes
  $_bracket_image_font_xlarge = 12;
  $_bracket_image_font_large = 10;
  $_bracket_image_font_norm = 7.5;
  $_bracket_image_font_small = 6.5;
  $_bracket_image_font_xsmall = 6;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // round 1
  $right = $iwidth - $left;
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 6, 'L');
  bracket_image_drawbracketset($img, $node, $right, $top, $width, $height, $spacing, 1, 7, 12, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $hh = $spacing;
  $sp = $spacing * 2;
  // new top - add half prev height
  $t = $top + ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 2, 1, 3, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 2, 4, 6, 'R');

  // results
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  bracket_image_draw_result($img, $l, $t, $width, $node->result[1], 'L');
  bracket_image_draw_result($img, $r, $t, $width, $node->result[4], 'R');
  
  $t += $hh;
  bracket_image_draw_result($img, $l, $t, $width, $node->result[2], 'L');
  bracket_image_draw_result($img, $r, $t, $width, $node->result[5], 'R');
  
  $t += $hh;
  bracket_image_draw_result($img, $l, $t, $width, $node->result[3], 'L');
  bracket_image_draw_result($img, $r, $t, $width, $node->result[6], 'R');

  // bracket title
  bracket_image_imagetextalign($img, $_bracket_image_font_xlarge, $iwidth / 2 - (400 / 2), 15, 400, $node->title, $_bracket_image_fg_color, 'C');

  // bracket subtitle
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $iwidth / 2 - (400 / 2), 30, 400, $node->subtitle, $_bracket_image_fg_color, 'C');

  // bracket comments
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_large, ($iwidth / 2) - 100, 200, 200, $node->comments, $_bracket_image_fg_color, 'C');

  // bracket footnote
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_small, 10, $iheight-30, $iwidth-10, $node->footer, $_bracket_image_fg_color, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_image_insert_image($img, $node->logopath, $iwidth / 2, 100, 150, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth / 2, $iheight - 100, 75, TRUE);
  }

  // generate the png image stream
  $png = bracket_image_output_png($img);
  
  // done with the image
  imagedestroy($img);

  // return the image
  return $png;
}

/**
 * Produce a pdf document for the requested bracket object
 *
 * @param $node
 *   the bracket node object
 * @return
 *   the pdf document
 */
function se24po2lr_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se24po2lr_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se24po2lr_pdf_page($node, &$pdf) {

  global $_bracket_pdf_font_name;
  global $_bracket_pdf_font_xlarge;
  global $_bracket_pdf_font_large;
  global $_bracket_pdf_font_norm;
  global $_bracket_pdf_font_small;
  global $_bracket_pdf_font_xsmall;

  // setup pdf
  $pdf->setAutoPageBreak(FALSE);
  $pdf->addPage('P');
  $iwidth = 8.5;
  $iheight = 11.0;

  // positions and spacing
  $top = 0.75;
  $left = 0.50;
  $width = 1.0;
  $height = 0.45;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 6.5;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node);

  // set font sizes
  $_bracket_pdf_font_norm = 8;
  $_bracket_pdf_font_small = 7;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round 1
  $right = $iwidth - $left;
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 6, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $right, $top, $width, $height, $spacing, 1, 7, 12, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $t = $top + ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 2, 1, 3, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 2, 4, 6, 'R');

  // results
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  bracket_pdf_draw_result($pdf, $l, $t, $width, $node->result[1], 'L');
  bracket_pdf_draw_result($pdf, $r, $t, $width, $node->result[4], 'R');
  
  $t += $hh;
  bracket_pdf_draw_result($pdf, $l, $t, $width, $node->result[2], 'L');
  bracket_pdf_draw_result($pdf, $r, $t, $width, $node->result[5], 'R');
  
  $t += $hh;
  bracket_pdf_draw_result($pdf, $l, $t, $width, $node->result[3], 'L');
  bracket_pdf_draw_result($pdf, $r, $t, $width, $node->result[6], 'R');

  // bracket title
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_xlarge);
  $pdf->setXY($left, 0.5);
  $pdf->multicell($iwidth - ($left * 2) , 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_large);
  $pdf->setXY($left, 0.75);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->subtitle, 0, 'C');

  // bracket comments
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_large);
  $pdf->setXY(($iwidth / 2) - (2.0 / 2), 3.5);
  $pdf->multicell(2.0, 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, $iheight - 0.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, $iwidth / 2, 2.25, 1.75, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, $iwidth / 2, 9.0, 0.75, TRUE);
  }
}