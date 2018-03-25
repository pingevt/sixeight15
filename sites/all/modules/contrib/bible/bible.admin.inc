<?php

/**
 * Returns the admin list in HTML.
 */
function bible_admin_list() {
  $page_content = '';
  $page_content .= '<fieldset><legend>' . t('Bible List') . '</legend>';
  $queryResult = db_query('SELECT * FROM {bible_list}');
  $rows = array();
  foreach ($queryResult as $bb) {
    $book_count = db_query('SELECT COUNT(*) AS c ' .
      'FROM {bible_book_name} WHERE bid = :bid', array(
        ':bid' => $bb->bid,
      ))
      ->fetchField();
    $verse_count = db_query('SELECT COUNT(*) AS c ' .
      'FROM {bible_context} WHERE bid = :bid', array(
        ':bid' => $bb->bid,
      ))
      ->fetchField();

    $bid = $bb->bid;
    $biblename = l($bb->bname, 'bible/' . $bb->bid);
    $action = l(t('Delete'), 'admin/config/bible/delete/' . $bb->bid);
    if ($bb->bid != variable_get('bible_select', 0)) {
      $action .= ' ' . l(t('Select'), 'admin/config/bible/select/' . $bb->bid);
    }
    else {
      $bid = '[' . $bid . ']*';
    }
    $rowdata = array(
      $bid,
      $bb->bsn,
      $biblename,
      $bb->lang,
      $bb->serialversion,
      $book_count,
      $verse_count,
      $action,
    );
    if ($bb->bid == variable_get('bible_select', 0)) {
      $rows[] = array('data' => $rowdata, 'class' => array('selected'));
    }
    else {
      $rows[] = array('data' => $rowdata);
    }
  }
  $header = array(
    array('data' => '#'),
    array('data' => t('ShortName')),
    array('data' => t('Bible Name')),
    array('data' => t('Language')),
    array('data' => t('Version Serial')),
    array('data' => t('Book Count')),
    array('data' => t('Verse Count')),
    array('data' => t('Action')),
  );
  $page_content .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
  $page_content .= '</fieldset>';

  $page_content .= '<fieldset><legend>' . t('Strong\'s Number List') . '</legend>';
  $queryResult = db_query('SELECT * FROM {bible_sn_list}');
  $rows1 = array();
  foreach ($queryResult as $sn) {
    $qr1 = db_query('SELECT COUNT(*) as c FROM {bible_strongnumber} WHERE snid = :snid', array(
        ':snid' => $sn->snid
      ))
      ->fetch();
    $snid = $sn->snid;
    $action = l(t('Delete'), 'admin/config/bible/sndelete/' . $sn->snid);
    if ($sn->snid != variable_get('bible_sn_select', 0)) {
      $action .= ' ' . l(t('Select'), 'admin/config/bible/snselect/' . $sn->snid);
    }
    else {
      $snid = '[' . $snid . ']*';
    }
    $rowdata = array($snid, $sn->snname, $sn->lang, $qr1->c, $action);
    if ($sn->snid == variable_get('bible_sn_select', 1)) {
      $rows1[] = array(
        'data' => $rowdata,
        'style' => 'background-color:#FFCCCC',
      );
    }
    else {
      $rows1[] = array('data' => $rowdata);
    }
  }
  $header = array(
    array('data' => '#'),
    array('data' => t('Strong\'s Number Version')),
    array('data' => t('Language')),
    array('data' => t('SN Count')),
    array('data' => t('Action')),
  );
  $page_content .= theme('table', array(
    'header' => $header,
    'rows' => $rows1,
  ));
  $page_content .= '</fieldset>';

  $page_content .= '<fieldset><legend>' .
    t('Strong\'s Number Bible Select') .
    '</legend>';
  $query = db_select('bible_list', 'bl');
  $bc = $query->join('bible_context', 'bc', 'bl.bid = %alias.bid');
  $query->fields('bl')
    ->fields($bc);
  $queryResult = $query->condition('book', 'GEN')
    ->condition('chapter', 1)
    ->condition('verse', 1)
    ->condition('linemark', '')
    ->condition('context', '%' . db_like('<H0430>') . '%', 'LIKE')
    ->execute();
  $bbsnrows = array();
  foreach ($queryResult as $bb) {
    $bid = $bb->bid;
    $action = '';
    if ($bb->bid != variable_get('bible_snsearch_select', 0)) {
      $action .= ' ' . l(t('Select'), 'admin/config/bible/snsselect/' . $bb->bid);
    }
    else {
      $bid = '[' . $bid . ']*';
    }
    $rowdata = array($bid, $bb->bsn, $bb->bname, $bb->lang, $action);
    if ($bb->bid == variable_get('bible_snsearch_select', 0)) {
      $bbsnrows[] = array(
        'data' => $rowdata,
        'style' => 'background-color:#FFCCCC',
      );
    }
    else {
      $bbsnrows[] = array('data' => $rowdata);
    }
  }
  $header = array(
    array('data' => '#'),
    array('data' => t('ShortName')),
    array('data' => t('Bible Name')),
    array('data' => t('Language')),
    array('data' => t('Action')),
  );
  $page_content .= theme('table', array(
    'header' => $header,
    'rows' => $bbsnrows,
  ));
  $page_content .= '</fieldset>';
  return $page_content;
}

