<?php

/**
 * @file
 * This file contains the required functions for the se32po2lr bracket design
 *
 * This design consists of 32 competitors in a single elimination playoff bracket
 *
 * The bracket is formatted as a left and right bracket with 16 competitors each
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
function se32po2lr_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 32);
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
function se32po2lr_image($node) {

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
  $width = 90;
  $height = 45;
  $spacing = $height * 1.75;

  // spacing between top and bottom brackets
  $tb = $spacing * 4.5;

  // setup image
  $iwidth = 900;
  $iheight = 750;
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
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 4, 'L');
  bracket_image_drawbracketset($img, $node, $right, $top, $width, $height, $spacing, 1, 9, 12, 'R');
  bracket_image_drawbracketset($img, $node, $left, $top + $tb, $width, $height, $spacing, 1, 5, 8, 'L');
  bracket_image_drawbracketset($img, $node, $right, $top + $tb, $width, $height, $spacing, 1, 13, 16, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $hh = $spacing;
  $sp = $spacing * 2;
  // new top - add half prev height
  $t = $top + ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 2, 1, 2, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 2, 5, 6, 'R');
  bracket_image_drawbracketset($img, $node, $l, $t + $tb, $width, $hh, $sp, 2, 3, 4, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t + $tb, $width, $hh, $sp, 2, 7, 8, 'R');

  // results
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-5, $w, $node->result[1]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+10, $w, $node->result[1]->comment, $_bracket_image_fg_color, 'L');
  imageline($img, $r, $t, $r-$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t-5, $w, $node->result[5]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+10, $w, $node->result[5]->comment, $_bracket_image_fg_color, 'R');
  imageline($img, $l, $t+$tb, $l+$width, $t+$tb, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb-5, $w, $node->result[3]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb+10, $w, $node->result[3]->comment, $_bracket_image_fg_color, 'L');
  imageline($img, $r, $t+$tb, $r-$width, $t+$tb, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$tb-5, $w, $node->result[7]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$tb+10, $w, $node->result[7]->comment, $_bracket_image_fg_color, 'R');
  $t += $hh;
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-5, $w, $node->result[2]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+10, $w, $node->result[2]->comment, $_bracket_image_fg_color, 'L');
  imageline($img, $r, $t, $r-$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t-5, $w, $node->result[6]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+10, $w, $node->result[6]->comment, $_bracket_image_fg_color, 'R');
  imageline($img, $l, $t+$tb, $l+$width, $t+$tb, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb-5, $w, $node->result[4]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb+10, $w, $node->result[4]->comment, $_bracket_image_fg_color, 'L');
  imageline($img, $r, $t+$tb, $r-$width, $t+$tb, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$tb-5, $w, $node->result[8]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$tb+10, $w, $node->result[8]->comment, $_bracket_image_fg_color, 'R');

  // bracket title
  bracket_image_imagetextalign($img, $_bracket_image_font_xlarge, $iwidth / 2 - (400 / 2), 15, 400, $node->title, $_bracket_image_fg_color, 'C');

  // bracket subtitle
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $iwidth / 2 - (400 / 2), 30, 400, $node->subtitle, $_bracket_image_fg_color, 'C');

  // bracket comments
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_large, ($iwidth / 2) - 100, 200, 200, $node->comments, $_bracket_image_fg_color, 'C');

  // bracket footnote
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_small, 10, $iheight-30, $iwidth-10, $node->footer, $_bracket_image_fg_color, 'C');

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_image_setup_bar_colors($node, $img);
    $t = $top + $tb - ($spacing / 2);
    imagefilledrectangle($img, $left, $t-($h/2)-2, $iwidth-$left, $t+($h/2)+2, $_bracket_image_bar_bg_color);
    $t += 3;
    for ($i=1; $i<=sizeof($node->round) && $i <= 2; $i++) {
      bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $left + (($i-1) * $width), $t, $width, $node->round[$i]->comment, $_bracket_image_bar_fg_color, 'C');
      bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $right - ($i * $width), $t, $width, $node->round[$i]->comment, $_bracket_image_bar_fg_color, 'C');
    }
  }

  // bracket logo
  if ($node->logopath != '') {
    bracket_image_insert_image($img, $node->logopath, $iwidth / 2, 100, 150, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth / 2, 500, 75, TRUE);
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
function se32po2lr_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se32po2lr_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se32po2lr_pdf_page($node, &$pdf) {

  global $_bracket_pdf_font_name;
  global $_bracket_pdf_font_xlarge;
  global $_bracket_pdf_font_large;
  global $_bracket_pdf_font_norm;
  global $_bracket_pdf_font_small;
  global $_bracket_pdf_font_xsmall;

  // setup pdf
  $pdf->setAutoPageBreak(FALSE);
  $pdf->addPage('L');
  $iwidth = 11.0;
  $iheight = 8.5;

  // positions and spacing
  $top = 0.75;
  $left = 0.50;
  $width = 1.10;
  $height = 0.5;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 4.5;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node);

  // set font sizes
  $_bracket_pdf_font_norm = 8;
  $_bracket_pdf_font_small = 7;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round 1
  $right = 11.0 - $left;
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 4, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $right, $top, $width, $height, $spacing, 1, 9, 12, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $left, $top + $tb, $width, $height, $spacing, 1, 5, 8, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $right, $top + $tb, $width, $height, $spacing, 1, 13, 16, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $t = $top + ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 2, 1, 2, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 2, 5, 6, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t + $tb, $width, $hh, $sp, 2, 3, 4, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t + $tb, $width, $hh, $sp, 2, 7, 8, 'R');

  // results
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->cell($width, 0.125, $node->result[1]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->cell($width, 0.125, $node->result[1]->comment, 0, 0, 'L');
  $pdf->line($r, $t, $r-$width, $t);
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->cell($width, 0.125, $node->result[5]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t);
  $pdf->cell($width, 0.125, $node->result[5]->comment, 0, 0, 'R');
  $pdf->line($l, $t+$tb, $l+$width, $t+$tb);
  $pdf->setXY($l, $t+$tb-0.125);
  $pdf->cell($width, 0.125, $node->result[3]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t+$tb);
  $pdf->cell($width, 0.125, $node->result[3]->comment, 0, 0, 'L');
  $pdf->line($r, $t+$tb, $r-$width, $t+$tb);
  $pdf->setXY($r-$width, $t+$tb-0.125);
  $pdf->cell($width, 0.125, $node->result[7]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t+$tb);
  $pdf->cell($width, 0.125, $node->result[7]->comment, 0, 0, 'R');
  $t += $hh;
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->cell($width, 0.125, $node->result[2]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->cell($width, 0.125, $node->result[2]->comment, 0, 0, 'L');
  $pdf->line($r, $t, $r-$width, $t);
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->cell($width, 0.125, $node->result[6]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t);
  $pdf->cell($width, 0.125, $node->result[6]->comment, 0, 0, 'R');
  $pdf->line($l, $t+$tb, $l+$width, $t+$tb);
  $pdf->setXY($l, $t+$tb-0.125);
  $pdf->cell($width, 0.125, $node->result[4]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t+$tb);
  $pdf->cell($width, 0.125, $node->result[4]->comment, 0, 0, 'L');
  $pdf->line($r, $t+$tb, $r-$width, $t+$tb);
  $pdf->setXY($r-$width, $t+$tb-0.125);
  $pdf->cell($width, 0.125, $node->result[8]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t+$tb);
  $pdf->cell($width, 0.125, $node->result[8]->comment, 0, 0, 'R');

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
  $pdf->setXY(($iwidth / 2) - (2.0 / 2), 2.5);
  $pdf->multicell(2.0, 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, $iheight - 0.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, 5.5, 1.5, 1.75, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 5.5, 5.5, 0.75, TRUE);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_pdf_setup_bar_colors($node, $pdf);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $t = $top + $tb - $height;
    $pdf->setXY($left, $t);
    $pdf->cell(11.0 - ($left * 2), 0.125, '', 0, 0, 'C', TRUE);
    for ($i=1; $i<=sizeof($node->round) && $i <= 2; $i++) {
      $pdf->setXY($left + (($i-1) * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C');
      $pdf->setXY($right - ($i * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C');
    }
  }
}