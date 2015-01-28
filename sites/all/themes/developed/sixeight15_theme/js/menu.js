/**
 * @file
 * menu.js
 *
 * Provides general enhancements for the menu.
 *
 * 992 - md and lg
 * 768 - sm
 */



(function($){

  Drupal.behaviors.SixEightMenu = {
    attach: function(context) {
      var timeout;

      $('.flyin-trigger, .flyin-menu', context).hover( function (e) {
        // Only if screen size is md and lg.
        if ($(window).width() > 992) {
          // get target id
          var target = $(this).data('target');

          // If the target exists, open it
          if ($('#'+target).length > 0) {
            $(this).trigger('menu-open');
          }
        }
      },
      function (e) {
        // Only if screen size is md and lg.
        if ($(window).width() > 992) {
          var target = $(this).data('target');
          // If the target exists, close it
          if ($('#'+target).length > 0) {
            $(this).trigger('menu-close');
          }
        }
      });

      $('.flyin-trigger, .flyin-menu', context).on('menu-open', function() {

        var target = $(this).data('target');

        window.clearTimeout(timeout);
        $('.flyin-menu').hide();
        $('#'+target).stop().show();
        var height = $('#flyin-wrapper > .container').height();

        $('#flyin-wrapper').stop().animate({height: height + 'px'}, { queue: false, duration: 1000, easing: 'easeOutCubic' });

      });

      $('.flyin-trigger, .flyin-menu', context).on('menu-close', function() {

        var target = $(this).data('target');

        $('#'+target).stop();

        $('#flyin-wrapper').stop();

        timeout = window.setTimeout(closeFlyIn, 400, $('#flyin-wrapper'), target);
      });


    }
  }

  function closeFlyIn($obj, target) {
    $obj.animate({height: 0}, { queue: false, duration: 400, easing: "easeInCubic", complete: function() {
      $('#'+target).hide();
    }});
  }
})(jQuery);