/**
 * Builds the bible import form.
 */
function bible_admin_import($form, &$form_state) {
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bible Import'),
  );
  $form['import']['file'] = array(
    '#type' => 'file',
    '#title' => t('Bible Context file'),
    '#size' => 50,
    '#description' => t('A bible context (.bc) file.') .
      l('[' . t('Download Page') . ']', 'http://drupalbible.org/download') .
      l('[' . t('Web Import') . ']', 'admin/config/bible/webimport'),
  );
  $form['import']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import .bc'),
    '#submit' => array('_bible_import_read'),
  );

  $form['importsn'] = array(
    '#type' => 'fieldset',
    '#title' => t('Strong\'s Number Import'),
  );
  $form['importsn']['filesn'] = array(
    '#type' => 'file',
    '#title' => t('Bible Strong\'s Number file'),
    '#size' => 50,
    '#description' => t('A bible Strong\'s number (.sn) file.') .
      l('[' . t('Download Page') . ']', 'http://drupalbible.org/node/2#SN'),
  );
  $form['importsn']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import .sn'),
    '#submit' => array('_bible_strongnumber_import_read'),
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  return $form;
}

/**
 * Process the bible file import form submission.
 */

/**
 * Converts encoding from charset X to utf8 if needed.
 */
function _bible_convertCharacterEncoding($texts) {
  $characterEncoding = mb_detect_encoding($texts, 'UTF-8, UTF-16, ISO-8859-1, ISO-8859-15, Windows-1252, ASCII');
  switch ($characterEncoding) {
    case 'UTF-8':
      // Do nothing.
      break;

    case 'ISO-8859-1':
      $texts = utf8_encode($texts);
      break;

    default:
      $texts = mb_convert_encoding($texts,'UTF-8',$characterEncoding);
      break;
  }
  return $texts;
}

/**
 * Form submit handler for bible import.
 */
function _bible_import_read($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('txt bc sn'));
  $file = file_save_upload('file', $validators);
  if (!isset($file) || strlen($file->filename) == 0) {
    $message = t('Please assign .bc file to import.');
    drupal_set_message($message, 'error');
    return FALSE;
  }
  // File will get closed by PHP on return.
  $fd = fopen($file->destination, 'rb');
  if (empty($fd)) {
    $message = t('The bible import failed, because the file @filename could not be read.', array(
      '@filename' => $file->filename,
    ));
    drupal_set_message($message, 'error');
    return FALSE;
  }
  // If not in 'safe mode', increase the maximum execution time.
  if (!ini_get('safe_mode')) {
    set_time_limit(240);
  }

  $status = '';
  $lineno = 0; // Current line
  $bid = -1;
  $bkid = 1;
  while (!feof($fd)) {
    // A line should not be this long.
    $line = fgets($fd, 10 * 1024);
    $lineno++;
    $line = trim(strtr($line, array("\\\n" => '')));
    if (strlen($line) > 0) {
      switch (substr($line, 0, 1)) {
        case '*': // Section Declare.
          if (strncmp('*Bible', $line, 6) == 0) {
            $status = 'B';
          }
          if (strncmp('*Chapter', $line, 8) == 0) {
            $status = 'C';
            db_delete('bible_book_name')
              ->condition('bid', $bid)
              ->execute();
          }
          if (strncmp('*Context', $line, 8) == 0) {
            $status = 'V';
            db_delete('bible_context')
              ->condition('bid', $bid)
              ->execute();
          }
          break;

        case '#': // Comment.
          break;

        case '^':  // Variable Setting.
          if (strncmp('^Bible', $line, 6) == 0) {
            $line = _bible_convertCharacterEncoding($line);
            $data = explode('|', $line);
            $bid = _bible_get_bible_id2($data[1], $data[2]);
            if ($bid === '') {
              $message = t('The bible fix file error. Bible name:@bsn, Language:@lang.', array(
                '@bsn' => $data[1],
                '@lang' => $data[2],
              ));
              drupal_set_message($message, 'error');
              return FALSE;
            }
            if (count($data) > 3) {
              db_update('bible_list')
                ->fields(array('serialversion' => $data[3]))
                ->condition('bid', $bid)
                ->execute();
            }
          }
          if (strncmp('^Context', $line, 8) == 0) {
            $status = 'V';
          }
          break;

        default: // Context Data.
          $line = _bible_convertCharacterEncoding($line);
          $data = explode('|', $line);

          switch ($status) {
            case 'B':
              db_insert('bible_list')
                ->fields(array(
                  'bsn' => $data[0],
                  'bname' => $data[1],
                  'lang' => $data[2],
                ))
                ->execute();
              $bid = _bible_get_bible_id2($data[0], $data[2]);
              if (count($data) > 3) {
                db_update('bible_list')
                  ->fields(array('serialversion' => $data[3]))
                  ->condition('bid', $bid)
                  ->execute();
              }
              break;

            case 'C':
              if ($bid > -1) {
                db_insert('bible_book_name')
                  ->fields(array(
                    'bid' => $bid,
                    'bkid' => $bkid,
                    'book' => $data[0],
                    'fname' => $data[1],
                    'sname' => $data[2],
                    'chap' => $data[3],
                  ))
                  ->execute();
                $bkid++;
              }
              break;

            case 'V':
              if ($bid > -1) {
                db_insert('bible_context')
                  ->fields(array(
                    'bid' => $bid,
                    'book' => $data[0],
                    'chapter' => $data[1],
                    'verse' => $data[2],
                    'linemark' => $data[3],
                    'context' => $data[4],
                  ))
                  ->execute();
              }
              break;

          }
          break;

      }
    }
  }
  if (variable_get('bible_select', 0) == 0) {
    variable_set('bible_select', $bid);
  }
  watchdog('Bible', 'Bible File Loaded. Lines: @lineno', array(
    '@lineno' => $lineno,
  ));
  $form_state['redirect'] = 'admin/config/bible/list';
}

