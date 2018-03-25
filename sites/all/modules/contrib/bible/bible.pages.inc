<?php

// Read functions.
function bible_all($bibles_ = NULL, $book = NULL, $chapter = NULL, $verse = NULL) {
  // Arg: bible/book/chap/verse.
  $page_content = '';

  $bible_count = _bible_get_bible_count();

  if ($bible_count === 0) {
    return t('Please import Bible Context File (*.bc) to use Bible module.');
  }
  else {
    if ($bibles_ === NULL) {
      drupal_goto('bible/' . _bible_get_select_bid());
    }
    $bibles = _bible_get_bibles_array($bibles_);
    if (count($bibles) === 0 || $bibles === NULL) {
      return t('Format invalid. Please check.');
    }
    $default_bible = $bibles[0];
    $bibles_ = implode('_', $bibles);

    if (!empty($book)) {
      $book = _bible_get_from_book_alias($book);
    }

    // Output bible breadcrumb.
    $page_content .= theme('bible_breadcrumb', array(
      'bibles' => $bibles,
      'book' => $book,
      'chapter' => $chapter,
    ));

    // Display specific chapter.
    if (!empty($chapter)) {
      $chapter_query = db_select('bible_context', 'bc')
        ->fields('bc')
        ->condition('bid', $bibles, 'IN')
        ->condition('book', $book)
        ->condition('chapter', $chapter)
        ->orderBy('verse')
        ->orderBy('linemark', 'desc');
      foreach ($bibles as $bid) {
        $chapter_query->orderBy('FIELD(bid, ' . $bid . ')');
      }
      $chapter_data = $chapter_query
        ->execute();

      // Mask verse.
      $versemask = array();
      // Highlight.
      if ($verse !== NULL) {
        $singleverse = (strpos($verse, '-') === FALSE);
        if ($singleverse) {
          $versemask[$verse][] = 'highlight';
        }
        else {
          $vv = explode('-', $verse);
          for ($i = $vv[0]; $i <= $vv[1]; $i++) {
            $versemask[$i][] = 'highlight';
          }
        }
      }

      // Goldenverse.
      $versemask = _bible_get_goldenversemask($book, $chapter, $versemask);

      // Refverse.
      $versemask = _bible_get_refversemask($book, $chapter, $versemask);

      // Note.
      if (variable_get('bible_config_showbiblenote', 0) == 1) {
        $versemask = _bible_get_notemask($book, $chapter, $versemask);
      }

      // Theme output.
      $page_content .= theme('bible_chapter', array(
        'bibles' => $bibles,
        'book' => $book,
        'chapter' => $chapter,
        'chapter_data' => $chapter_data,
        'versemask' => $versemask,
      ));
    }
    // Display chapter list.
    elseif (!empty($book)) {
      $book_data = db_query('SELECT * FROM {bible_book_name} ' .
        'WHERE bid = ? AND book = ?',
        array(check_plain($default_bible), check_plain($book))
      )
        ->fetch();

      // Theme output.
      $page_content .= theme('bible_select_chapter', array(
        'bibles' => $bibles_,
        'book' => $book,
        'book_data' => $book_data,
      ));
    }
    // Display book list.
    else {
      $bible = db_query('SELECT * FROM {bible_list} WHERE bid = ?',
        array(check_plain($default_bible))
      )
        ->fetch();
      if ($bible === NULL) {
        $page_content .= t('No such Bible.');
      }
      else {
        $book_data = db_query('SELECT * FROM {bible_book_name} ' .
          'WHERE bid = ? ORDER BY bkid', array($bible->bid));

        // Theme output.
        $page_content .= theme('bible_select_book', array(
          'bibles' => $bibles_,
          'book_data' => $book_data,
        ));
      }
    }
    // Output links.
    $page_content .= theme('bible_links', array(
      'bibles' => $bibles,
      'bible_count' => $bible_count,
    ));

    if (!empty($chapter) && $chapter_data->rowCount() > 0) {
      $page_content .= theme('bible_chapter_data', array(
        'book' => $book,
        'chapter' => $chapter,
      ));
    }
  }

  return $page_content;
}
