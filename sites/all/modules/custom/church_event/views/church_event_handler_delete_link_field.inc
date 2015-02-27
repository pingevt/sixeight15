<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class church_event_handler_delete_link_field extends church_event_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};

    //Creating a dummy cevents to check access against
    $dummy_church_event = (object) array('type' => $type);
    if (!church_event_access('edit', $dummy_church_event)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $church_event_id = $values->{$this->aliases['church_event_id']};

    return l($text, 'admin/content/church_event/manage/' . $church_event_id . '/delete');
  }
}
