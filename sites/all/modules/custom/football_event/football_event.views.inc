<?php

/**
 * @file contains views specific hooks
 */

/**
 * Implements hook_views_data_alter().
 */
function football_event_views_data_alter(&$data) {
  // Adds a button to move a line item from cart to wishlist.
  $data['node']['join_football_event'] = array(
    'field' => array(
      'title' => t('Join Football Event'),
      'help' => t('Join or leave a football event.'),
      'handler' => 'football_event_handler_field_join',
    ),
  );
}