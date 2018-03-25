<?php

function bible_note() {
  global $user;
  global $imagedir;
  if ($user->uid == 0) {
    drupal_set_message(t('Please login.'));
    drupal_goto('bible');
  }

  $rows = array();
  $header = array(
    array('data' => t('Verse')),
    array('data' => t('Public')),
    array('data' => t('Context')),
    array('data' => t('Action')),
  );

  $result_set = db_select('bible_note')
    ->fields('bible_note')
    ->extend('PagerDefault')
    ->condition('uid', $user->uid)
    ->limit(15)
    ->orderBy('bnid')
    ->execute();

  $default_bible = _bible_get_select_bid();
  foreach ($result_set as $note){
    $pp = ($note->access === 0 ? 'public' : 'private');
    $rows[] = array(
      _bible_get_blslink($default_bible, $note->bls),
      '<image src="' . $imagedir . 'access' . $pp . '.gif" title="' . $pp . ' usage" />',
      check_plain($note->content),
      l(t('Edit'), 'bible/note/edit/' . $note->bnid),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= theme('pager');

  // Output links.
  $output .= bible_note_links();
  $output .= theme('bible_links');
  return $output;
}

function bible_note_links() {
  $output = '<hr />';
  $output .= '[' . l(t('Add Note'), 'bible/note/add') . ']';
  $output .= '[' . l(t('Add Multi-Notes'), 'bible/note/addlines') . ']';
  $output .= '[' . l(t('Export my notes'), 'bible/note/export') . ']';
  return $output;
}

function bible_note_addform($form, &$form_state, $bnid = -1) {
  if ($bnid >= 0) {
    $bnobj = _bible_get_note_obj($bnid);
  }
  $form['note'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add your note'),
  );
  $form['note']['bnid'] = array('#type' => 'hidden', '#value' => $bnid);
  $form['note']['bls'] = array(
    '#type' => 'textfield',
    '#title' => t('Verse'),
    '#size' => 40,
    '#default_value' => ($bnid == -1 ? '' : $bnobj->bls),
  );
  $form['note']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 80,
    '#default_value' => ($bnid == -1 ? '' : $bnobj->title),
  );
  $form['note']['content'] = array(
    '#type' => 'textarea',
    '#title' => t('Content'),
    '#rows' => 20,
    '#required' => TRUE,
    '#default_value' => ($bnid == -1 ? '' : $bnobj->content),
  );
  $form['note']['access'] = array(
    '#type' => 'radios',
    '#title' => t('These notes are for public usage or private usage?'),
    '#options' => array(
      0 => t('Public usage'),
      1 => t('Private usage'),
    ),
    '#default_value' => ($bnid == -1 ? 0 : $bnobj->access),
  );
  $form['note']['source'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#size' => 80,
    '#default_value' => ($bnid == -1 ? '' : $bnobj->source),
  );
  $form['note']['submit'] = array(
    '#type' => 'submit',
    '#value' => ($bnid == -1 ? t('Add') : t('Save')),
    '#submit' => array('bible_note_addform_submit'),
  );
  if ($bnid >=0) {
    $form['note']['submit1'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('bible_note_deleteform_submit'),
    );
  }
  $form['note']['links'] = array(
    '#type' => 'item',
    '#value' => bible_note_links() . theme('bible_links'),
  );
  return $form;
}

function bible_note_addform_submit($form, &$form_state) {
  $bnid = $form['note']['bnid']['#value'];
  $bls = $form['note']['bls']['#value'];
  $title = $form['note']['title']['#value'];
  $content = $form['note']['content']['#value'];
  $access = $form['note']['access']['#value'];
  $source = $form['note']['source']['#value'];
  global $user;
  if ($bnid == -1) {
    _bible_note_add($user->uid, $access, $bls, $title, $content, $source);
  }
  else {
    db_update('bible_note')
    ->fields(array (
      'access' => $access,
      'bls' => $bls,
      'title' => $title,
      'content' => $content,
      'source' => $source,
    ))
    ->expression('modified', 'CURRENT_TIMESTAMP')
    ->condition('bnid', $bnid)
    ->execute();
  }
  drupal_goto('bible/note');
}

function bible_note_deleteform_submit($form, &$form_state) {
  $bnid = $form['note']['bnid']['#value'];
  $form_state['redirect'] = 'bible/note/delete/' . $bnid;
}

function bible_note_delete($form, &$form_state, $bnid = -1) {
  $form = array();
  $form['noteid'] = array(
    '#type' => 'value',
    '#value' => $bnid,
  );
  return confirm_form($form,
    t('Are you sure you want to delete this note?'),
    'bible/note',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function bible_note_delete_submit($form, &$form_state) {
  $bnid = $form['noteid']['#value'];
  db_delete('bible_note')
    ->condition('bnid', $bnid)
    ->execute();
  $form_state['redirect'] = 'bible/note';
}

function bible_note_addlinesform($form, &$form_state) {
  $form['note'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add your notes one note per line.'),
  );
  $form['note']['content'] = array(
    '#type' => 'textarea',
    '#title' => t('Note content'),
    '#description' => t('Please following this format: BLS|note. Ex. GEN:1:1|God create the world.'),
    '#rows' => 20,
    '#required' => TRUE,
    '#default_value' => '',
  );
  $form['note']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 80,
    '#default_value' => '',
  );
  $form['note']['access'] = array(
    '#type' => 'radios',
    '#title' => t('These notes are for public usage or private usage?'),
    '#options' => array(
      0 => t('Public usage'),
      1 => t('Private usage'),
    ),
    '#default_value' => 0,
  );
  $form['note']['source'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#size' => 80,
    '#default_value' => '',
  );
  $form['note']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Command'),
    '#value' => t('Add'),
    '#submit' => array('bible_note_addlinesform_submit'),
  );
  $form['note']['links'] = array(
    '#type' => 'item',
    '#value' => bible_note_links() . theme("bible_links"),
  );
  return $form;
}

function bible_note_addlinesform_submit($form, &$form_state) {
  $content = $form['note']['content']['#value'];
  $access = $form['note']['access']['#value'];
  $title = $form['note']['title']['#value'];
  $source = $form['note']['source']['#value'];
  global $user;
  $line = explode("\r\n", $content);
  $addcount = 0;
  foreach ($line as $l) {
    if ($l === '') {
      continue;
    }
    $data = explode('|', $l);
    if ($data[0] === '') {
      continue;
    }
    $addcount += _bible_note_add($user->uid, $access, $data[0], $title, $data[1], $source);
  }
  drupal_set_message(t('Bible notes added:%count', array('%count' => $addcount)));
  $form['redirect'] = 'bible/note';
}

function bible_note_export() {
  global $user;

  $result_set = db_select('bible_note', 'bn')
    ->fields('bn')
    ->condition('uid', $user->uid)
    ->orderBy('bnid')
    ->execute();
  $exportlines = '';
  foreach ($result_set as $note) {
    $line = $note->bls . '|' . $note->content;
    if (strlen($line) > 0) {
      $exportlines .= $line . "\r\n";
    }
  }
  header('Content-Type: text/plain; charset=utf-8');
  header('Content-Transfer-Encoding: 8bit');
  header("Content-Disposition: attachment; filename=mybiblenote.txt");
  print $exportlines;
  return;
}

function bible_note_ajax($bnid = '') {
  if ($bnobj = _bible_get_note_obj($bnid)) {
    print check_plain($bnobj->content);
  }
  else {
    print '';
  }
  exit();
}

function _bible_get_note_obj($bnid) {
  global $user;
  $note = db_select('bible_note', 'bn')
    ->fields('bn')
    ->condition('bnid', $bnid)
    ->condition(db_or()
      ->condition('access', 0)
      ->condition('uid', $user->uid)
    )
    ->execute()
    ->fetch();
  return $note;
}

function _bible_get_note_obj_bls($bls) {
  global $user;
  $queryResult = db_select('bible_note', 'bn')
    ->fields('bn')
    ->condition('bls', $bls)
    ->condition(db_or()
      ->condition('access', 0)
      ->condition('uid', $user->uid)
    )
    ->orderBy('bnid')
    ->execute();
  $notes = '';
  foreach ($queryResult as $bn) {
    $notes .= check_plain($bn->content) . "\r\n";
  }
  return $notes;
}

function _bible_note_add($uid, $access, $bls, $title, $content, $source) {
  if ($bls === '' || strlen($bls) > 11) {
    return 0;
  }
  $title = str_replace("'", "\'", $title);
  $content = str_replace("'", "\'", $content);
  $source = str_replace("'", "\'", $source);
  $bnobj = db_select('bible_note', 'bn')
    ->fields('bn')
    ->condition('uid', $uid)
    ->condition('bls', $bls)
    ->condition('access',$access)
    ->condition('content', $content)
    ->execute()
    ->fetch();
  if (empty($bnobj)) {
    db_insert('bible_note')
      ->fields(array(
        'uid' => $uid,
        'access' => $access,
        'bls' => $bls,
        'title' => $title,
        'content' => $content,
        'source' => $source,
        'modified' => date('Y-m-d H:i:s', REQUEST_TIME),
      ))
      ->execute();
    return 1;
  }
  else {
    return 0;
  }
}
