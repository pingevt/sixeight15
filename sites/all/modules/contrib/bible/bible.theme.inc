<?php
/**
 * @file
 * Theme functions for Bible module.
 */

/**
 * Theme the bible_multiread form.
 */
function theme_bible_multiread($variables) {
  $form = $variables['form'];

  $rows = array();
  foreach ($form['bible'] as $key => $element) {
    // Do not take form control structures.
    if (is_array($element) && element_child($key)) {
      $rows[] = array(
        check_plain($key),
        $form['bible'][$key]['#value'],
        drupal_render($form['enabled'][$key]),
        drupal_render($form['bible_default'][$key]),
      );
    }
  }
  $header = array(
    array('data' => t('#')),
    array('data' => t('Bible name')),
    array('data' => '<input type="checkbox" class="selectall" checked />' .
      t('Selected')
    ),
    array('data' => t('Base Bible')),
  );
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}

function theme_bible_breadcrumb($variables) {
  $bibles = $variables['bibles'];
  $book = $variables['book'];
  $chapter = $variables['chapter'];
  $default_bible = $bibles[0];
  $bibles_ = implode('_', $bibles);

  $page_content = '<div class="bible-breadcrumb">';
   $bname = _bible_get_bible_name($default_bible);
  if (!empty($bibles_)) {
    $page_content .= l($bname, 'bible/' . $bibles_);
  }
  $cname = '';
  if (!empty($book)) {
    $cname = _bible_get_chapter_name($default_bible, $book);
    $page_content .= ' &raquo; ' . l(
      $cname,
      'bible/' . $bibles_ . '/' . $book
    );
  }
  $chapname = '';
  if (!empty($chapter)) {
    $chapname = t('Chapter @chap', array('@chap' => $chapter));
    $page_content .= ' &raquo; '. l(
      $chapname,
      'bible/' . $bibles_ . '/' . $book . '/' . $chapter
    );
  }
  $page_content .= '</div>';
  $title = $cname . ' ' . $chapname;
  if (count($bibles) <= 1) {
    $title .= ($cname === '' ? '' : ' - ') . $bname;
  }
  if (trim($title) === '') {
    $title = t('Bible');
  }
  drupal_set_title($title);

  return $page_content;
}

