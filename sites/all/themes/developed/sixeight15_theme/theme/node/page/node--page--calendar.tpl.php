<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h1<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h1>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      //print render($content);
    ?>

    <div class="row">
      <div class="col-sm-10">
        <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-2 col-sm-push-10 menu-column">
        <?php print render($menu); ?>
        <div class="legend-wrapper"><?php print $legend; ?></div>
      </div>

      <div class="col-sm-10 col-sm-pull-2">
        <?php print render($content['field_body']); ?>
        <div id="calendar"></div>
      </div>

    </div>

  </div>

</div>

<script type="text/template" id="calendar-month-template">
  <nav>
    <a rel="prev" class="clndr-prev"><i class="fa fa-caret-left"></i>Previous</a>
    <strong><%= month %></strong> <%= year %>
    <a rel="next" class="clndr-next">Next<i class="fa fa-caret-right"></i></a>
  </nav>
  <section class="hidden-xs">
    <table border="0" cellspacing="0" cellpadding="0">
      <thead>
        <tr>
          <% for(var i = 0; i < daysOfTheWeek.length; i++) { %>
            <th><%= daysOfTheWeek[i] %></th>
          <% } %>
        </tr>
      </thead>
      <tbody>
      <% for(var i = 0; i < numberOfRows; i++){ %>
        <tr>
        <% for(var j = 0; j < 7; j++){ %>
          <% var d = j + i * 7; %>
          <td class="<%= days[d].classes %>">
            <div class="day"><%= days[d].day %></div>
            <% _.each(days[d].events, function (event) { %>
              <div class="event <%= event.class %>">
                <i class="<%= event.class %> cal-icon"></i>
                <%= event.title %>
                <% if(event.popover) { %>
                  <%= event.popover %>
                <% } %>
              </div>
            <% }); %>
          </td>
        <% } %>
        </tr>
      <% } %>
      </tbody>
    </table>
  </section>

  <div class="event-listing visible-xs-block">

    <%
      var currentDate = '';
      _.each(eventsThisMonth, function(event) {

        if (event.startDate != currentDate) {
          currentDate = event.startDate;
    %>
        <div class="event-item-date"><%= event.startDate %></div>
     <% } %>

        <div class="event-item event <%= event.class %>">
          <div class="event-item-name"><i class="<%= event.class %> cal-icon"></i> <%= event.title %></div>
        </div>

      <% }); %>
  </div>

</script>
