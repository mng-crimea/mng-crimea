<?php

function fm_menu_link(array $variables) { 
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
    if ($element['#original_link']['menu_name'] == 'main-menu') {
    $linkText = $element['#title'];
    $element['#localized_options']['html'] = true;
    } else {
    $linkText = $element['#title'];
    }
  
  $output = l($linkText, $element['#href'], array('attributes' => $element['#attributes']));
  return $output;
}

/**
 * Override or insert variables into the page template.
 */
function fm_preprocess_page(&$vars) {
    
  if (drupal_is_front_page()) {
    $vars['title'] = '';
    unset($vars['page']['content']['system_main']['default_message']);
  }

  if (isset($vars['secondary_menu'])) {
     $var_temp = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'secondary-menu'),
      )
    ));
     $vars['secondary_nav'] = strip_tags($var_temp, '<a>');
    
  }
  else {
    $vars['secondary_nav'] = FALSE;
  }
}