function theme_bible_chapter($variables) {
  $bibles = $variables['bibles'];
  $book = $variables['book'];
  $chapter = $variables['chapter'];
  $chapter_data = $variables['chapter_data'];
  $versemask = $variables['versemask'];

  $ismulti = (count($bibles) > 1);
  if ($ismulti) {
    for ($i = 0; $i < count($bibles); $i++) {
      $bibles[$i] = _bible_get_bible_id_number($bibles[$i]);
      $biblename[$bibles[$i]] = _bible_get_bible_bsn($bibles[$i]);
    }
  }
  $page_content = '';

  if ($book !== '' && $chapter !== '') {
    // Generate 'prev chapter' and 'next chapter' links.
    $pnchap = explode(':',
      _bible_get_prevnextchap($book . ':' . $chapter, $bibles[0])
    );
    $bibles_ = implode('_', $bibles);
    $pnline1 = '&#171;' . l(
      $pnchap[2] . ' ' . t('Chapter @chap', array(
        '@chap' => $pnchap[1],
      )),
      'bible/' . $bibles_ . '/' . $pnchap[0] . '/' . $pnchap[1]
    );
    $pnline2 = l(
      $pnchap[5] . ' ' . t('Chapter @chap', array(
        '@chap' => $pnchap[4],
      )),
      'bible/' . $bibles_ . '/' . $pnchap[3] . '/' . $pnchap[4]
    ) . '&#187;';
  }

  // Output chapter content.
  $page_content .= '<dl class="bible-chapter-content">';
  $curverse = 0;
  $bbpos = 0;
  global $user;
  foreach ($chapter_data as $verse) {
    if ($verse->linemark == '*') {
      $page_content .= '<dt class="header">' . check_plain($verse->context) .
        '&nbsp;</dt>';
    }
    else {
      $showchapternumber = variable_get('bible_config_showchapternumber', 0);
      $verse_ = ($showchapternumber ? $verse->chapter . ':' : '') .
        $verse->verse;
      $page_content .= '<span';
      if ($curverse != $verse->verse) {
        $bls = $verse->book . ':' . $verse->chapter . ':' . $verse->verse;
        $mark = isset($versemask[$verse->verse]);
        // Check mark highlight.
        if ($mark && in_array('highlight', $versemask[$verse->verse])) {
          $page_content .= ' class="bible-chapter-highlight"';
        }
        $page_content .= '><dt';
        $page_content .= '><a name="v' . $verse->verse . '"></a>';
        if ($user->uid > 0) {
          $page_content .= '<span class="chap-verse" vset="' .
            bible_verseset_status($bls) . '">' .
            '<verse para="' . $bibles_ . '/' . $bls . '">' . $verse_ .
            '</verse><span class="vsetimg">';
        }
        else {
          $page_content .= $verse->verse;
        }
        // Check mark goldenverse.
        if ($mark) {
          global $imagedir;
          for ($i = 0; $i < 6; $i++) {
            $vsetitem = ($i === 0 ? 'goldenverse' : 'verseset' . $i);
            $icon = ($i === 0 ? 'icon_star' : 'vset_' . $i) . '.gif';
            if (isset($versemask[$verse->verse][$vsetitem])) {
              $page_content .= '<image src=' . $imagedir . $icon . ' />';
            }
          }
        }
        if ($user->uid > 0) {
          $page_content .= '</span></span>';
        }
        $page_content .= '</dt';
        $curverse = $verse->verse;
        $bbpos = 0;
      }
      $page_content .= '><dd class="bible-context-' . ($bbpos % 7) . '">';
      if ($ismulti) {
        $multireadbiblename = variable_get('bible_config_multireadbiblename', 0);
        if ($multireadbiblename) {
          $page_content .= '(<b>' .
            check_plain($biblename[$bibles[$bbpos]]) . '</b>) ';
        }
      }
      $page_content .= _bible_sn_replace(check_plain($verse->context));

      if (isset($versemask[$verse->verse]['refverse']) && $versemask[$verse->verse]['refverse'] !== '') {
        $refverse = $versemask[$verse->verse]['refverse'];
        global $imagedir;
        $idname = 'refverse_' . $verse->verse;
        $page_content .= '<a href="' . url('bible/refverse/') . $bls .
          '/' . $bibles_ . '"><span class="bls" id="' . $idname .
          '" width="100px;"><img src="' . $imagedir .
          'refverse.gif" /></span></a><span class="popup" id="popup-' .
          $idname . '" style="position:absolute;visibility:hidden;">';
        $data = explode(';', $refverse);
        $rvline = '';
        foreach ($data as $bls) {
          if ($bls !== '') {
            $rvline .= ($rvline !== '' ? '<br />' : '');
            $bb = explode(':', $bls);
            $rvline .= '<span class="vref" id="' . $bls . '">' .
              _bible_get_chapter_sname($bibles[0], $bb[0]) . ':' . $bb[1] .
              ':' . $bb[2] . '</span>';
          }
        }
        $page_content .= $rvline . '</span>';
      }

      if (isset($versemask[$verse->verse]['note']) && $versemask[$verse->verse]['note'] !== '') {
        $notes = $versemask[$verse->verse]['note'];
        global $imagedir;
        $bnline = '';
        foreach ($notes as $note) {
          // No need for a check_plain() on any of $note, as they can be only
          // numbers.
          // @see _bible_get_notemask()
          $bnline .= '<img class="note" id="note-' . $note[0] . '" src="' .
            $imagedir . 'note' . $note[1] . '.gif" />';
        }
        $page_content .= $bnline;
      }

      $page_content .= '</dd></span>';
      $bbpos++;
    }
  }
  $page_content .= '</dl>';

  if ($ismulti) {
    $page_content .= '<h3 class="title">' . t('Bible Color Mark') . '</h3>';
    $page_content .= '<ul class="bible-color-mark-list">';
    for ($i = 0; $i < count($bibles); $i++) {
      $page_content .= '<li class="bible-context-' . $i . '">' .
        check_plain(_bible_get_bible_name($bibles[$i])) . '</li>';
    }
    $page_content .= '</ul>';
  }

  // Output prev/next chapter.
  if ($pnline1 !== '' && $pnline2 !== '') {
    $page_content .= '<div class="bible-chapter-seek">';
    $page_content .= '<ul class="links clear-block">';
    $page_content .= '<li class="first bible-prev-chapter">' . $pnline1 . '</li>';
    $page_content .= '<li class="last bible-next-chapter">' . $pnline2 . '</li>';
    $page_content .= '</ul>';
    $page_content .= '</div>';
  }

  return $page_content;
}

