/**
 * @file
 * auto-menu.js
 *
 *
 */


(function($){
  // Add our commands to the Drupal commands collection.
  Drupal.ajax.prototype.commands.acOpenModal = function (ajax, response, status) {
    $(response.selector).modal('show');
  }

  // Add our commands to the Drupal commands collection.
  Drupal.ajax.prototype.commands.acCloseModal = function (ajax, response, status) {
    $(response.selector).modal('hide');
  }

  Drupal.behaviors.resourceLinks = {
    attach: function(context) {

      // Figure out what to do with this link.
      $('.resource-item', context).each(function() {
        var oldHREF = $(this).attr("href");
        var getInfoURL = oldHREF.replace('node', 'resource') + '/get-url';
        var $item = $(this);

        $.post(getInfoURL, function(data) {

          switch ( data.type ) {
            // Image and video we need to change it to an ajax callback to get the modal markup.
          	case 'image':
          	case 'video':
          		var newHREF = oldHREF.replace('node', 'resource') + '/nojs';
          		$item.attr("href", newHREF);
              $item.addClass('use-ajax');
              Drupal.attachBehaviors($(this));

          		break;

          	// Url and file we just need to get the new href.
          	case 'url':
          	case 'file':
          	  $item.attr("href", data.link.path);

          	  if ($item.attr("target") == undefined && data.link.options.attributes.target != undefined) {
                $item.attr("target", data.link.options.attributes.target);
          	  }

          		break;
          }

        }, 'json');

      });

      // When we close a modal, destroy it.
      $('.modal.resource-modal').on('hidden.bs.modal', function(e) {
        $(this).remove();
      });
    }
  }

})(jQuery);
