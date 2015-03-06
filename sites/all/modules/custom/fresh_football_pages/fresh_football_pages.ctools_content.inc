<?php
/**
 * @file
 * fresh_football_pages.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function fresh_football_pages_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'home_page_football_field_block';
  $content->admin_title = 'Home page football field block';
  $content->admin_description = '';
  $content->category = '';
  $content->settings = array(
    'admin_title' => '',
    'title' => '',
    'body' => '',
    'format' => 'full_html',
    'substitute' => 0,
  );
  $export['home_page_football_field_block'] = $content;

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'login_and_register_home_page_block';
  $content->admin_title = 'Login and register home page block';
  $content->admin_description = '';
  $content->category = '';
  $content->settings = array(
    'admin_title' => '',
    'title' => '',
    'body' => '<?php
print \'<p><a href="javascript:;" class="btn btn-default login">Login</a></p>\';
print \'<p><a href="javascript:;" class="btn btn-default register">Register</a></p>\';
print \'<p><a href="javascript:;" class="btn btn-default forgot-password">Forgot password</a></p>\';
 $register_form = drupal_get_form(\'user_register_form\');
 $login_form = drupal_get_form(\'user_login\');
 $pass_form = drupal_get_form(\'fresh_football_pass_form\');
print drupal_render($login_form); 
print drupal_render($pass_form );
print drupal_render($register_form); 
?>',
    'format' => 'php_code',
    'substitute' => 0,
  );
  $export['login_and_register_home_page_block'] = $content;

  return $export;
}
