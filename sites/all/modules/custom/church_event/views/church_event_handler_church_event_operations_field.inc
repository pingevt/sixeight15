<?php

/**
 * This field handler aggregates operations that can be done on a cevents
 * under a single field providing a more flexible way to present them in a view
 */
class church_event_handler_church_event_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['church_event_id'] = 'church_event_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('church_event', 'admin/content/church_event/manage', array($this->get_value($values, 'church_event_id')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
