<?php
/**
 * @file
 * Strong's number related functions for Bible module.
 */

function bible_sn($snid, $sn) {
  if (!empty($sn)) {
    $sn_object = db_select('bible_strongnumber', 'bsn')
      ->fields('bsn')
      ->condition('snid', $snid)
      ->condition('sn', $sn)
      ->execute()
      ->fetch();
    if ($sn_object === NULL) {
      $top_snid = db_select('bible_sn_list', 'bsnl')
        ->fields('bsnl', array('snid'))
        ->range(0, 1)
        ->execute()
        ->fetchField();
      if (!empty($top_snid) && ($top_snid != $snid)) {
        drupal_goto('bible/sn/' . $snid . '/' . $snid);
      }
      else {
        return t('Strong\'s Number File not imported; Or Strong\'s Number is mistype.');
      }
    }
    if (variable_get('bible_sn_select', 0) === 0) {
      variable_set('bible_sn_select', $snid);
    }
    $sn_content = _bible_sn_replace(check_plain($sn_object->content));
    $output = str_replace(
      "\n",
      '<br />',
      t('Strong\'s Number') . '[<b>' . $sn . '</b>]<br />' . $sn_content
    );
    $snselect = variable_get('bible_snsearch_select', 0);
    if ($snselect <> 0) {
      $output .= '<hr />[' .
        l(
          'Search for all appearance',
          'bible/snsearch/' . $snselect . '/' . $sn
        ) .
        ']';
    }
    return $output;
  }
  elseif (!empty($snid)) {
    drupal_goto('bible/sn/' . variable_get('bible_sn_select', 0) . '/' . $snid);
  }
}

function bible_snajax($sn) {
  $snid = variable_get('bible_sn_select', 0);
  $snlist = db_select('bible_strongnumber', 'bsn')
    ->fields('bsn')
    ->condition('snid', $snid)
    ->condition('sn', $sn)
    ->execute();
  if ($snobj = $snlist->fetch()) {
    $sndata = $snobj->sn . "\r" . str_replace("\n", '', check_plain($snobj->content));
    $sndata = str_replace("\r", '|', $sndata);
    if (strlen($sndata) > 300) {
      $sndata = substr($sndata, 0, 300) . '...';
    }
    print $sndata;
  }
  else {
    print '';
  }
  drupal_exit();
}

function bible_ajax_vcontent($bls) {
  $bid = _bible_get_select_bid();
  print _bible_get_verse_content2($bls, $bid, '@c', '[@v]@c');
  drupal_exit();
}

/**
 * Search Bible for Strong note.
 * BdB: URL is something like: bible/snsearch/20/H1000
 */
function bible_sn_search($bid, $strong_number) {
  $arg3 = check_plain(arg(3));
  if (!empty($arg3)) {
    $query = db_select('bible_context')
      ->fields('bible_context')
      ->condition('bid', $bid)
      ->condition('context', '%<' . strtoupper(arg(3)) . '>%', 'LIKE')
      ->condition('linemark', '*', '<>')
      ->orderBy('vsid');
    $count_query = clone ($query);
    $result_set = $query
      ->extend('PagerDefault')
      ->limit(10)
      ->execute();
    $rows = array();
    foreach ($result_set as $verse){
      $bls = _bible_get_chapter_sname($bid, $verse->book) . ':' . $verse->chapter;
      $context = str_replace('<', '&lt;', $verse->context);
      $context = str_replace(
        '&lt;' . arg(3) . '>',
        '<span class="bible-strong">&lt;' . $arg3 . '></span>',
        $context
      );
      $rows[] = array(
        l(
          $bls . ':' . $verse->verse,
          'bible/' . $bid . '/' . $verse->book . '/' . $verse->chapter
        ),
        $context,
      );
    }
    drupal_add_css(drupal_get_path('module', 'bible') . '/bible.css');
    $count = $count_query->execute()
      ->rowCount();
    $output = t('Search in Bible [@bible] for Strong\'s Number [@kw], total found [@count] time(s).', array(
      '@bible' => _bible_get_bible_name($bid),
      '@kw' => $arg3,
      '@count' => $count,
    ));
    $header = array();
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $output .= theme('pager');
    return $output;
  }
  elseif (!empty($bid)) {
    drupal_goto('bible/sn/' . variable_get('bible_sn_select', 0) . '/' . $bid);
  }
}