/**
 * Form submit handler for Strong's Number import.
 */
function _bible_strongnumber_import_read($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('txt bc sn'));
  $file = file_save_upload('filesn',$validators);
  if (!isset($file) || strlen($file->filename) == 0) {
    $message = t('Please assign .sn file to import.');
    drupal_set_message($message, 'error');
    return FALSE;
  }
  watchdog('Bible', 'File Submit received. [@filename]', array(
    '@filename' => $file->filename,
  ));
  // File will get closed by PHP on return.
  $fd = fopen($file->destination, 'rb');
  if (empty($fd)) {
    $message = t('The Strong\'s number import failed, because the file @filename could not be read.', array(
      '@filename' => $file->filename,
    ));
    drupal_set_message($message, 'error');
    return FALSE;
  }
  // If not in 'safe mode', increase the maximum execution time.
  if (!ini_get('safe_mode')) {
    set_time_limit(240);
  }
  $lineno = 0; // Current line.
  $snid = 0;
  $sn = '';
  $content = '';
  $errcount = 0;
  while (!feof($fd)) {
    // A line should not be this long.
    $line = fgets($fd, 10 * 1024);
    $lineno++;
    if (strlen($line) > 0) {
      switch (substr($line, 0, 1)) {
        case '*':
          if (strncmp('*SN', $line, 3) == 0) {
            $line = fgets($fd, 10*1024); // A line should not be this long.
            $line = trim(strtr($line, array("\\\n" => '')));
            $data = explode(',', $line);
            // BdB: I have no idea how we can hit this code
            db_query('INSERT INTO {bible_sn_list} (snname, lang) VALUES (:snname, :lang)', array(
              ':snname' => $data[0],
              ':lang' => $data[1],
            ));
            $snobj = db_query('SELECT snid FROM {bible_sn_list} WHERE snname = :snname AND lang = :lang', array(
                ':snname' => $data[0],
                ':lang' => $data[1],
              ))
              ->fetch();
            $snid = $snobj->snid;
          }
          else {
            if ($sn !== '' && $snid > 0) {
              $line = trim(strtr($line, array("\\\n" => '')));
              try {
                db_query('INSERT INTO {bible_strongnumber} (snid, sn, content) VALUES (:snid, :sn, :content)', array(
                  ':snid' => $snid,
                  ':sn' => $sn,
                  ':content' => $content,
                ));
              }
              catch (PDOException $e) {
                watchdog('Bible', 'Import sn file erorr. SN:@sn, Message:@errmsg', array(
                  '@sn' => $sn,
                  '@errmsg' => $e->getMessage(),
                ));
                $errcount++;
              }
            }
            $sn = trim(substr($line, 1));
            $content = '';
          }
          break;

        case '^':
          if (strncmp('^SN', $line, 3) == 0) {
            // A line should not be this long.
            $line = fgets($fd, 10 * 1024);
            $line = trim(strtr($line, array("\\\n" => '')));
            $data = explode(',', $line);
            // BdB: no idea how to hit this code.
            $snobj = db_query('SELECT snid FROM {bible_sn_list} WHERE snname = :snname AND lang = :lang', array(
                ':snname' => $data[0],
                ':lang' => $data[1],
              ))
              ->fetch();
            $snid = $snobj->snid;
            db_query('DELETE FROM {bible_strongnumber} WHERE snid = :snid', array(
              ':snid' => $snid,
            ));
          }
          break;

        default:
          $content .= $line;
          break;
      }
    }
  }
  db_query('INSERT INTO {bible_strongnumber} (snid, sn, content) VALUES (:snid, :sn, :content)', array(
    ':snid' => $snid,
    ':sn' => $sn,
    ':content' => $content,
  ));
  if (variable_get('bible_sn_select', 0) == 0) {
    variable_set('bible_sn_select', $snid);
  }
  if ($errcount == 0) {
    watchdog('Bible', 'Bible Strong\'s Number File Loaded. Lines: @lineno', array(
      '@lineno' => $lineno,
    ));
  }
  else {
    drupal_set_message(t('Import with errors. Please see <a href="!link">System log</a>.', array(
      '!link' => url('admin/reports/dblog'),
    )), 'error');
  }
  $form_state['redirect'] = 'admin/config/bible/list';
}

