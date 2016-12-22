<?php

/**
 * @file
 * This file contains the class definitions for the bracket module
 *
 * @author Jim Bullington <jimb@jrbcs.com>
 */

/**
 * Class to contain info attached to a bracket node
 */
class Bracket {

  /**
   * bracket subtitle
   */
  public $subtitle;
  /**
   * bracket comments
   */
  public $comments;
  /**
   * activity
   */
  public $sport;
  /**
   * division
   */
  public $division;
  /**
   * season
   */
  public $season;
  /**
   * group
   */
  public $brgroup;
  /**
   * bracket footer
   */
  public $footer;
  /**
   * path to bracket logo image
   */
  public $logopath;
  /**
   * path to bracket sponsor logo image
   */
  public $sponsorlogopath;
  /**
   * bracket design code
   */
  public $design;
  /**
   * array of bracket competitors
   */
  public $comp;
  /**
   * array of bracket rounds
   */
  public $round;
  /**
   * array of bracket results
   */
  public $result;
  /**
   * array of bracket options
   */
  public $options;

  /**
   * Constructs a Bracket object
   */
  function Bracket() {

    $this->subtitle = '';       // bracket comments, etc
    $this->comments = '';
    $this->sport = '';
    $this->division = '';
    $this->season = '';
    $this->brgroup = '';
    $this->footer = '';
    $this->logopath = '';       // paths to logo image files
    $this->sponsorlogopath = '';
    $this->design = '';         // bracket design (module name)
    $this->comp = array();      // bracket competitors
    $this->round = array();     // bracket rounds
    $this->result = array();    // bracket results
    $this->options = array();   // bracket options
    
    // set default options
    $this->options['display'] = variable_get('bracket_default_display', 'Image');
    $this->options['hide_pdf']= FALSE;
    $this->options['show_match_id'] = FALSE;
    $this->options['image_options']['fg_color'] = '';
    $this->options['image_options']['bg_color'] = '';
    $this->options['image_options']['show_bracket_bar'] = FALSE;
    $this->options['image_options']['bar_fg_color'] = '';
    $this->options['image_options']['bar_bg_color'] = '';
    $this->options['image_options']['image_fonts']['image_font'] = '';
    $this->options['image_options']['image_fonts']['image_font_bold'] = '';
    $this->options['image_options']['image_fonts']['image_font_italic'] = '';
    $this->options['image_options']['image_fonts']['image_font_bolditalic'] = '';
    $this->options['image_options']['pdf_font'] = '';
  }
}

/**
 * Class to contain competitor info
 */
class Bracket_Competitor {

  /**
   * competitor name
   */
  public $name;
  /**
   * competitor incoming seed
   */
  public $seedin;

  /**
   * Constructs a Bracket_Competitor object
   */
  function Bracket_Competitor() {

    $this->name = '';           // competitor name
    $this->seedin = '';         // competitor seed
  }
}

/**
 * Class to contain round info
 */
class Bracket_Round {

  /**
   * round id (index)
   */
  public $id;
  /**
   * name of this round
   */
  public $name;
  /**
   * indicates a loser round
   */
  public $loser;
  /**
   * indicates a first round
   */
  public $first;
  /**
   * round comment
   */
  public $comment;
  /**
   * array of matches in this round
   */
  public $match;

  /**
   * Constructs a Bracket_Round object
   */
  function Bracket_Round() {

      $this->id = 0;            // round id (index)
      $this->name = '';         // round name
      $this->loser = FALSE;     // round is a loser round if true
      $this->first = FALSE;     // round is a first found if true
      $this->comment = '';      // round comment
      $this->match = array();   // round matches
  }
}

/**
 * Class to contain match info
 */
class Bracket_Match {

  /**
   * match id (unique across entire bracket)
   */
  public $id;
  /**
   * array of match competitors
   */
  public $compid;
  /**
   * array of match competitor names
   */
  public $cname;
  /**
   * array of match competitor comments
   */
  public $comp_comment;
  /**
   * array of match scores
   */
  public $score;
  /**
   * array of match home indicators
   */
  public $home;
  /**
   * array of match win indicators
   */
  public $win;
  /**
   * array of match comments
   */
  public $comment;
  /**
   * pointer to winner's next match
   */
  public $winner_match;
  /**
   * competitor index of winner's next match
   */
  public $winner_comp;
  /**
   * pointer to loser's next match
   */
  public $loser_match;
  /**
   * competitor index of loser's next match
   */
  public $loser_comp;
  /**
   * winner's result index
   */
  public $winner_result;
  /**
   * loser's result index
   */
  public $loser_result;
  /**
   * use result if winner is this index
   */
  public $win_use_result;

  /**
   * Constructs a Bracket_Match object
   */
  function Bracket_Match() {

    $this->compid = array();
    $this->cname = array();
    $this->comp_comment = array();
    $this->score = array();
    $this->home = array();
    $this->win = array();
    $this->comment = array();

    $this->id = 0;              // match id
    $this->compid[1] = 0;       // competitor 1 id (index)
    $this->cname[1] = '';       // competitor 1 name
    $this->comp_comment[1] = '';// competitor 1 comment
    $this->score[1] = '';       // competitor 1 score
    $this->home[1] = FALSE;     // competitor 1 home indicator
    $this->win[1] = FALSE;      // competitor 1 win indicator
    $this->compid[2] = 0;       // competitor 2 ...
    $this->cname[2] = '';
    $this->comp_comment[2] = '';
    $this->score[2] = '';
    $this->home[2] = FALSE;
    $this->win[2] = FALSE;
    $this->comment[1] = '';     // match comments
    $this->comment[2] = '';
    $this->winner_match = 0;    // route winner to this match id
    $this->winner_comp = 0;     // and competitor (1 or 2)
    $this->loser_match = 0;     // route loser to this match id
    $this->loser_comp = 0;      // and competitor (1 or 2)
    $this->winner_result = 0;   // route winner to this result (place)
    $this->loser_result = 0;    // route loser to this result (place)
    $this->win_use_result = 0;  // a win by this competitor (1 or 2) places and completes the bracket, otherwise routing is used
  }
}

/**
 * Class to contain result info
 */
class Bracket_Result {

  /**
   * result competitor id
   */
  public $compid;
  /**
   * result competitor name
   */
  public $cname;
  /**
   * result comment
   */
  public $comment;
  /**
   * result competitor outgoing seed
   */
  public $seedout;

  /**
   * Constructs a Bracket_Result object
   */
  function Bracket_Result() {

    $this->compid = 0;          // competitor id (index)
    $this->cname = '';          // competitor name
    $this->comment = '';        // result comment
    $this->seedout = '';        // result seed
  }
}

