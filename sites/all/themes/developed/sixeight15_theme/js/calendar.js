/**
 * @file
 * calendar.js
 *
 * Provides general enhancements for the calendar.
 *
 */

(function($){

  var url = '/admin/calendar/events';

  Drupal.behaviors.SixEightCalendar = {
    attach: function(context) {

      $('li.toggle-calendar', context).on('click', function() {
        var targetClass = $(this).data('target-class');

        $('.event.' +  targetClass).toggle();
        $(this).toggleClass('hidden-calendar');

      });

    }
  }

  $(document).ready(function() {
    var calendar = $('#calendar').clndr({
      template: $('#calendar-month-template').html(),
      daysOfTheWeek: ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'],
      startWithMonth: $(this).data('date') || moment(),
      events: [],
      multiDayEvents: {
        startDate: 'startDate',
        endDate: 'endDate',
        singleDay: 'date'
      },
      clickEvents: {
        onMonthChange: function (month) {
          // get data
          $.get(url, {date: month.format('YYYY-MM-DD')}, function (response) {
            calendar.setEvents(response);
          });

        }
      },
      targets: {
        nextButton: 'clndr-next',
        previousButton: 'clndr-prev',
      },
      doneRendering: function(){
        Drupal.attachBehaviors(self);
        establishEventVisibility();
      }
    });

    $.get(url, function (response) {
      calendar.setEvents(response);
    });

  });


  function establishEventVisibility() {
console.log('called');
    $('li.toggle-calendar').each(function() {
console.log($(this));
      if ($(this).hasClass('hidden-calendar')) {
        var targetClass = $(this).data('target-class');
        $('.event.' +  targetClass).toggle();
      }
    });
  }
})(jQuery);