/**
 * Handles bible import from the web.
 *
 * @param string $bid
 *   The bible ID.
 * @param string $startvsid
 *   Verse ID to start with.
 * @return null|string|void
 *   HTML to display.
 */
function bible_admin_webimport($bid = '', $startvsid = '') {
  if ($bid === '') {
    global $language;
    $xml = drupal_http_request(BIBLE_WEBIMPORT_URL . '////' . $language->language);
    if ($xml->code == 200) {
      $doc = new DOMDocument();
      $doc->loadXML($xml->data);
      $domXPath = new DOMXPath($doc);
      $header = array(
        array('data' => t('ShortName')),
        array('data' => t('Bible name')),
        array('data' => t('Language')),
        array('data' => t('Version on Server')),
        array('data' => t('Status')),
      );
      $rows = array();
      foreach ($domXPath->query('//webimport/bible') as $keyDOM) {
        $bsn = $keyDOM->textContent;
        $bid = $keyDOM->getAttribute('bid');
        $lang = $keyDOM->getAttribute('lang');
        $serialversion = $keyDOM->getAttribute('serialversion');
        $bb = _bible_get_bible2($bsn, $lang);
        if ($bb !== NULL) {
          $svcomp = strcmp($serialversion, $bb->serialversion);
          if ($svcomp > 0) {
            $status = BIBLE_STATUS_IMPORTED_VERSION_UPDATE_AVAILABLE;
          }
          else {
            if ($svcomp < 0) {
              $status = BIBLE_STATUS_IMPORTED_VERSION_ERROR;
            }
            else {
              $status = BIBLE_STATUS_IMPORTED_VERSION_OK;
            }
          }
          if ($status == BIBLE_STATUS_IMPORTED_VERSION_OK) {
            $action = t('Already imported');
          }
          else {
            $action = l(
              t('Update available'),
              'admin/config/bible/webimport/' . $bid
            );
          }
        }
        else {
          $status = BIBLE_STATUS_NOT_IMPORTED;
          $action = l(
            t('Click to import'),
            'admin/config/bible/webimport/' . $bid
          );
        }
        $rows[] = array($bsn,
          $keyDOM->getAttribute('bname'),
          $lang,
          '<span class="update' . $status . '">' . $serialversion . '</span>',
          $action,
        );
      }
      $page_content = theme('table', array(
        'header' => $header,
        'rows' => $rows,
      ));
      $page_content .= t('Need some other bible? Please suggest in <a href="!link">Bible Forum</a>', array(
        '!link' => 'http://drupalbible.org/forum/5',
      ));
      return $page_content;
    }
    return t('Network error. Code: @code, error: @error', array(
      '@code' => $xml->code,
      '@error' => $xml->error,
    ));
  }

  if ($startvsid === '') {
    $xml = drupal_http_request(BIBLE_WEBIMPORT_URL . '/' . $bid);
    if ($xml->code == 200) {
      $doc = new DOMDocument();
      $doc->loadXML($xml->data);
      $domXPath = new DOMXPath($doc);
      $bbnode = $domXPath->query('//webimport/bible')->item(0);
      $bsn = $bbnode->textContent;
      $lang = $bbnode->getAttribute('lang');
      $serialversion = $bbnode->getAttribute('serialversion');
      $start = $bbnode->getAttribute('start');
      drupal_add_js('misc/progress.js', array('type' => 'file', 'weight' => JS_LIBRARY));
      drupal_add_js(drupal_get_path('module', 'bible') . '/bible_webimport.js');
      drupal_add_js(
        array('bibleurl' => url('admin/config/bible/webimport')),
        array(
          'type' => 'setting',
          'scope' => JS_DEFAULT,
        )
      );
      drupal_add_js(
        array('biblepara' => '/' . $bid . '/' . $start),
        array(
          'type' => 'setting',
          'scope' => JS_DEFAULT,
        )
      );
      drupal_add_js(
        array('bibleimsg' => t('Starting web import')),
        array(
          'type' => 'setting',
          'scope' => JS_DEFAULT,
        )
      );
      drupal_add_js(
        array('bibleemsg' => t('Error encountered.')),
        array(
          'type' => 'setting',
          'scope' => JS_DEFAULT,
        )
      );
      $_SESSION['webimport_start'] = $start;
      $_SESSION['webimport_next'] = $start;
      $_SESSION['webimport_total'] = $bbnode->getAttribute('count');

      $bid2 = _bible_get_bible_id2($bsn, $lang);
      if ($bid2 > 0) {
        $bid = db_query('SELECT MAX(bid) FROM {bible_list}')
          ->fetchField() + 1;
        db_delete('bible_book_name')
          ->condition('bid', $bid)
          ->execute();
        db_delete('bible_context')
          ->condition('bid', $bid)
          ->execute();
      }
      else {
        db_insert('bible_list')
          ->fields(array(
            'bsn' => $bsn,
            'bname' => $bbnode->getAttribute('bname'),
            'lang' => $lang,
            'serialversion' => $serialversion,
          ))
          ->execute();
        $bid = _bible_get_bible_id2($bsn, $lang);
      }
      if ($bid === '') {
        return t('Data error on webimport.');
      }
      variable_set('bible_webimport_bid', $bid);
      variable_set('bible_webimport_bid2', $bid2);
      variable_set('bible_webimport_serialversion', $serialversion);
      foreach ($domXPath->query('//webimport/book') as $keyDOM) {
        $data = explode('|', $keyDOM->textContent);
        $bkid = $keyDOM->getAttribute('bkid');
        db_insert('bible_book_name')
          ->fields(array(
          'bid' => $bid,
          'bkid' => $bkid,
          'book' => $data[0],
          'fname' => $data[1],
          'sname' => $data[2],
          'chap' => $data[3],
        ))
        ->execute();
      }

      $_SESSION['bible_webimport_bid'] = $bid;

      $page_content = '<div id="progress"></div><p id="wait">' .
        t('Please wait while bible content is being imported.') . '</p>';
      return $page_content;
    }
    return t('Network error. Code: @code, error: @error', array(
      '@code' => $xml->code,
      '@error' => $xml->error,
    ));
  }

  $nextvsid = $_SESSION['webimport_next'];
  $xml = drupal_http_request(BIBLE_WEBIMPORT_URL . '/' . $bid . '/' . $nextvsid);
  if ($xml->code == 200) {
    $doc = new DOMDocument();
    $doc->loadXML($xml->data);
    $domXPath = new DOMXPath($doc);

    $nextvsid = $domXPath->query('//webimport')
      ->item(0)
      ->getAttribute('endvsid') + 1;
    $_SESSION['webimport_next'] = $nextvsid;

    $bid = $_SESSION['bible_webimport_bid'];
    foreach ($domXPath->query('//webimport/verse') as $keyDOM) {
      $data = explode('|', $keyDOM->textContent);
      db_insert('bible_context')
        ->fields(array(
          'bid' => $bid,
          'book' => $data[0],
          'chapter' => $data[1],
          'verse' => $data[2],
          'linemark' => $data[3],
          'context' => $data[4],
        ))
        ->execute();
    }

    // Update progressbar.
    // HTTP Post required.
    if ($_SERVER['REQUEST_METHOD'] != 'POST') {
      drupal_set_message('HTTP Post is required.', 'error');
      drupal_set_title('Error');
      return '';
    }
    $total = $_SESSION['webimport_total'];
    $start = $_SESSION['webimport_start'];
    $percentage = floor(($nextvsid - $start) / $total * 100);
    $message = ($nextvsid - $start) . '/' . $total;
    print drupal_json_encode(array(
      'status' => TRUE,
      'percentage' => $percentage,
      'message' => $message,
    ));
    if ($percentage == 100) {
      $bid = variable_get('bible_webimport_bid', '-1');
      $bid2 = variable_get('bible_webimport_bid2', '-2');
      $serialversion = variable_get('bible_webimport_serialversion', '');
      if ($bid2 > 0) {
        db_delete('bible_book_name')
          ->condition('bid', $bid2)
          ->execute();
        db_update('bible_book_name')
          ->fields(array(
            'bid' => $bid2,
          ))
          ->condition('bid', $bid)
          ->execute();
        db_delete('bible_context')
          ->condition('bid', $bid2)
          ->execute();
        db_update('bible_context')
          ->fields(array(
            'bid' => $bid2,
          ))
          ->condition('bid', $bid)
          ->execute();
        db_update('bible_list')
          ->fields(array(
            'serialversion' => $serialversion,
          ))
          ->condition('bid', $bid2)
          ->execute();
      }
      variable_del('bible_webimport_bid');
      variable_del('bible_bible_webimport_bid2');
    }
    return;
  }
  return t('Network error. Code: @code, error: @error', array(
    '@code' => $xml->code,
    '@error' => $xml->error,
  ));
}