function theme_bible_chapter_data($variables) {
  $book = $variables['book'];
  $chapter = $variables['chapter'];

  global $bibledataxml;
  if (_bible_get_bibledata($book, $chapter) === '') {
    return '';
  }
  global $imagedir;
  $page_content = '<div class="bible-chapter-data">';
  $page_content .= '<ul class="links inline">';
  $doc = new DOMDocument();
  $doc->loadXML($bibledataxml);
  $root = $doc->documentElement;
  $domXPath = new DOMXPath($doc);
  global $bdtypelist;
  foreach ($bdtypelist as $li => $name) {
    if ($li == 'refverse') {
      continue;
    }
    if ($domXPath->query('//bibledata/' . $li)->length > 0) {
      $rows = array();
      $page_content .= '<fieldset><legend>' . $name . '</legend>';
      foreach ($domXPath->query('//bibledata/' . $li . '/data') as $keyDOM) {
        $did = check_plain($keyDOM->getAttribute('did'));
        $datalink = '<img src="' . $imagedir . $li . '.gif" />';
        $datalink .= l(
          $keyDOM->textContent,
          BIBLE_DATA_DEFAULT_URL . '/fwd/' . $did,
          array('attributes' => array('target' => 'bibledata'))
        );
        $resplink = l(
          '<img src="' . $imagedir . 'recommend.gif">',
          BIBLE_DATA_DEFAULT_URL . '/rec/' . $did,
          array(
            'html' => TRUE,
            'attributes' => array(
              'title' => t('Recommend this bible data.'),
              'target' => 'bibledata',
            ),
          )
        );
        $resplink .= l(
          '<img src="' . $imagedir . 'opposite.gif">',
          BIBLE_DATA_DEFAULT_URL . '/opp/' . $did,
          array(
            'html' => TRUE,
            'attributes' => array(
              'title' => t('Opposite this bible data.'),
              'target' => 'bibledata',
            ),
          )
        );
        $resplink .= l(
          '<img src="' . $imagedir . 'link-broken.gif">',
          BIBLE_DATA_DEFAULT_URL . '/linkbrk/' . $did,
          array(
            'html' => TRUE,
            'attributes' => array(
              'title' => t('Report this data link borken.'),
              'target' => 'bibledata',
            ),
          )
        );
        $resplink .= l(
          '<img src="' . $imagedir . 'unfit.gif">',
          BIBLE_DATA_DEFAULT_URL . '/unfit/' . $did,
          array(
            'html' => TRUE,
            'attributes' => array(
              'title' => t('Report this data content unfit.'),
              'target' => 'bibledata',
            ),
          )
        );
        $rows[] = array(
          $datalink,
          array(
            'data' => $resplink,
            'align' => 'right',
          ),
        );
      }
      $page_content .= theme('table', array('rows' => $rows));
      $page_content .= '</fieldset>';
    }
  }
  $page_content .= '</ul></div>';
  return $page_content;
}

function theme_bible_select_chapter($variables) {
  $bibles_ = $variables['bibles'];
  $book = $variables['book'];
  $book_data = $variables['book_data'];
  $page_content = '<h3 class="title">' . t("Select Chapter") . '</h3>';
  $page_content .= '<ul class="bible-chapter-list">';
  for ($i = 1; $i <= $book_data->chap; $i++) {
    $page_content .= '<li>' . l(
      $i,
      'bible/' . $bibles_ . '/' . $book . '/' . $i
    ) . '</li>';
  }
  $page_content .= '</ul><br />';
  return $page_content;
}

function theme_bible_select_book($variables) {
  $bibles_ = $variables['bibles'];
  $book_data = $variables['book_data'];
  $lastbook = '';
  $booklines = '';
  foreach ($book_data as $qr) {
    if ($lastbook == 'MAL' || $lastbook == 'REV') {
      $booklines .= '|';
    }
    $book = check_plain($qr->book);
    $booklines .= '<span class="book ' . drupal_html_class('book-' . $book) .
      '">' .
      l(check_plain($qr->fname), 'bible/' . $bibles_ . '/' . $book) .
      '</span>';
    $lastbook = $qr->book;
  }
  $bookline = explode('|', $booklines);

  $page_content = '<div class="bible-book-list">';
  $header = array();
  $rows = array();
  if (strlen($bookline[0]) > 0) {
    $rows[] = array(
      'data' => array(
        t('Old Testament'),
        $bookline[0],
      ),
      'class' => array('old-testament'),
    );
  }
  if (isset($bookline[1]) && strlen($bookline[1]) > 0) {
    $rows[] = array(
      'data' => array(
        t('New Testament'),
        $bookline[1],
      ),
      'class' => array('new-testament'),
    );
  }
  if (isset($bookline[2]) && strlen($bookline[2]) > 0) {
    $rows[] = array(
      'data' => array(
        t('Apocrypha'),
        $bookline[2],
      ),
      'class' => array('apocrypha'),
    );
  }
  $page_content .= theme('table', array('header' => $header, 'rows'=> $rows));
  $page_content .= '</div>';
  return $page_content;
}

