/**
 *  @file
 *  Initiate the BxSlider plugin.
 */

(function ($) {
  Drupal.behaviors.viewsSlideshowBxslider = {
    attach: function (context, settings) {
      for (id in Drupal.settings.viewsSlideshowBxslider) {
        var html_id = id.replace(/_/g, '-');
        $('#' + html_id + ':not(.viewsSlideshowBxslider-processed)', context).addClass('viewsSlideshowBxslider-processed').each(function () {
          // Fire up the gallery.
          var functionName = "bxSliderInitialize" + id;
          if(typeof functionName == 'function') {
            // Dynamic function call.
            dynamicFunctionCaller(functionName, $(this));
          } else {
            var settingsBxSlider = Drupal.settings.viewsSlideshowBxslider[id];
            $(this).bxSlider(eval("({" + eval(settingsBxSlider) + "})"));
          }
        });
      }
    }
  };
}(jQuery));

function dynamicFunctionCaller(func){
  this[func].apply(this, Array.prototype.slice.call(arguments, 1));
}