/**
 * Check bible imported from the web.
 *
 * @return array
 *   Count for each status, keys:
 *   - BIBLE_STATUS_IMPORTED_VERSION_ERROR,
 *   - BIBLE_STATUS_IMPORTED_VERSION_OK,
 *   - BIBLE_STATUS_IMPORTED_VERSION_UPDATE_AVAILABLE,
 *   - BIBLE_STATUS_NOT_IMPORTED.
 */
function _bible_webimport_check() {
  $wi_status = array(
    BIBLE_STATUS_IMPORTED_VERSION_ERROR => 0,
    BIBLE_STATUS_IMPORTED_VERSION_OK => 0,
    BIBLE_STATUS_IMPORTED_VERSION_UPDATE_AVAILABLE => 0,
    BIBLE_STATUS_NOT_IMPORTED => 0,
  );
  $xml = drupal_http_request(BIBLE_WEBIMPORT_URL);
  if ($xml->code == 200) {
    $doc = new DOMDocument();
    $doc->loadXML($xml->data);
    $domXPath = new DOMXPath($doc);
    foreach ($domXPath->query('//webimport/bible') as $keyDOM) {
      $bsn = $keyDOM->textContent;
      $lang = $keyDOM->getAttribute('lang');
      $serialversion = $keyDOM->getAttribute('serialversion');
      $bb = _bible_get_bible2($bsn, $lang);
      if ($bb !== NULL) {
        $svcomp = strcmp($serialversion, $bb->serialversion);
        if ($svcomp > 0) {
          $status = BIBLE_STATUS_IMPORTED_VERSION_UPDATE_AVAILABLE;
        }
        else {
          if ($svcomp < 0) {
            $status = BIBLE_STATUS_IMPORTED_VERSION_ERROR;
          }
          else {
            $status = BIBLE_STATUS_IMPORTED_VERSION_OK;
          }
        }
      }
      else {
        $status = BIBLE_STATUS_NOT_IMPORTED;
      }
      $wi_status[$status]++;
    }
  }
  return $wi_status;
}

