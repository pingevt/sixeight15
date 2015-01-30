/**
 * @file
 * menu.js
 *
 * Provides general enhancements for the menu.
 *
 */



(function($){

  Drupal.behaviors.WWB = {
    attach: function(context) {
      $('.mcp-description .collapse').on('show.bs.collapse', function() {
        $(this).parent().show();
      });

      $('.mcp-description .collapse').on('hidden.bs.collapse', function() {
        $(this).parent().hide();
      });


    }
  }

})(jQuery);
