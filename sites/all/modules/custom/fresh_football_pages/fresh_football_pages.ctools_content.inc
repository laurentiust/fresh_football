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
    'body' => '<?php
echo \'this is some code\';
?>',
    'format' => 'php_code',
    'substitute' => 0,
  );
  $export['home_page_football_field_block'] = $content;

  return $export;
}
