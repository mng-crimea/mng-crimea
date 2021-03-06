<?php
/**
 * @file
 * The theme system that controls the display of Views Slideshow: Bxslider.
 */

/**
 *  Process variables for views-bxslider-main-frame.tpl.php.
 */
function template_preprocess_bxslider_views_slideshow_main_frame(&$vars) {
  _bxslider_views_slideshow_set_extra_css($vars['settings']['general']);

  _bxslider_views_slideshow_add_js($vars['settings'], 'views-slideshow-bxslider-images-' . $vars['id']);

  $vars['classes_array'][] = 'bxslider';
  $rendered_rows = '';
  foreach ($vars['rows'] as $count => $item) {
    $rendered_rows[] = theme('bxslider_views_slideshow_main_frame_row', array(
      'vss_id' => $vars['vss_id'], 'items' => $item, 'count' => count($vars['rows']), 'view' => $vars['view']));
  }
  $vars['rendered_rows'] = $rendered_rows;
}

function _bxslider_views_slideshow_set_extra_css($general_settings) {
  $align_image = isset($general_settings['align_image']) ? $general_settings['align_image'] : NULL;
  $color_caption = isset($general_settings['color_caption']) ? $general_settings['color_caption'] : NULL;
  $align_caption = isset($general_settings['align_caption']) ? $general_settings['align_caption'] : NULL;;
  // Overlay bug fix.
  $selector_overlay = ".views-slideshow-bxslider .bx-wrapper .bx-controls-direction a";
  drupal_add_css($selector_overlay . ' { z-index:499; }', 'inline');

  $selector = ".views-slideshow-bxslider li img";
  switch($align_image) {
    case 'center':
      drupal_add_css($selector . ' { margin-left:auto; margin-right:auto; }', 'inline');
      break;
    case 'right':
      drupal_add_css($selector . ' { margin-left:auto; }', 'inline');
      break;
    default:
      drupal_add_css($selector . ' { margin-right:auto; }', 'inline');
  }
  // Caption alignment.
  $selector_caption_alignment = ".views-slideshow-bxslider .bx-caption";
  if (!empty($align_caption)) {
    switch($align_caption) {
      case 'center':
        drupal_add_css($selector_caption_alignment . ' { text-align: center; }', 'inline');
        break;
      case 'right':
        drupal_add_css($selector_caption_alignment . ' { text-align: right; }', 'inline');
        break;
      default:
        // Nothing.
    }
  }
  // Second part color caption overruling.
  $selector_caption = ".views-slideshow-bxslider .bx-wrapper .bx-caption";
  if (!empty($color_caption)) {
    drupal_add_css($selector_caption . ' { background: rgba(' . $color_caption . ') }', 'inline');
  }
}

/*
 * Helper function to build and pass BxSlider settings to Drupal.
 */