/**
 * Builds the general bible admin config form.
 */
function bible_admin_config($form, &$form_state) {
  // Common config section.
  $form['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bible Parameter Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['config']['multireadbiblename'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Bible Name when Multi-Read.'),
    '#default_value' => variable_get('bible_config_multireadbiblename', '0'),
    '#description' => t('Show Bible Name before verse when user read chapter in multi-read function.'),
  );
  $form['config']['showchapternumber'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Chapter Number.'),
    '#default_value' => variable_get('bible_config_showchapternumber', '0'),
    '#description' => t('Show Chapter number in the verse context. Ex [1:1].'),
  );
  $bolist = array(
    0 => t('Original Order'),
    1 => t('Order by Bible Name'),
  );
  $form['config']['biblelistorder'] = array(
    '#type' => 'select',
    '#title' => t('Bible List Order'),
    '#default_value' => variable_get('bible_config_biblelistorder', 0),
    '#size' => 1,
    '#options' => $bolist,
  );
  $form['config']['showbiblenote'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Bible Note.'),
    '#default_value' => variable_get('bible_config_showbiblenote', '1'),
    '#description' => t('Show Bible Note when user read chapter.'),
  );
  $form['config']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('bible_admin_config_submit'),
  );

  // Golden verse section.
  $form['goldenverse'] = array(
    '#type' => 'fieldset',
    '#title' => t('Daily Golden Verse Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $gvlist = array(
    BIBLE_GV_UPDATE_EVERY_TIME => t('Update every time.'),
    BIBLE_GV_UPDATE_HOURLY => t('Update hourly.'),
    BIBLE_GV_UPDATE_DAILY => t('Update daily.'),
    BIBLE_GV_GET_FROM_VERSE_LIST => t('Get from verse list below'),
  );
  $form['goldenverse']['gv'] = array(
    '#type' => 'select',
    '#title' => t('Golden Verse Update Type'),
    '#default_value' => variable_get('bible_block_GV_bls_type', BIBLE_GV_UPDATE_EVERY_TIME),
    '#size' => 4,
    '#options' => $gvlist,
  );
  $form['goldenverse']['gv_verses'] = array(
    '#type' => 'textarea',
    '#title' => t('Golden Verse List'),
    '#default_value' => variable_get('bible_block_GV_verses', ''),
    '#rows' => 20,
  );
  $form['goldenverse']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Golden Verse'),
    '#submit' => array('bible_admin_config_goldenverse'),
  );

  // Bible data section.
  $form['bibledata'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bible Data Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['bibledata']['activebibledata'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active bibledata'),
    '#default_value' => variable_get('bible_data_active', 1),
  );
  $bdtypeselect = variable_get('bible_data_bdtypeselect', 'CMGRDSX');
  $bdselect = array();
  foreach (str_split($bdtypeselect) as $char) {
    switch ($char) {
      case 'C':
        $bdselect[] = 'commentary';
        break;

      case 'M':
        $bdselect[] = 'music';
        break;

      case 'G':
        $bdselect[] = 'gallery';
        break;

      case 'R':
        $bdselect[] = 'refverse';
        break;

      case 'D':
        $bdselect[] = 'dailyread';
        break;

      case 'S':
        $bdselect[] = 'sermon';
        break;

      case 'X':
        $bdselect[] = 'misc';
        break;
    }
  }
  global $bdtypelist;
  $form['bibledata']['bdtype'] = array(
    '#type' => 'select',
    '#title' => t('Bible Data type selection'),
    '#default_value' => $bdselect,
    '#size' => 6,
    '#options' => $bdtypelist,
    '#multiple'  => TRUE,
  );
  $form['bibledata']['langcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Languages'),
    '#default_value' => variable_get('bible_data_langcode', '*'),
    '#description' => t('The language to get bibledata. Please use | to separate langcodes. Ex: en|zh-hant. * for all languages.'),
  );
  $form['bibledata']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit BibleData'),
    '#submit' => array('bible_admin_config_bibledata'),
  );

  // Bls popup section.
  $form['blspopup'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('BLS Filter Popup Layer Style'),
  );
  $blspopupstyle = variable_get('bible_bls_popup_style', BIBLE_BLS_POPUP_STYLE);
  $css = explode(';', $blspopupstyle);
  foreach ($css as $style) {
    if (strlen($style) == 0) {
      continue;
    }
    $data = explode(':', $style);
    switch ($data[0]) {
      case 'width':
      case 'height':
      case 'border-style':
      case 'border-width':
      case 'border-color':
      case 'background-color':
        $form['blspopup']['css' . $data[0]] = array(
          '#type' => 'textfield',
          '#title' => $data[0],
          '#default_value' => $data[1],
        );
        break;
    }
  }
  $form['blspopup']['morelink'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add more link.'),
    '#default_value' => variable_get('bible_bls_popup_morelink', '0'),
    '#description' => t('Add a more link at the end of bls popup.'),
  );
  $form['blspopup']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit BLS'),
    '#submit' => array('bible_admin_config_blspopup'),
  );

  // Bible language section.
  $form['biblelang'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bible Language Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Choose browser language for the bible version. Your browser accept language: @language', array(
      '@language' => _bible_get_user_browser_lang(),
    )),
  );
  $queryResult = db_query('SELECT * FROM {bible_list}');
  foreach ($queryResult as $bb) {
    $form['biblelang']['bblang'.$bb->bid] = array(
      '#type' => 'textfield',
      '#title' => $bb->bname . '[' . $bb->lang . ']',
      '#default_value' => variable_get('bibledata_language_' . $bb->bid, '*'),
    );
  }
  $form['biblelang']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Language'),
    '#submit' => array('bible_admin_config_biblelang'),
  );

  // Block section.
  $form['block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Block Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Bible Block Configuration'),
  );
  $form['block']['showsearchadvance'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Advanced Search Options in Search Block.'),
    '#default_value' => variable_get('bible_block_searchblockshowadvance', '0'),
  );
  $form['block']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Block'),
    '#submit' => array('bible_admin_config_bibleblock'),
  );

  return $form;
}

