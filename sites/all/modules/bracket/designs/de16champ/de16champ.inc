<?php

/**
 * @file
 * This file contains the required functions for the de16champ bracket design
 *
 * This design consists of 16 competitors in a double elimination bracket
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function de16champ_create(&$node) {

  // set match id option
  $node->options['show_match_id'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 16);
  // add winner rounds
  bracket_design_create_winner_rounds($node);
  // add championship results
  bracket_design_create_championship_results($node);
  // add loser rounds
  bracket_design_create_loser_rounds($node);
  // name the rounds
  for ($i=1; $i<=4; $i++) {
    $node->round[$i]->name = t('Round') . ' ' . $i;
  }
  $node->round[5]->name = t('Final') . ' 1';
  $node->round[6]->name = t('Final') . ' 2';
  for ($i=7; $i<=12; $i++) {
    $node->round[$i]->name = t('Loser Rnd') . ' ' . ($i-6);
  }
}

/**
 * Produce a png image for the requested bracket object
 *
 * @param $b
 *   the bracket object
 * @return
 *   the png image
 */
function de16champ_image($node) {

  global $_bracket_image_font;
  global $_bracket_image_font_bold;
  global $_bracket_image_font_xlarge;
  global $_bracket_image_font_large;
  global $_bracket_image_font_norm;
  global $_bracket_image_font_small;
  global $_bracket_image_font_xsmall;
  global $_bracket_image_bg_color;
  global $_bracket_image_fg_color;

  // setup positions and spacing
  $top = 75;
  $left = 15;
  $width = 110;
  $height = 45;
  $spacing = $height * 1.75;

  // spacing between top and bottom brackets
  $tb = $spacing * 8.25;

  // setup image
  $iwidth = 950;
  $iheight = 1100;
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
  $_bracket_image_font_norm = 9;
  $_bracket_image_font_small = 7;
  $_bracket_image_font_xsmall = 6.5;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // round 1
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 8, 'L', TRUE);

  // round 2
  $l = $left + $width;
  $hh = $spacing;
  $sp = $spacing * 2;
  // new top - add half prev height
  $t = $top + ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 2, 1, 4, 'L', TRUE);

  // round 3
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 3, 1, 2, 'L', TRUE);

  // round 4
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 4, 1, 1, 'L', TRUE);

  // final - top competitor
  $toplinex = $l + $width;
  $topliney = $t + ($hh / 2);

  // loser rounds
  $lrnd = bracket_round_first_loser_round($node);
  $t = $top + $tb;

  // loser round 1
  bracket_image_drawbracketset($img, $node, $left, $t, $width, $height, $spacing, $lrnd, 1, 4, 'L', TRUE);

  // loser round 2
  $l = $left + $width;
  // determine if last match winner goes to top of bottom slot
  if ($node->round[$lrnd]->match[1]->winner_comp == 1)
      $t += ($height / 2);
  else
      $t -= ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $height, $spacing, $lrnd+1, 1, 4, 'L', TRUE);

  // loser round 3
  $l += $width;
  $t += ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $lrnd+2, 1, 2, 'L', TRUE);

  // loser round 4
  $l += $width;
  if ($node->round[$lrnd]->match[1]->winner_comp == 1)
      $t += ($hh / 2);
  else
      $t -= ($hh / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $lrnd+3, 1, 2, 'L', TRUE);

  // loser round 5
  $l += $width;
  $t = $t + ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $lrnd+4, 1, 1, 'L', TRUE);

  // loser round 6
  $l += $width;
  // determine if last match winner goes to top of bottom slot
  if ($node->round[$lrnd+2]->match[1]->winner_comp == 1) {
    $t += ($hh / 2);
  }
  else {
    $t -= ($hh / 2);
  }
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $lrnd+5, 1, 1, 'L', TRUE);

  // finals
  $botlinex = $l + $width;
  $botliney = $t + ($hh / 2);
  $hh = $botliney - $topliney;
  $sp = $sp * 2;
  imageline($img, $toplinex, $topliney, $botlinex, $topliney, $_bracket_image_fg_color);
  bracket_image_drawbracketset($img, $node, $botlinex, $topliney, $width, $hh, $sp, 5, 1, 1, 'L', TRUE);

  // second final - if loser's first loss
  $x = $botlinex + $width;
  $y = $topliney + ($hh / 2);
  $hh = ($hh / 2) + ($height * 2);
  bracket_image_drawbracketset($img, $node, $x, $y, $width, $hh, $sp, 6, 1, 1, 'L', TRUE, TRUE);

  // winner and runner-up
  $t = $iheight-100;
  $l = $x - $width;
  $w = $width * 2;
  imageline($img, $l, $t, $l+$w, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $w, $node->result[1]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $w, $node->result[1]->comment, $_bracket_image_fg_color, 'C');
  $t += 50;
  imageline($img, $l, $t, $l+$w, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $w, $node->result[2]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $w, $node->result[2]->comment, $_bracket_image_fg_color, 'C');

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
    bracket_image_insert_image($img, $node->logopath, $iwidth-350, 120, 200);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth/2, $iheight-100, 75, TRUE);
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
function de16champ_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  de16champ_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function de16champ_pdf_page($node, &$pdf) {

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
  $top = 0.5;
  $left = 0.5;
  $width = 0.9;
  $height = 0.45;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 8.25;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // set font sizes
  $_bracket_pdf_font_xlarge = 14.0;
  $_bracket_pdf_font_large = 10.0;
  $_bracket_pdf_font_norm = 7.0;
  $_bracket_pdf_font_small = 6.0;
  $_bracket_pdf_font_xsmall = 5.0;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round 1
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 8, 'L', TRUE);

  // round 2
  $l = $left + $width;
  $t = $top + ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 2, 1, 4, 'L', TRUE);

  // round 3
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 3, 1, 2, 'L', TRUE);

  // round 4
  $l += $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 4, 1, 1, 'L', TRUE);

  // final - top competitor
  $toplinex = $l + $width;
  $topliney = $t + ($hh / 2);

  // loser rounds
  $lrnd = bracket_round_first_loser_round($node);
  $t = $top + $tb;

  // loser round 1
  bracket_pdf_drawbracketset($pdf, $node, $left, $t, $width, $height, $spacing, $lrnd, 1, 4, 'L', TRUE);

  // loser round 2
  $l = $left + $width;
  // determine if last match winner goes to top of bottom slot
  if ($node->round[$lrnd]->match[1]->winner_comp == 1) {
    $t += ($height / 2);
  }
  else {
    $t -= ($height / 2);
  }
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $height, $spacing, $lrnd+1, 1, 4, 'L', TRUE);

  // loser round 3
  $l += $width;
  $t += ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $lrnd+2, 1, 2, 'L', TRUE);

  // loser round 4
  $l += $width;
  // determine if last match winner goes to top of bottom slot
  if ($node->round[$lrnd]->match[1]->winner_comp == 1) {
    $t += ($hh / 2);
  }
  else {
    $t -= ($hh / 2);
  }
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $lrnd+3, 1, 2, 'L', TRUE);

  // loser round 5
  $l += $width;
  $t = $t + ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $lrnd+4, 1, 1, 'L', TRUE);

  // loser round 6
  $l += $width;
  // determine if last match winner goes to top of bottom slot
  if ($node->round[$lrnd+2]->match[1]->winner_comp == 1) {
    $t += ($hh / 2);
  }
  else {
    $t -= ($hh / 2);
  }
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $lrnd+5, 1, 1, 'L', TRUE);

  // finals
  $botlinex = $l + $width;
  $botliney = $t + ($hh / 2);
  $hh = $botliney - $topliney;
  $sp = $sp * 2;
  $pdf->line($toplinex, $topliney, $botlinex, $topliney);
  bracket_pdf_drawbracketset($pdf, $node, $botlinex, $topliney, $width, $hh, $sp, 5, 1, 1, 'L', TRUE);

  // second final - if loser's first loss
  $l = $botlinex + $width;
  $t = $topliney + ($hh / 2);
  $hh = ($hh / 2) + ($height * 2);
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 6, 1, 1, 'L', TRUE, TRUE);

  // winner and runner-up
  $t = 9.5;
  $w = $width * 2;
  $l = 8.0 - $w;
  $pdf->line($l, $t, $l+$w, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($w, 0.125, $node->result[1]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($w, 0.125, $node->result[1]->comment, 0, 0, 'C');
  $t += 0.5;
  $pdf->line($l, $t, $l+$w, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($w, 0.125, $node->result[2]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($w, 0.125, $node->result[2]->comment, 0, 0, 'C');

  // bracket title
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_xlarge);
  $pdf->setXY(3.5, $top);
  $pdf->multicell(4.5, 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_large);
  $pdf->setXY(3.5, $top + 0.5);
  $pdf->multicell(4.5, 0.125, $node->subtitle, 0, 'C');

  // bracket comments
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->setXY(2.0, $top + 0.75);
  $pdf->multicell(5.0, 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, 10.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, 6.5, $top + 1.0, 2.0);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 4.25, 9.5, 0.75);
  }
}

