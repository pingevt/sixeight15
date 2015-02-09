<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class cevents_handler_delete_link_field extends cevents_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy cevents to check access against
    $dummy_cevents = (object) array('type' => $type);
    if (!cevents_access('edit', $dummy_cevents)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $cevents_id = $values->{$this->aliases['cevents_id']};
    
    return l($text, 'admin/content/ceventss/cevents/' . $cevents_id . '/delete');
  }
}