/**
 * Process the bible config form submission, generic part.
 */
function bible_admin_config_submit($form, &$form_state) {
  variable_set('bible_config_multireadbiblename', $form['config']['multireadbiblename']['#value']);
  variable_set('bible_config_showchapternumber', $form['config']['showchapternumber']['#value']);
  variable_set('bible_config_biblelistorder', $form['config']['biblelistorder']['#value']);
  variable_set('bible_config_showbiblenote', $form['config']['showbiblenote']['#value']);
}

/**
 * Process the bible config form submission, golden verse part.
 */
function bible_admin_config_goldenverse($form, &$form_state) {
  variable_set('bible_block_GV_bls_type', $form['goldenverse']['gv']['#value']);
  variable_set('bible_block_GV_verses', $form['goldenverse']['gv_verses']['#value']);
  drupal_set_message(t('Golden Verse update type is set.'));
  $form_state['redirect'] = 'admin/config/bible/config';
}

/**
 * Process the bible config form submission, bible data part.
 */
function bible_admin_config_bibledata($form, &$form_state) {
  $bibledata = $form['bibledata'];
  variable_set('bible_data_active', $bibledata['activebibledata']['#value'] == '1');
  $bdtype = '';
  if (isset($bibledata['bdtype']['#value'])) {
  foreach ($bibledata['bdtype']['#value'] as $bd) {
    switch ($bd) {
        case 'commentary':
          $bdtype .= 'C';
          break;

        case 'music':
          $bdtype .= 'M';
          break;

        case 'gallery':
          $bdtype .= 'G';
          break;

        case 'refverse':
          $bdtype .= 'R';
          break;

        case 'dailyread':
          $bdtype .= 'D';
          break;

        case 'sermon':
          $bdtype .= 'S';
          break;

        case 'misc':
          $bdtype .= 'X';
          break;
      }
  }
  }
  variable_set('bible_data_bdtypeselect', $bdtype);
  variable_set('bible_data_langcode', $bibledata['langcode']['#value']);
  global $bibledataxml;
  $bibledataxml = '';
  $_SESSION['bibledataxml'] = '';
  $form_state['redirect'] = 'admin/config/bible/config';
}