function theme_bible_links($variables) {
  $bibles = $variables['bibles'];
  $bible_count = $variables['bible_count'];
  $page_content = '<hr /><div class="bible-links"><ul class="links inline">';
  $arg2 = check_plain(arg(2));
  $arg3 = check_plain(arg(3));
  if (count($bibles) == 1) {
    if ($bible_count > 1) {
      $biblelist = _bible_get_bible_list();
      $href = "'" . url('bible') . "/'+this.value";
      $hrefpara = (!empty($arg2) ? '/' . $arg2 : '') .
        (!empty($arg3) ? '/' . $arg3 : '');
      if ($hrefpara !== '') {
        $href .= "+'" . $hrefpara . "';";
      }
      global $imagedir;
      $page_content .= '<li class="bible-selector">';
      $page_content .= '<img src=' . $imagedir . 'change.gif alt="' .
        t('Change Bible') . '" title="' . t('Change Bible') .
        '" />';
      $page_content .= '<select onchange="location.href=' . $href .
        '" class="bible-select">';
      foreach ($biblelist as $bid => $bb) {
        $page_content .= '<option value="' . $bid . '"';
        if ($bid == arg(1)) {
          $page_content .= ' selected="selected"';
        }
        $page_content .= '>' . check_plain($bb) . '</option>';
      }
      $page_content .= '</select></li>';
    }
    if (arg(1) !== '') {
      $href = "'" . url('bible') . '/' . arg(1) . "/'+this.value";
      $href .= (!empty($arg3) ? "+'/" . $arg3 . "';" : '');
      $page_content .= '<li class="book-selector">';
      $page_content .= '<select onchange="location.href=' . $href .
        '" class="book-select">';
      // No need to check_plain(arg(1)), as the underlying code handles both
      // numeric and string cases properly.
      $bid = _bible_get_bible_id_number(arg(1));
      $book_data = db_select('bible_book_name', 'bbn')
        ->fields('bbn')
        ->condition('bid', $bid)
        ->orderBy('bkid')
        ->execute();
      foreach ($book_data as $qr) {
        $page_content .= '<option value="' . check_plain($qr->book) . '"';
        if (!empty($arg2) && $qr->book == $arg2) {
          $page_content .= ' selected="selected"';
        }
        $page_content .= '>' . check_plain($qr->fname) . '</option>';
      }
      $page_content .= '</select></li>';

      if (arg(2) !== '') {
        $href = "'" . url('bible') . '/' . arg(1) . '/' . $arg2 .
          "/'+this.value";
        $book_data = db_select('bible_book_name', 'bbn')
          ->fields('bbn')
          ->condition('bid', $bid)
          ->condition('book', $arg2)
          ->execute()
          ->fetch();
        if (!empty($book_data)) {
          $page_content .= '<li class="chap-selector">';
          $page_content .= '<select onchange="location.href=' . $href .
            '" class="chap-select">';
          for ($i = 1; $i <= $book_data->chap; $i++) {
            $page_content .= '<option value="' . $i . '"';
            if ($i == $arg3) {
              $page_content .= ' selected="selected"';
            }
            $page_content .= '>' . $i . '</option>';
          }
          $page_content .= '</select></li>';
        }
      }
    }
    $page_content .= '<br/>';
  }

  $page_content .= '<li class="first bible-search">' .
    l(t('Search Keyword in Bible'), 'bible/search') . '</li>';
  $page_content .= '<li>' . l(t('My Verses'), 'bible/vset/list') .
    '</li>';
  if ($bible_count > 1) {
    if (count($bibles) > 1) {
      $page_content .= '<li id="bible-plain-read">' .
        l(t('Bible Plain-Read'), 'bible') . '</li>';
    }
    else {
      $page_content .= '<li class="last bible-multi-read">' .
        l(t('Bible Multi-Read'), 'bible/multiread') . '</li>';
    }
  }
  else {
    $page_content .= '<li>' . l(t('Select Bible'), 'bible') .
      '</li>';
  }
  if (variable_get('bible_config_showbiblenote', 0) == 1) {
    $page_content .= '<li>' . l(t('My Notes'), 'bible/note') .
      '</li>';
  }
  $page_content .= '</ul></div>';
  return $page_content;
}
