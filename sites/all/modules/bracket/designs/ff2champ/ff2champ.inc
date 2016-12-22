<?php

/**
 * @file
 * This file contains the required functions for the ff2champ bracket design
 *
 * This design consists of 2 competitors in 4 single elimination brackets
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function ff2champ_create(&$node) {

  // add competitors
  bracket_design_create_competitors($node, 8);
  // add rounds
  $c = 1;
  $mid = 1;
  for ($i=1; $i<=4; $i++) {
    $node->round[$i] = new Bracket_Round();
    $node->round[$i]->first = TRUE;
    $node->round[$i]->name = t('Bracket') . ' ' . $i . ' - ' . t('Final');
    $node->round[$i]->match[1] = new Bracket_Match();
    $node->round[$i]->match[1]->id = $mid++;
    $node->round[$i]->match[1]->compid[1] = $c++;
    $node->round[$i]->match[1]->compid[2] = $c++;
    $node->round[$i]->match[1]->winner_result = $i;
    $node->result[$i] = new Bracket_Result();
    $node->result[$i]->comment = t('Bracket') . ' ' . $i . ' - ' . t('Champion');
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
function ff2champ_image($node) {

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
  $width = 140;
  $height = 75;
  $spacing = $height * 1.75;
  $gap = $spacing * 2.5;

  // setup image
  $iwidth = 800;
  $iheight = 700;
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
  $_bracket_image_font_small = 8.5;
  $_bracket_image_font_xsmall = 7;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // bracket 1
  $l = $left + ($width / 2);
  $t = ($iheight / 4) - ($height / 2);
  bracket_image_imageTextAlign($img, $_bracket_image_font_large, $l, $t-40, $width, $node->round[1]->comment, $_bracket_image_bar_fg_color, 'L');
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $height, $spacing, 1, 1, 1, 'L');
  $l += $width;
  $t += ($height / 2);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-5, $w, $node->result[1]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$h, $w, $node->result[1]->comment, $_bracket_image_fg_color, 'L');

  // bracket 2
  $r = $iwidth - $left - ($width / 2);
  $t = ($iheight / 4) - ($height / 2);
  bracket_image_imageTextAlign($img, $_bracket_image_font_large, $r-$width, $t-40, $width, $node->round[2]->comment, $_bracket_image_bar_fg_color, 'R');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $height, $spacing, 2, 1, 1, 'R');
  $t += ($height / 2);
  $r -= $width;
  imageline($img, $r, $t, $r-$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t-5, $w, $node->result[2]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$h, $w, $node->result[2]->comment, $_bracket_image_fg_color, 'R');

  // bracket 3
  $t = $iheight - ($iheight / 4) - ($height / 2);
  $l = $left + ($width / 2);
  bracket_image_imageTextAlign($img, $_bracket_image_font_large, $l, $t-40, $width, $node->round[3]->comment, $_bracket_image_bar_fg_color, 'L');
  bracket_image_drawbracketset($img, $node, $l, $t, $width, $height, $spacing, 3, 1, 1, 'L');
  $l += $width;
  $t += ($height / 2);
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-5, $w, $node->result[3]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$h, $w, $node->result[3]->comment, $_bracket_image_fg_color, 'L');

  // bracket 4
  $t = $iheight - ($iheight / 4) - ($height / 2);
  $r = $iwidth - $left - ($width / 2);
  bracket_image_imageTextAlign($img, $_bracket_image_font_large, $r-$width, $t-40, $width, $node->round[4]->comment, $_bracket_image_bar_fg_color, 'R');
  bracket_image_drawbracketset($img, $node, $r, $t, $width, $height, $spacing, 4, 1, 1, 'R');
  $r -= $width;
  $t += ($height / 2);
  imageline($img, $r, $t, $r-$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t-5, $w, $node->result[4]->cname, $_bracket_image_fg_color, 'R');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $r-10, $t+$h, $w, $node->result[4]->comment, $_bracket_image_fg_color, 'R');

  // draw some dividing lines
  $l = $left + ($width / 2);
  $t = $iheight / 2;
  for ($i=0; $i<3; $i++) {
    imageline($img, $l, $t, $l+$width+($width/2), $t, $_bracket_image_fg_color);
    $t++;
  }
  
  $r = $iwidth - $left - ($width / 2);
  $t = $iheight / 2;
  for ($i=0; $i<3; $i++) {
    imageline($img, $r, $t, $r-$width-($width/2), $t, $_bracket_image_fg_color);
    $t++;
  }
  
  $c = ($iwidth / 2) - 1;
  $t = 100;
  for ($i=0; $i<3; $i++) {
    imageline($img, $c, $t, $c, $t+($height*2), $_bracket_image_fg_color);
    $c++;
  }
  
  $c = ($iwidth / 2) - 1;
  $t = $iheight - ($iheight / 4) - $height;
  for ($i=0; $i<3; $i++) {
    imageline($img, $c, $t, $c, $t+($height*2), $_bracket_image_fg_color);
    $c++;
  }
  
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
    bracket_image_insert_image($img, $node->logopath, $iwidth/2, $iheight/2, 150, TRUE);
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
function ff2champ_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  ff2champ_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function ff2champ_pdf_page($node, &$pdf) {

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
  $left = 1.0;
  $width = 1.25;
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

  // bracket 1
  $l = $left;
  $t = ($iheight / 4) - ($height / 2);
  $pdf->setXY($l, $t-0.4);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->round[1]->comment, 0, 0, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $height, $spacing, 1, 1, 1, 'L');
  $l += $width;
  $t += ($height / 2);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[1]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[1]->comment, 0, 0, 'L');
  
  // bracket 2
  $r = $iwidth - $left;
  $t = ($iheight / 4) - ($height / 2);
  $pdf->setXY($r-$width, $t-0.4);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->round[2]->comment, 0, 0, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $height, $spacing, 2, 1, 1, 'R');
  $r -= $width;
  $t += ($height / 2);
  $pdf->line($r, $t, $r-$width, $t);
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[2]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[2]->comment, 0, 0, 'R');

  // bracket 3
  $t = $iheight - ($iheight / 4) - ($height / 2);
  $l = $left;
  $pdf->setXY($l, $t-0.4);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->round[3]->comment, 0, 0, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $l, $t, $width, $height, $spacing, 3, 1, 1, 'L');
  $l += $width;
  $t += ($height / 2);
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[3]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[3]->comment, 0, 0, 'L');

  // bracket 4
  $t = $iheight - ($iheight / 4) - ($height / 2);
  $r = $iwidth - $left;
  $pdf->setXY($r-$width, $t-0.4);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->round[4]->comment, 0, 0, 'R');
  bracket_pdf_drawbracketset($pdf, $node, $r, $t, $width, $height, $spacing, 4, 1, 1, 'R');
  $r -= $width;
  $t += ($height / 2);
  $pdf->line($r, $t, $r-$width, $t);
  $pdf->setXY($r-$width, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[4]->cname, 0, 0, 'R');
  $pdf->setXY($r-$width, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[4]->comment, 0, 0, 'R');

  // draw some dividing lines
  $pdf->setlinewidth(0.03);
  $l = $left;
  $t = $iheight / 2;
  $pdf->line($l, $t, $l+$width+($width/2), $t);
  
  $r = $iwidth - $left;
  $t = $iheight / 2;
  $pdf->line($r, $t, $r-$width-($width/2), $t);
  
  $c = $iwidth / 2;
  $t = 2.0;
  $pdf->line($c, $t, $c, $t+2.0);
  
  $c = $iwidth / 2;
  $t = ($iheight / 2) + 1.5;
  $pdf->line($c, $t, $c, $t+2.0);

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
    bracket_pdf_insert_image($pdf, $node->logopath, $iwidth/2, $iheight/2, 1.75, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 4.25, 9.5, 0.75, TRUE);
  }
}