/**
 * Process the bible config form submission, BLS popup part.
 */
function bible_admin_config_blspopup($form, &$form_state) {
  $blspopup = $form['blspopup'];
  $styleline = '';
  foreach (element_children($blspopup) as $key => $element) {
    if (substr($element, 0, 3) == 'css') {
      $styleline .= substr($element, 3) .
        ':' . $blspopup[$element]['#value'] . ';';
    }
  }
  $styleline .= "overflow-x:hidden;overflow-y:auto;";
  variable_set('bible_bls_popup_style', $styleline);
  variable_set('bible_bls_popup_morelink', $blspopup['morelink']['#value']);
  $form_state['redirect'] = 'admin/config/bible/config';
}

/**
 * Process the bible config form submission, bible language part.
 */
function bible_admin_config_biblelang($form, &$form_state) {
  $biblelang = $form['biblelang'];
  foreach (element_children($biblelang) as $key => $element) {
    if (substr($element, 0, 6) == 'bblang') {
      $bid = substr($element, 6);
      variable_set('bibledata_language_' . $bid, $biblelang[$element]['#value']);
    }
  }
  $form_state['redirect'] = 'admin/config/bible/config';
}

/**
 * Process the bible config form submission, bible block part.
 */
function bible_admin_config_bibleblock($form, &$form_state) {
  variable_set('bible_block_searchblockshowadvance', $form['block']['showsearchadvance']['#value']);
  $form_state['redirect'] = 'admin/config/bible/config';
}

function bible_admin_select() {
  $arg = check_plain(arg(4));
  if (!empty($arg)) {
    variable_set('bible_select', $arg);
    drupal_goto('admin/config/bible/list');
  }
}

function bible_admin_snselect() {
  $arg = check_plain(arg(4));
  if (!empty($arg)) {
    variable_set('bible_sn_select', $arg);
    drupal_goto('admin/config/bible/list');
  }
}

function bible_admin_snsselect() {
  $arg = check_plain(arg(4));
  if (!empty($arg)) {
    variable_set('bible_snsearch_select', $arg);
    drupal_goto('admin/config/bible/list');
  }
}

function bible_admin_delete() {
  $arg = check_plain(arg(4));
  if (empty($arg)) {
    drupal_goto('admin/config/bible');
  }
  $form['bible'] = array(
    '#type' => 'value',
    '#value' => $arg,
  );
  return confirm_form($form,
    t('Are you sure you want to delete bible @name?', array(
      '@name' => _bible_get_bible_name($arg),
    )),
    'admin/config/bible',
    t('Deleting a bible will remove all data associated with it. This action cannot be undone.'),
    t('Delete'), t('Cancel'));
}

function bible_admin_delete_submit($form, &$form_state) {
  $bid = $form['bible']['#value'];
  db_delete('bible_context')
    ->condition('bid', $bid)
    ->execute();
  db_delete('bible_book_name')
    ->condition('bid', $bid)
    ->execute();
  db_delete('bible_list')
    ->condition('bid', $bid)
    ->execute();
  $form_state['redirect'] = 'admin/config/bible/list';
}

function bible_admin_sndelete() {
  $arg = check_plain(arg(4));
  if (empty($arg)) {
    drupal_goto('admin/config/bible');
  }
  $form['sn'] = array(
    '#type' => 'value',
    '#value' => $arg,
  );
  return confirm_form($form,
    t('Are you sure you want to delete the Strong\'s Number @name?', array(
      '@name' => _bible_get_sn_name($arg),
    )),
    'admin/config/bible',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function bible_admin_sndelete_submit($form, &$form_state) {
  $snid = $form['sn']['#value'];
  db_delete('bible_sn_list')
    ->condition('snid', $snid)
    ->execute();
  db_delete('bible_strongnumber')
    ->condition('snid', $snid)
    ->execute();
  $form_state['redirect'] = 'admin/config/bible';
}

function bible_admin_maintain() {
  $deletecount = 0;
  $queryResult = db_select('bible_context', 'bc')
    ->fields('bc')
    ->groupBy('bid')
    ->groupBy('book')
    ->groupBy('chapter')
    ->groupBy('verse')
    ->groupBy('linemark')
    ->having('count(*) > 1')
    ->execute();
  foreach ($queryResult as $mm) {
    $query = db_select('bible_context', 'bc')
      ->condition('bid', $mm->bid)
      ->condition('book', $mm->book)
      ->condition('chapter', $mm->chapter)
      ->condition('verse', $mm->verse)
      ->condition('linemark', $mm->linemark);
    $query = $query->countQuery();
    $count = $query
      ->execute()
      ->fetchField();
    if ($count > 1) {
      $deletecount++;
    }
  }
  return '<br/>' . t('Total Delete Duplicate: ') . $deletecount;
}
