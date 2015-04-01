<?php
/**
 * @file
 * six_eight_general.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function six_eight_general_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_page_front_ad|node|page|form';
  $field_group->group_name = 'group_page_front_ad';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Ad',
    'weight' => '36',
    'children' => array(
      0 => 'field_front_ad',
      1 => 'field_front_ad_duration',
      2 => 'field_front_ad_image',
      3 => 'field_front_ad_link',
      4 => 'field_front_ad_no_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-page-front-ad field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_page_front_ad|node|page|form'] = $field_group;

  return $export;
}
