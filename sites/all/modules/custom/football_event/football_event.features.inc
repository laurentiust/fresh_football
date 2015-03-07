<?php
/**
 * @file
 * football_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function football_event_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function football_event_node_info() {
  $items = array(
    'football_event' => array(
      'name' => t('Football Event'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
