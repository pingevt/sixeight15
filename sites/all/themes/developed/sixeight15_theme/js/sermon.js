

(function($){

  Drupal.behaviors.SixEightSermons = {
    attach: function(context) {
      $('.sermon-desc-collapse').on('show.bs.collapse', function() {
        $(this).parent().find('.sermon-desc-collapse-btn span').html('close');
        $(this).parent().find('.sermon-desc-collapse-btn i').removeClass('fa-rotate-180');
      });

      $('.sermon-desc-collapse').on('hide.bs.collapse', function() {
        $(this).parent().find('.sermon-desc-collapse-btn span').html('open');
        $(this).parent().find('.sermon-desc-collapse-btn i').addClass('fa-rotate-180');
      });
    }
  }
})(jQuery);
