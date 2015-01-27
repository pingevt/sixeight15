/**
 * @file
 * calendar.js
 *
 * Provides general enhancements for the calendar.
 *
 */

(function($){

  Drupal.behaviors.SixEightCalendar = {
    attach: function(context) {
      $('#calendar').clndr();

    }
  }

})(jQuery);
