<?php

/**
 * @file
 * This file contains the required functions for the se2champ bracket design
 *
 * This design consists of 2 competitors in a single elimination bracket
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Create a bracket tree in the given node object
 *
 * @param $node
 *   the node object
 */
function se2champ_create(&$node) {

  // set bracket bar option
  $node->options['image_options']['show_bracket_bar'] = TRUE;

  // add competitors
  bracket_design_create_competitors($node, 2);
  // add rounds
  bracket_design_create_winner_rounds($node);
  // name the rounds
  $node->round[1]->name = t('Finals');
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
function se2champ_image($node) {

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
  $top = 160;
  $left = 40;
  $width = 200;
  $height = 100;

  // setup image
  $iwidth = 700;
  $iheight = 450;
  $img = imagecreatetruecolor($iwidth, $iheight);

  // allocate colors
  bracket_image_setup_colors($node, $img);

  // setup fonts
  bracket_image_setup_fonts($node);

  // fill in background
  imagefill($img, 0, 0, $_bracket_image_bg_color);

  // font sizes
  $_bracket_image_font_xlarge = 16;
  $_bracket_image_font_large = 14;
  $_bracket_image_font_norm = 12;
  $_bracket_image_font_small = 10;
  $_bracket_image_font_xsmall = 8;

  // font height
  $bbox = imagettfbbox($_bracket_image_font_norm, 0, $_bracket_image_font, 'Q');
  $h = $bbox[1] - $bbox[7];
  $w = 10;

  // round comment
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $left, $top-40, $width, $node->round[1]->comment, $_bracket_image_fg_color, 'C');

  // finals
  bracket_image_drawbracketset($img, $node, $left, $top, $width, $height, 0, 1, 1, 1, 'L');

  // winner
  $t = $top + ($height / 2);
  $l = $left + $width;
  imageline($img, $l, $t, $l+$width, $t, $_bracket_image_fg_color);
  bracket_image_imagetextalign($img, $_bracket_image_font_large, $l+2, $t-2, $width, $node->result[1]->cname, $_bracket_image_fg_color, 'L');
  bracket_image_imagetextalign($img, $_bracket_image_font_norm, $l+2, $t+$h+1, $width, $node->result[1]->comment, $_bracket_image_fg_color, 'L');

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
    bracket_image_insert_image($img, $node->logopath, $iwidth-200, 50, 175);
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
function se2champ_pdf($node) {

  // produce and return pdf as a string
  $pdf = new PDF('P', 'in', 'letter');
  se2champ_pdf_page($node, $pdf);
  return $pdf->output('', 'S');
}

function se2champ_pdf_page($node, &$pdf) {

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
  $top = 4.5;
  $left = 2.0;
  $width = 2.0;
  $height = 1.0;
  $pdf->setMargins($top, $left);

  // set pdf colors
  bracket_pdf_setup_colors($node, $pdf);

  // set pdf font
  bracket_pdf_setup_font($node, $pdf);

  // set font sizes
  $_bracket_pdf_font_norm = 10;
  $_bracket_pdf_font_small = 8;
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);

  // round comment
  $pdf->setXY($left, $top-0.5);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->round[1]->comment, 0, 0, 'C');
  
  // semis
  bracket_pdf_drawbracketset($pdf, $node, $left, $top, $width, $height, 0, 1, 1, 1, 'L');

  // winner
  $t = $top + ($height / 2);
  $l = $left + $width;
  $pdf->line($l, $t, $l+$width, $t);
  $pdf->setXY($l, $t-0.125);
  $pdf->setFont($_bracket_pdf_font_name, 'B', $_bracket_pdf_font_large);
  $pdf->cell($width, 0.125, $node->result[1]->cname, 0, 0, 'L');
  $pdf->setXY($l, $t);
  $pdf->setFont($_bracket_pdf_font_name, '', $_bracket_pdf_font_norm);
  $pdf->cell($width, 0.125, $node->result[1]->comment, 0, 0, 'L');

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
  $pdf->setXY($left, $iheight - 1.0);
  $pdf->multicell($iwidth - ($left * 2), 0.125, $node->footer, 0, 'C');

  // bracket logo
  if ($node->logopath != '') {
    bracket_pdf_insert_image($pdf, $node->logopath, 4.25, 2.0, 2.0, TRUE);
  }

  // sponsor logo
  if ($node->sponsorlogopath != '') {
    bracket_pdf_insert_image($pdf, $node->sponsorlogopath, 4.25, 9.0, 0.75, TRUE);
  }
}