function _bxslider_views_slideshow_add_js($options, $id) {
  // Make an correct id.
  $id = str_replace('-', '_', $id);

  // Import variables.
  extract($options);

  $bxslider_path = _bxslider_views_slideshow_library_path();

  // Load Bxslider.
  drupal_add_js($bxslider_path, array('group' => JS_LIBRARY));
  if (!$general['disable_standard_css']) {
    drupal_add_css(libraries_get_path('bxslider') . '/jquery.bxslider.css');
  }

  // Load our Bxslider js.
  drupal_add_js(drupal_get_path('module', 'bxslider_views_slideshow') . '/bxslider_views_slideshow.js');

  // Process Bxslider settings.
  // Load bxslider settings.
  $bx_slider_js = <<<BXSLIDERJS
    function bxSliderInitialize$id(slideShow) {
      jQuery(slideShow).bxSlider({
BXSLIDERJS;
  // Content.
  $bx_slider_js .= _bxslider_views_slideshow_theme_get_admin_js(
    $autofieldset, $general, $carousel, $pagerfieldset, $controlsfieldset, $carousel);
  // Callbacks.
  if (!empty($callback['onSliderLoad'])) {
    $bx_slider_js .= "onSliderLoad: function(currentIndex){" . filter_xss($callback['onSliderLoad']) . "},";
  }
  if (!empty($callback['onSlideBefore'])) {
    $bx_slider_js .=
      "onSlideBefore: function(slideElement, oldIndex, newIndex){" . filter_xss($callback['onSlideBefore']) . "},";
  }
  if (!empty($callback['onSlideAfter'])) {
    $bx_slider_js .=
      "onSlideAfter: function(slideElement, oldIndex, newIndex){" . filter_xss($callback['onSlideAfter']) . "},";
  }
  if (!empty($callback['onSlideNext'])) {
    $bx_slider_js .=
      "onSlideNext: function(slideElement, oldIndex, newIndex){" . filter_xss($callback['onSlideNext']) . "},";
  }
  if (!empty($callback['onSlidePrev'])) {
    $bx_slider_js .=
      "onSlidePrev: function(slideElement, oldIndex, newIndex){" . filter_xss($callback['onSlidePrev']) . "}";
  }
  $bx_slider_js .= <<<ENDBXSLIDERJS
     });
    }
ENDBXSLIDERJS;

  //Admin section
  $bx_slider_js_content = _bxslider_views_slideshow_theme_get_admin_js(
    $autofieldset, $general, $carousel, $pagerfieldset, $controlsfieldset, $carousel);
  drupal_add_js(array('viewsSlideshowBxslider' =>
  array($id => json_encode($bx_slider_js_content))), 'setting');
  // Add my own Javascript implementation via Php.
  drupal_add_js($bx_slider_js, 'inline');
}

function _bxslider_views_slideshow_theme_get_admin_js($autofieldset,
                                                      $general,
                                                      $carousel,
                                                      $pagerfieldset,
                                                      $controlsfieldset,
                                                      $carousel) {
  $bx_slider_js = <<<BXSLIDERJSCONTENT
    mode: '{$general['mode']}',
    speed: {$general['speed']},
    slideMargin: {$general['slideMargin']},
    startSlide: {$general['startSlide']},
    randomStart: {$general['randomStart']},
    infiniteLoop: {$general['infiniteLoop']},
    hideControlOnEnd: {$general['hideControlOnEnd']},
    captions: {$general['captions']},
    pager: {$pagerfieldset['pager']},
    pagerType: '{$pagerfieldset['pagerType']}',
    controls: {$controlsfieldset['controls']},
    auto: {$autofieldset['auto']},
    pause: {$autofieldset['pause']},
    minSlides: {$carousel['minSlides']},
    maxSlides: {$carousel['maxSlides']},
    ticker: {$general['ticker']},
    tickerHover: {$general['tickerHover']},
    adaptiveHeight: {$general['adaptiveHeight']},
    adaptiveHeightSpeed: {$general['adaptiveHeightSpeed']},
    video: {$general['video']},
    touchEnabled: {$general['touchEnabled']},
    preloadImages: '{$general['preloadImages']}',
    swipeThreshold: {$general['swipeThreshold']},
    oneToOneTouch: {$general['oneToOneTouch']},
    preventDefaultSwipeX: {$general['preventDefaultSwipeX']},
    preventDefaultSwipeY: {$general['preventDefaultSwipeY']},
    pagerShortSeparator: '{$pagerfieldset['pagerShortSeparator']}',
    nextText: '{$controlsfieldset['nextText']}',
    prevText: '{$controlsfieldset['prevText']}',
    startText: '{$controlsfieldset['startText']}',
    stopText: '{$controlsfieldset['stopText']}',
    autoControls: {$controlsfieldset['autoControls']},
    autoControlsCombine: {$controlsfieldset['autoControlsCombine']},
    autoHover: {$autofieldset['autoHover']},
    autoDelay: {$autofieldset['autoDelay']},
    moveSlides: {$carousel['moveSlides']},
    slideWidth: {$carousel['slideWidth']},
    useCSS: {$general['useCSS']},
    autoDirection: '{$autofieldset['autoDirection']}'
BXSLIDERJSCONTENT;
  return trim($bx_slider_js);
}
