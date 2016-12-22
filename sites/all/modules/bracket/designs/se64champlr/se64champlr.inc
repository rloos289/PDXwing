<?php

/**
 * @file
 * This file contains the required functions for the se64champlr bracket design
 *
 * This design consists of 64 competitors in a single elimination bracket
 *
 * The bracket is formatted as a left and right bracket with 32 competitors each
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function se64champlr_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 64);
  // add rounds
  bracket_design_create_winner_rounds($node);
  // name the rounds
  $node->round[1]->name = t('Round') . ' 1';
  $node->round[2]->name = t('Round') . ' 2';
  $node->round[3]->name = t('Round') . ' 3';
  $node->round[4]->name = t('Quarterfinals');
  $node->round[5]->name = t('Semifinals');
  $node->round[6]->name = t('Finals');
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
function se64champlr_image($node) {

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
  $left = 5;
  $width = 85;
  $height = 40;
  $spacing = $height * 1.75;

  // spacing between top and bottom brackets
  $tb = $spacing * 8.5;

  // setup image
  $iwidth = 1000;
  $iheight = 1200;
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
  $_bracket_image_font_norm = 7;
  $_bracket_image_font_small = 6.5;
  $_bracket_image_font_xsmall = 6;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = $bbox[2] - $bbox[0];

  // round 1
  $right = $iwidth - $left;
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 8, 'L');
  bracket_image_drawbracketset($img, $node, $right, $top, $width, $height, $spacing, 1, 17, 24, 'R');
  bracket_image_drawbracketset($img, $node, $left, $top + $tb, $width, $height, $spacing, 1, 9, 16, 'L');
  bracket_image_drawbracketset($img, $node, $right, $top + $tb, $width, $height, $spacing, 1, 25, 32, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $hh = $spacing;
  $sp = $spacing * 2;
  // new top - add half prev height
  $t = $top + ($height / 2);
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 2, 1, 4, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 2, 9, 12, 'R');
  bracket_image_drawbracketset($img, $node, $l, $t + $tb, $width, $hh, $sp, 2, 5, 8, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t + $tb, $width, $hh, $sp, 2, 13, 16, 'R');

  // round 3
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 3, 1, 2, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 3, 5, 6, 'R');
  bracket_image_drawbracketset($img, $node, $l, $t + $tb, $width, $hh, $sp, 3, 3, 4, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t + $tb, $width, $hh, $sp, 3, 7, 8, 'R');

  // quarters
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 4, 1, 1, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 4, 3, 3, 'R');
  bracket_image_drawbracketset($img, $node, $l, $t + $tb, $width, $hh, $sp, 4, 2, 2, 'L');
  bracket_image_drawbracketset($img, $node, $r, $t + $tb, $width, $hh, $sp, 4, 4, 4, 'R');

  // semis
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp + $height;
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, 5, 1, 1, 'L', FALSE);
  $match = $node->round[4]->match[1];
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $l-$w, $t + ($hh / 3), $width, $match->comment[1], $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $l-$w, $t + ($hh / 3) + ($h * 2), $width, $match->comment[2], $_bracket_image_fg_color, 'R');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $hh, $sp, 5, 2, 2, 'R', FALSE);
  $match = $node->round[4]->match[2];
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $r-$width+$w, $t + $hh - ($hh / 3), $width, $match->comment[1], $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $r-$width+$w, $t + $hh - ($hh / 3) + ($h * 2), $width, $match->comment[2], $_bracket_image_fg_color, 'L');

  // finals
  $l += $width;
  $t += ($hh / 3);
  $match = $node->round[6]->match[1];
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-2, $width, $match->cname[1], $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $l+2, $t+$h+2, $width, $match->comp_comment[1], $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+$width-($w*2), $t-2, $w*2, $match->score[1], $_bracket_image_fg_color, 'R');
  if ($match->home[1]) {
    $_bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $l+$width-($w*2), $t+$h, $w, 'H', $_bracket_image_fg_color);
  }
  $t += ($hh / 3);
  $r -= $width;
  imageline($img, $r, $t, $r-$width, $t, $_bracket_image_fg_color);

  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-$width, $t-2, $width, $match->cname[2], $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $r-$width, $t+$h+2, $width, $match->comp_comment[2], $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-$width, $t-2, $w*2, $match->score[2], $_bracket_image_fg_color, 'L');
  if ($match->home[2]) {
    bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-$width, $t+$h, $w, 'H', $_bracket_image_fg_color);
  }

  bracket_image_imagetextalign($img, $_bracket_image_font_small, $iwidth / 2 - ($width / 2), $t + ($h * 5), $width, $match->comment[1], $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_small, $iwidth / 2 - ($width / 2) , $t + ($h * 5) + ($h * 2), $width, $match->comment[2], $_bracket_image_fg_color, 'C');

  // winner and runner-up
  $t = $iheight - 130;
  $w = $width * 2;
  $l = ($iwidth / 2) - ($w / 2);
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
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_norm, ($iwidth / 2) - 100, 200, 200, $node->comments, $_bracket_image_fg_color, 'C');

  // bracket footnote
  bracket_image_imagetextwordwrap($img, $_bracket_image_font_small, 10, $iheight-30, $iwidth-10, $node->footer, $_bracket_image_fg_color, 'C');

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_image_setup_bar_colors($node, $img);
    $t = $top + $tb - ($spacing / 2);
    imagefilledrectangle($img, $left, $t-($h/2)-2, $iwidth-$left, $t+($h/2)+2, $_bracket_image_bar_bg_color);
    $t += 3;
    for ($i=1; $i<=count($node->round) && $i <= 5; $i++) {
      bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $left + (($i-1) * $width), $t, $width, $node->round[$i]->comment, $_bracket_image_bar_fg_color, 'C');
      bracket_image_imageTextAlign($img, $_bracket_image_font_norm, $right - ($i * $width), $t, $width, $node->round[$i]->comment, $_bracket_image_bar_fg_color, 'C');
    }
    $l = $left + (4 * $width);
    $r = $right - (4 * $width);
    $width = $r - $l;
    if (count($node->round) >= 6) {
      bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t, $width, $node->round[6]->comment, $_bracket_image_bar_fg_color, 'C');
    }
  }

  // bracket logo
  if ($node->logopath != '') {
    bracket_image_insert_image($img, $node->logopath, $iwidth / 2, 100, 150, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth / 2, $iheight - 225, 75, TRUE);
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
function se64champlr_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se64champlr_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se64champlr_pdf_page($node, &$pdf) {

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
  $top = 0.25;
  $left = 0.25;
  $width = 0.85;
  $height = 0.285;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 8.5;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // font sizes
  $_bracket_pdf_font_norm = 7;
  $_bracket_pdf_font_small = 6;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round 1
  $right = 11.0 - $left;
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 8, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $right, $top, $width, $height, $spacing, 1, 17, 24, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $left, $top + $tb, $width, $height, $spacing, 1, 9, 16, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $right, $top + $tb, $width, $height, $spacing, 1, 25, 32, 'R');

  // round 2
  $l = $left + $width;
  $r = $right - $width;
  $t = $top + ($height / 2);
  $hh = $spacing;
  $sp = $spacing * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 2, 1, 4, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 2, 9, 12, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t + $tb, $width, $hh, $sp, 2, 5, 8, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t + $tb, $width, $hh, $sp, 2, 13, 16, 'R');

  // round 3
  $l += $width;
  $r += - $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 3, 1, 2, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 3, 5, 6, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t + $tb, $width, $hh, $sp, 3, 3, 4, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t + $tb, $width, $hh, $sp, 3, 7, 8, 'R');

  // quarters
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp;
  $sp = $sp * 2;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 4, 1, 1, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 4, 3, 3, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t + $tb, $width, $hh, $sp, 4, 2, 2, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t + $tb, $width, $hh, $sp, 4, 4, 4, 'R');

  // semis
  $l += $width;
  $r -= $width;
  $t += ($hh / 2);
  $hh = $sp + $height;
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, 5, 1, 1, 'L', FALSE);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $match = $node->round[4]->match[1];
  $pdf->setXY($l-0.125, $t + ($hh / 3) - 0.125);
  $pdf->cell($width, 0.125, $match->comment[1], 0, 0, 'R');
  $pdf->setXY($l-0.125, $t + ($hh / 3));
  $pdf->cell($width, 0.125, $match->comment[2], 0, 0, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $hh, $sp, 5, 2, 2, 'R', FALSE);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $match = $node->round[4]->match[2];
  $pdf->setXY($r-$width+0.125, $t + ($hh - ($hh / 3)) - 0.125);
  $pdf->cell($width, 0.125, $match->comment[1], 0, 0, 'L');
  $pdf->setXY($r-$width+0.125, $t + ($hh - ($hh / 3)));
  $pdf->cell($width, 0.125, $match->comment[2], 0, 0, 'L');

  // finals
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $l += $width;
  $t += $hh / 3;
  $match = $node->round[6]->match[1];
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->cell($width, 0.125, $match->cname[1], 0, 0, 'L');
  $pdf->setXY($l, $t+0.0625);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->cell($width, 0.125, $match->comp_comment[1], 0, 0, 'L');
  $pdf->setXY($l+$width-0.25+0.03125, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell(0.25, 0.125, $match->score[1], 0, 0, 'R');
  if ($match->home[1]) {
    $pdf->setXY($l+$width-0.125, $t+0.0625);
    $pdf->cell(0.125, $h, 'H');
  }
  $t += $hh / 3;
  $r -= $width;
  $pdf->line($r, $t, $r-$width, $t);
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->cell($width, 0.125, $match->cname[2], 0, 0, 'R');
  $pdf->setXY($r, $t+0.0625);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->cell($width, 0.125, $match->comp_comment[2], 0, 0, 'L');
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell(0.25, 0.125, $match->score[2], 0, 0, 'L');
  if ($match->home[2]) {
    $pdf->setXY($r-$width, $t+0.0625);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $pdf->cell(0.125, 0.125, 'H');
  }
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY(5.5 - ($width/2), $t + 0.25);
  $pdf->cell($width, 0.125, $match->comment[1], 0, 0, 'C');
  $pdf->setXY(5.5 - ($width/2), $t + 0.25 + 0.125);
  $pdf->cell($width, 0.125, $match->comment[2], 0, 0, 'C');

  // winner and runner-up
  $t = 7.25;
  $w = $width * 2;
  $l = 5.5 - ($w / 2);
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
  $pdf->setXY($left, 0.5);
  $pdf->multicell($iwidth - ($left * 2) , 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_large);
  $pdf->setXY($left, 0.75);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->subtitle, 0, 'C');

  // bracket comments
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->setXY(($iwidth / 2) - (1.0 / 2), 2.5);
  $pdf->multicell(1.0, 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, $iheight - 0.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, $iwidth/2, 1.5, 1.5, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, $iwidth/2, $iheight-2.0, 0.5, TRUE);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_pdf_setup_bar_colors($node, $pdf);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
    $t = $top + $tb - $height;
    $pdf->setXY($left, $t);
    $pdf->cell(11.0 - ($left * 2), 0.125, '', 0, 0, 'C', TRUE);
    for ($i=1; $i<=count($node->round) && $i <= 5; $i++) {
      $pdf->setXY($left + (($i-1) * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C');
      $pdf->setXY($right - ($i * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C');
    }
    $l = $left + (4 * $width);
    $pdf->setXY($l, $t);
    $r = $right - (4 * $width);
    $width = $r - $l;
    if (count($node->round) >= 6) {
      $pdf->cell($width, 0.125, $node->round[6]->comment, 0, 0, 'C');
    }
  }
}