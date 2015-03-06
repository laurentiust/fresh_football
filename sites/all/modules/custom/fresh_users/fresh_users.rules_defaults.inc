<?php
/**
 * @file
 * fresh_users.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function fresh_users_default_rules_configuration() {
  $items = array();
  $items['rules_user_login_go_to_profile'] = entity_import('rules_config', '{ "rules_user_login_go_to_profile" : {
      "LABEL" : "user login go to profile",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "login", "redirect" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "DO" : [ { "redirect" : { "url" : "user" } } ]
    }
  }');
  return $items;
}
