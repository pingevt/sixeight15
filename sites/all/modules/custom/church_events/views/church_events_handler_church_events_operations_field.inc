<?php

/**
 * This field handler aggregates operations that can be done on a cevents
 * under a single field providing a more flexible way to present them in a view
 */
class cevents_handler_cevents_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['cevents_id'] = 'cevents_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('cevents', 'admin/content/ceventss/cevents', array($this->get_value($values, 'cevents_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
