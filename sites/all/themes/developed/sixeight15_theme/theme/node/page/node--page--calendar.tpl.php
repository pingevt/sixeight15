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
      <div class="col-sm-7 col-md-offset-1">
        <?php
          if (isset($content['field_page_video'])) {
            print render($content['field_page_video']);
            print '<hr class="double">';
          }
          else {
            if (isset($content['field_page_image'])) {
              print render($content['field_page_image']);
              print '<hr class="double">';
            }
          }
        ?>
      </div>
    </div>



    <div class="row">
      <div class="col-sm-7 col-md-offset-1">
        <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
        <?php print render($content['field_body']); ?>
      </div>
      <div class="col-sm-2 col-sm-offset-1 menu-column">
        <?php print render($menu); ?>
      </div>
    </div>



    <div class="row">
      <div class="col-sm-2">
        <div class=""><?php print $legend; ?></div>
      </div>
      <div class="col-sm-10">
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
  <section>
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

</script>
