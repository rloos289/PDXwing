<?php

/**
 * @file
 * This file contains the required functions for the mde4champ bracket design
 *
 * This design consists of 4 competitors in a modified double elimination bracket
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function mde4champ_create(&$node) {

  // set match id option
  $node->options['show_match_id'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 4);
  // add winner rounds
  bracket_design_create_winner_rounds($node);
  // add championship results
  bracket_design_create_championship_results($node);
  // add loser rounds
  bracket_design_create_loser_rounds($node, TRUE);
  // add loser results
  $llr = bracket_round_last_loser_round($node);
  $node->round[$llr]->match[1]->winner_match = 0;
  $node->round[$llr]->match[1]->winner_compid = 0;
  $node->round[$llr]->match[1]->winner_result = 3;
  $node->round[$llr]->match[1]->loser_result = 4;
  $node->result[3] = new Bracket_Result();
  $node->result[3]->comment = '3rd Place';
  $node->result[4] = new Bracket_Result();
  $node->result[4]->comment = '4th Place';
  // name the rounds
  $node->round[1]->name = t('Semifinals');
  $node->round[2]->name = t('Final');
  $lr = 1;
  for ($i=bracket_round_first_loser_round($node); $i<=$llr; $i++) {
    $node->round[$i]->name = t('Loser Rnd') . ' ' . $lr++;
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
function mde4champ_image($node) {

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
  $width = 140;
  $height = 80;
  $spacing = $height * 1.75;

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
  $_bracket_image_font_small = 9;
  $_bracket_image_font_xsmall = 8;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // winner rounds
  for ($r=1; $r<=bracket_round_last_winner_round($node); $r++) {

    if ($r == 1) {  
      $l = $left;
      $hh = $height;
      $sp = $spacing;
      $t = $top;
      // number of winner matches
      $mc = count($node->comp) / 2;
    }
    else {
      $l += $width;
      $t += ($hh / 2);
      $hh = $sp;
      $sp = $sp * 2;
      $mc /= 2;
    }
    
    bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $r, 1, $mc, 'L', TRUE);
  }
  
  // winner and runner-up
  $l += $width;
  $t += ($hh / 3);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $width, $node->result[1]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $width, $node->result[1]->comment, $_bracket_image_fg_color, 'C');
  $t += ($hh / 3);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $width, $node->result[2]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $width, $node->result[2]->comment, $_bracket_image_fg_color, 'C');
  
  // loser rounds
  $lrnd = bracket_round_first_loser_round($node);
  
  for ($r=$lrnd; $r<=bracket_round_last_loser_round($node); $r+=2) {
  
    if ($r == $lrnd) {
      $l = $left;
      $hh = $height;
      $sp = $spacing;
      // number of winner matches
      $mc = count($node->comp) / 2;
      // spacing down to bottom bracket
      $t = $top + ($spacing * ($mc + 0.25));
      // starting loser match count
      $mc /= 2;
    }
    else {
      $l += $width;
      $t += ($hh / 2);
      $hh = $sp;
      $sp = $sp * 2;
      $mc /= 2;
    }
    bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $r, 1, $mc, 'L', TRUE);

    // break if last round
    if ($r == bracket_round_last_loser_round($node)) {
      break;
    }
    
    $l += $width;
    if ($node->round[$lrnd]->match[1]->winner_comp == 1) {
      $t += ($hh / 2);
    }
    else {
      $t -= ($hh / 2);
    }
    bracket_image_drawbracketset($img, $node, $l, $t, $width, $hh, $sp, $r+1, 1, $mc, 'L', TRUE);
  }

  // 3rd and 4th place
  $l += $width;
  $t += ($hh / 4);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $width, $node->result[3]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $width, $node->result[3]->comment, $_bracket_image_fg_color, 'C');
  $t += ($hh / 2);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l, $t-2, $width, $node->result[4]->cname, $_bracket_image_fg_color, 'C');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l, $t+$h+1, $width, $node->result[4]->comment, $_bracket_image_fg_color, 'C');

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
    bracket_image_insert_image($img, $node->logopath, $iwidth-200, 120, 200);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth/2, $iheight-75, 75, TRUE);
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
function mde4champ_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  mde4champ_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function mde4champ_pdf_page($node, &$pdf) {

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
  $top = 1.5;
  $left = 1.0;
  $width = 1.5;
  $height = 1.0;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // set font sizes
  $_bracket_pdf_font_xlarge = 14.0;
  $_bracket_pdf_font_large = 12.0;
  $_bracket_pdf_font_norm = 10.0;
  $_bracket_pdf_font_small = 9.0;
  $_bracket_pdf_font_xsmall = 8.0;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // winner rounds
  for ($r=1; $r<=bracket_round_last_winner_round($node); $r++) {

    if ($r == 1) {  
      $l = $left;
      $hh = $height;
      $sp = $spacing;
      $t = $top;
      // number of winner matches
      $mc = count($node->comp) / 2;
    }
    else {
      $l += $width;
      $t += ($hh / 2);
      $hh = $sp;
      $sp = $sp * 2;
      $mc /= 2;
    }
    
    bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $r, 1, $mc, 'L', TRUE);
  }
  
  // winner and runner-up
  $l += $width;
  $t += ($hh / 3);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[1]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[1]->comment, 0, 0, 'C');
  $t += ($hh / 3);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[2]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[2]->comment, 0, 0, 'C');

  // loser rounds
  $lrnd = bracket_round_first_loser_round($node);
  
  for ($r=$lrnd; $r<=bracket_round_last_loser_round($node); $r+=2) {
  
    if ($r == $lrnd) {
      $l = $left;
      $hh = $height;
      $sp = $spacing;
      // number of winner matches
      $mc = count($node->comp) / 2;
      // spacing down to bottom bracket
      $t = $top + ($spacing * ($mc + 0.25));
      // starting loser match count
      $mc /= 2;
    }
    else {
      $l += $width;
      $t += ($hh / 2);
      $hh = $sp;
      $sp = $sp * 2;
      $mc /= 2;
    }
    bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $r, 1, $mc, 'L', TRUE);

    // break if last round
    if ($r == bracket_round_last_loser_round($node)) {
      break;
    }
    
    $l += $width;
    if ($node->round[$lrnd]->match[1]->winner_comp == 1) {
      $t += ($hh / 2);
    }
    else {
      $t -= ($hh / 2);
    }
    bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $hh, $sp, $r+1, 1, $mc, 'L', TRUE);
  }

  // 3rd and 4th place
  $l += $width;
  $t += ($hh / 4);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[3]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[3]->comment, 0, 0, 'C');
  $t += ($hh / 2);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[4]->cname, 0, 0, 'C');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[4]->comment, 0, 0, 'C');

  // bracket title
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_xlarge);
  $pdf->setXY(2.0, 0.75);
  $pdf->multicell(5.0, 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_large);
  $pdf->setXY(2.0, 1.0);
  $pdf->multicell(5.0, 0.125, $node->subtitle, 0, 'C');

  // bracket comments
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->setXY(2.0, 1.25);
  $pdf->multicell(5.0, 0.125, $node->comments, 0, 'C');

  // bracket footnote
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_small);
  $pdf->setXY($left, 10.5);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, 6.0, 1.5, 2.0);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, $iwidth / 2, 10.0, 0.75, TRUE);
  }
}

