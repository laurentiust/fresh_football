<?php

/**
 * @file
 * Field handler to present a button to move a line item from cart to wishlist. It's a dummy
 * handler, most part of the implementation is done via pre and post render
 * hooks.
 */

/**
 * Field handler to present a button to delete a line item.
 */
class football_event_handler_field_join extends views_handler_field {

  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';

    // Set real_field in order to make it generate a field_alias.
    $this->real_field = 'nid';
  }

  function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Returns the form which replaces the placeholder from render().
   */
  function views_form(&$form, &$form_state) {
    global $user;
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    // At this point, the query has already been run, so we can access the results
    // in order to get the base key value (for example, nid for nodes).
    foreach ($this->view->result as $row_id => $row) {
      $nid = $this->get_value($row);
      $node_type = $row->node_type;

      if ($node_type == 'football_event') {
        if ($this->football_event_joined($nid, $user->uid)) {
          $title = t('Leave');
        }
        else {
          $title = t('Join');
        }

        $form[$this->options['id']][$row_id] = array(
          '#type' => 'submit',
          '#value' => $title,
          '#name' => 'join-event-' . $row_id,
          '#attributes' => array('class' => array('join-event')),
          '#nid' => $nid,
          '#submit' => $form['#submit'],
        );
      }
    }
  }

  function views_form_validate($form, &$form_state) {
    global $user;

    if (!$user->uid) {
      form_set_error('football_event_error', t('You need to be authenticated to join the team.'));
      return FALSE;
    }
  }

  function views_form_submit($form, &$form_state) {
    global $user;

    $field_name = $this->options['id'];

    foreach (element_children($form[$field_name]) as $row_id) {
      // Check for the removal of an item.
      if ($form_state['triggering_element']['#name'] == 'join-event-' . $row_id) {
        // add line item in wishlist
        $nid = $form[$field_name][$row_id]['#nid'];
        $node = node_load($nid);

        if ($this->football_event_joined($nid, $user->uid)) {
          foreach ($node->field_participants[LANGUAGE_NONE] as $index => $target) {
            if ($target['target_id'] == $user->uid) {
              unset($node->field_participants[LANGUAGE_NONE][$index]);
              drupal_set_message(t('You successfully left event <em>@event</em>.', array('@event' => $node->title)));
            }
          }
        }
        else {
          $node->field_participants[LANGUAGE_NONE][]['target_id'] = $user->uid;
          drupal_set_message(t('You successfully joined event <em>@event</em>.', array('@event' => $node->title)));
        }
        node_save($node);
      }
    }
  }

  protected function football_event_joined($nid, $uid) {
    $node = node_load($nid);

    if (!empty($node->field_participants[LANGUAGE_NONE])) {
      foreach ($node->field_participants[LANGUAGE_NONE] as $index => $target) {
        if ($target['target_id'] == $uid) {
          return TRUE;
        }
      }
    }
  }
}
