<?php

/**
 * @file
 * This file contains the required functions for the se8champ bracket design
 *
 * This design consists of 8 competitors in a single elimination bracket
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function se8champ_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 8);
  // add rounds
  bracket_design_create_winner_rounds($node);
  // name the rounds
  $node->round[1]->name = t('Quarterfinals');
  $node->round[2]->name = t('Semifinals');
  $node->round[3]->name = t('Finals');
  // add championship results
  bracket_design_create_championship_results($node);
}

/**
 * Produce a png image for the requested bracket object
 *
 * @param $b
 *   the bracket object
 * @return
 *   the png image
 */
function se8champ_image($node) {

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
  $top = 75;
  $left = 15;
  $width = 130;
  $height = 60;
  $spacing = $height * 1.75;

  // spacing between top and bottom brackets
  $tb = $spacing * 2.5;

  // setup image
  $iwidth = 700;
  $iheight = 600;
  $img = imagecreatetruecolor($iwidth, $iheight);

  // allocate colors
  bracket_image_setup_colors($node, $img);

  // setup fonts
  bracket_image_setup_fonts($node);

  // fill in background
  imagefill($img, 0, 0, $_bracket_image_bg_color);

  // font sizes
  $_bracket_image_font_xlarge = 14;
  $_bracket_image_font_large = 12;
  $_bracket_image_font_norm = 10;
  $_bracket_image_font_small = 8;
  $_bracket_image_font_xsmall = 6.5;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // quarters
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 2, 'L');
  bracket_image_drawbracketset($img, $node, $left, $top+$tb, $width, $height, $spacing, 1, 3, 4, 'L');

  // semis
  $l = $left + $width;
  $hh = $spacing;
  $sp = $spacing * 2;
  // new top - add half prev height
  $t = $top + ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 2, 1, 1, 'L');
  bracket_image_drawbracketset($img, $node, $l, $t+$tb, $width, $hh, $sp, 2, 2, 2, 'L');

  // finals
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp + ($spacing / 2);
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 3, 1, 1, 'L', FALSE);

  // get match
  $match = $node->round[3]->match[1];
  // finals comments
  if ($match->comment[1] != '' || $match->comment[2] != '') {
    // comment left position
    $cl = $l + 5;
    // comment top position
    $ct = $t + ($hh / 2) - 50;
    // adjust for two comments
    if ($match->comment[1] != '' && $match->comment[2] != '') {
      $ct -= 10;
    }
    // draw comments
    if ($match->comment[1] != '') {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $cl, $ct, $width-5, $match->comment[1], $_bracket_image_fg_color, 'L');
      $ct += 10;
    }
    if ($match->comment[2] != '') {
      bracket_image_imagetextalign($img, $_bracket_image_font_small, $cl, $ct, $width-5, $match->comment[2], $_bracket_image_fg_color, 'L');
    }
  }

  // winner and runner-up
  $t += ($hh / 3);
  $l += $width;
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l+2, $t-2, $width, $node->result[1]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$h+1, $width, $node->result[1]->comment, $_bracket_image_fg_color, 'L');
  $t += ($hh / 3);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l+2, $t-2, $width, $node->result[2]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$h+1, $width, $node->result[2]->comment, $_bracket_image_fg_color, 'L');

  // bracket title
  bracket_image_imagetextalign($img, $_bracket_image_font_xlarge, $iwidth / 2 - (400 / 2), 15, 400, $node->title, $_bracket_image_fg_color, 'C');

  // bracket subtitle
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $iwidth / 2 - (400 / 2), 30, 400, $node->subtitle, $_bracket_image_fg_color, 'C');

  // bracket comments
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_small, $iwidth / 2 - (400 / 2), 60, 400, $node->comments, $_bracket_image_fg_color, 'C');

  // bracket footnote
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_small, $left, $iheight-$h, $iwidth-($left*2), $node->footer, $_bracket_image_fg_color, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_image_insert_image($img, $node->logopath, $iwidth-250, 80, 150);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth/2, $iheight-75, 75, TRUE);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_image_setup_bar_colors($node, $img);
    $t = $top + $tb - ($spacing / 2);
    imagefilledrectangle($img, $left, $t-($h/2)-2, $l, $t+($h/2)+2, $_bracket_image_bar_bg_color);
    $t += 4;
    for ($i=1; $i<=sizeof($node->round); $i++) {
      bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $left + (($i-1) * $width), $t, $width, $node->round[$i]->comment, $_bracket_image_bar_fg_color, 'C');
    }
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
function se8champ_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se8champ_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se8champ_pdf_page($node, &$pdf) {

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
  $top = 3.0;
  $left = 0.75;
  $width = 1.5;
  $height = 0.75;
  $spacing = $height * 1.5;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 2.5;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // set font sizes
  $_bracket_pdf_font_norm = 8;
  $_bracket_pdf_font_small = 7;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // quarters
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 2, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $left, $top + $tb, $width, $height, $spacing, 1, 3, 4, 'L');

  // semis
  $l = $left + $width;
  $t = $top + ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 2, 1, 1, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t + $tb, $width, $hh, $sp, 2, 2, 2, 'L');

  // finals
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp + ($spacing / 2);
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 3, 1, 1, 'L', FALSE);

  // get match
  $match = $node->round[3]->match[1];
  // draw comments
  if ($match->comment[1] != '' || $match->comment[2] != '') {
    // draw bracket cell comments
    $t2 = $t + ($hh / 2) - 0.5;
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
    if ($match->comment[1] != '' && $match->comment[2] != '') {
      $t2 -= 0.125;
    }
    $pdf->setXY($l, $t2);
    if ($match->comment[1] != '') {
      $pdf->setXY($l, $t2);
      $pdf->cell($width, 0.125, $match->comment[1], 0, 0, 'L');
      $t2 += 0.125;
    }
    if ($match->comment[2] != '') {
      $pdf->setXY($l, $t2);
      $pdf->cell($width, 0.125, $match->comment[2], 0, 0, 'L');
    }
  }

  // winner and runner-up
  $t += ($hh / 3);
  $l += $width;
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[1]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[1]->comment, 0, 0, 'L');
  $t += ($hh / 3);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[2]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[2]->comment, 0, 0, 'L');

  // bracket title
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_xlarge);
  $pdf->setXY($left, 0.5);
  $pdf->multicell($iwidth - ($left * 2) , 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_large);
  $pdf->setXY($left, 0.75);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->subtitle, 0, 'C');

  // bracket comments
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->setXY($left, 1.0);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, $iheight - 0.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, 6.5, 1.75, 2.0);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 4.25, 9.5, 0.75);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_pdf_setup_bar_colors($node, $pdf);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $t = $top + $tb - ($spacing / 2);
    for ($i=1; $i<=sizeof($node->round); $i++) {
      $pdf->setXY($left + (($i-1) * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C', TRUE);
    }
  }
}