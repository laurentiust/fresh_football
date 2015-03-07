<?php
/**
 * @file
 * fresh_football_pages.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function fresh_football_pages_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'football_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Football events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Football events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Description';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Date/Time */
  $handler->display->display_options['fields']['field_date_time']['id'] = 'field_date_time';
  $handler->display->display_options['fields']['field_date_time']['table'] = 'field_data_field_date_time';
  $handler->display->display_options['fields']['field_date_time']['field'] = 'field_date_time';
  $handler->display->display_options['fields']['field_date_time']['label'] = 'At what time';
  $handler->display->display_options['fields']['field_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_time']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Participants */
  $handler->display->display_options['fields']['field_participants']['id'] = 'field_participants';
  $handler->display->display_options['fields']['field_participants']['table'] = 'field_data_field_participants';
  $handler->display->display_options['fields']['field_participants']['field'] = 'field_participants';
  $handler->display->display_options['fields']['field_participants']['label'] = 'Who\'s going';
  $handler->display->display_options['fields']['field_participants']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_participants']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_participants']['delta_offset'] = '0';
  /* Field: Content: Stadium */
  $handler->display->display_options['fields']['field_stadium']['id'] = 'field_stadium';
  $handler->display->display_options['fields']['field_stadium']['table'] = 'field_data_field_stadium';
  $handler->display->display_options['fields']['field_stadium']['field'] = 'field_stadium';
  $handler->display->display_options['fields']['field_stadium']['label'] = 'Where';
  $handler->display->display_options['fields']['field_stadium']['element_label_colon'] = FALSE;
  /* Field: Content: Join Football Event */
  $handler->display->display_options['fields']['join_football_event']['id'] = 'join_football_event';
  $handler->display->display_options['fields']['join_football_event']['table'] = 'node';
  $handler->display->display_options['fields']['join_football_event']['field'] = 'join_football_event';
  $handler->display->display_options['fields']['join_football_event']['label'] = 'Join';
  $handler->display->display_options['fields']['join_football_event']['element_label_colon'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'football_event' => 'football_event',
  );

  /* Display: List of events */
  $handler = $view->new_display('panel_pane', 'List of events', 'panel_pane_1');
  $export['football_events'] = $view;

  return $export;
}
