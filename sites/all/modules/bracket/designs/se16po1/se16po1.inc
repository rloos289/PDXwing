<?php

/**
 * @file
 * This file contains the required functions for the se16po1 bracket design
 *
 * This design consists of 16 competitors in a one round playoff bracket
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function se16po1_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 16);
  // add rounds
  bracket_design_create_winner_rounds($node, 1);
  // name the rounds
  $node->round[1]->name = t('Round') . ' 1';
  // add playoff results
  bracket_design_create_playoff_results($node);
}

/**
 * Produce a png image for the requested bracket object
 *
 * @param $b
 *   the bracket object
 * @return
 *   the png image
 */
function se16po1_image($node) {

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
  $tb = $spacing * 4.5;

  // setup image
  $iwidth = 700;
  $iheight = 1000;
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

  // round 1
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, $spacing, 1, 1, 4, 'L');
  bracket_image_drawbracketset($img, $node, $left, $top+$tb, $width, $height, $spacing, 1, 5, 8, 'L');

  // results
  $l = $left + $width;
  $t = $top + ($height / 2);
  for ($i=1; $i<=count($node->result)/2; $i++) {
    imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
    bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t-5, $w, $node->result[$i]->cname, $_bracket_image_fg_color, 'L');
    bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+10, $w, $node->result[$i]->comment, $_bracket_image_fg_color, 'L');
    imageline($img, $l, $t+$tb, $l+$width, $t+$tb, $_bracket_image_fg_color);
    bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb-5, $w, $node->result[$i+4]->cname, $_bracket_image_fg_color, 'L');
    bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$tb+10, $w, $node->result[$i+4]->comment, $_bracket_image_fg_color, 'L');
    $t += $spacing;
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
    bracket_image_insert_image($img, $node->logopath, $iwidth-200, 80, 200);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_image_insert_image($img, $node->sponsorlogopath, $iwidth-100, $iheight-300, 75, TRUE);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_image_setup_bar_colors($node, $img);
    $t = $top + $tb - ($spacing / 2);
    imagefilledrectangle($img, $left, $t-($h/2)-2, $l, $t+($h/2)+2, $_bracket_image_bar_bg_color);
    $t += 4;
    for ($i=1; $i<=sizeof($node->round) && $i <= 4; $i++) {
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
function se16po1_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se16po1_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se16po1_pdf_page($node, &$pdf) {

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
  $left = 0.75;
  $width = 1.4;
  $height = 0.6;
  $spacing = $height * 1.75;
  $pdf->setMargins($top, $left);

  // spacing between top and bottom brackets
  $tb = $spacing * 4.5;

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // set font sizes
  $_bracket_pdf_font_norm = 8;
  $_bracket_pdf_font_small = 7;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round 1
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, $spacing, 1, 1, 4, 'L');
  bracket_pdf_drawbracketset($pdf, $node, $left, $top + $tb, $width, $height, $spacing, 1, 5, 8, 'L');

  // results
  $l = $left + $width;
  $t = $top + ($height / 2);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  for ($i=1; $i<=count($node->result)/2; $i++) {
    $pdf->line($l, $t, $l+$width, $t);
    $pdf->setXY($l, $t-0.125);
    $pdf->cell($width, 0.125, $node->result[$i]->cname, 0, 0, 'L');
    $pdf->setXY($l, $t);
    $pdf->cell($width, 0.125, $node->result[$i]->comment, 0, 0, 'L');
    $pdf->line($l, $t+$tb, $l+$width, $t+$tb);
    $pdf->setXY($l, $t+$tb-0.125);
    $pdf->cell($width, 0.125, $node->result[$i+4]->cname, 0, 0, 'L');
    $pdf->setXY($l, $t+$tb);
    $pdf->cell($width, 0.125, $node->result[$i+4]->comment, 0, 0, 'L');
    $t += $spacing;
  }
  
  // bracket title
  $pdf->setFont($_bracket_pdf_font_name, 'BI', $_bracket_pdf_font_xlarge);
  $pdf->setXY($left, 0.5);
  $pdf->multicell($iwidth - ($left * 2) , 0.25, $node->title, 0, 'C');

  // bracket subtitle
  $pdf->setFont($_bracket_pdf_font_name, 'BI', '10');
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
    bracket_pdf_insert_image($pdf, $node->logopath, 6.0, 1.75, 2.0);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 5.25, 7.5, 0.75);
  }

  // bracket bar
  if ($node->options['image_options']['show_bracket_bar']) {
    bracket_pdf_setup_bar_colors($node, $pdf);
    $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
    $t = $top + $tb - ($spacing / 2);
    for ($i=1; $i<=count($node->round); $i++) {
      $pdf->setXY($left + (($i-1) * $width), $t);
      $pdf->cell($width, 0.125, $node->round[$i]->comment, 0, 0, 'C', TRUE);
    }
  }
}