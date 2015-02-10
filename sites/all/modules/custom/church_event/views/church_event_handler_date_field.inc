<?php

/**
 * This field handler aggregates operations that can be done on a cevents
 * under a single field providing a more flexible way to present them in a view
 */
class church_event_handler_date_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['church_event_id'] = 'church_event_id';
  }

  function render($values) {

    $value = $this->get_value($values);

    return date("Y-m-d", $this->get_value($values));
  }
}
