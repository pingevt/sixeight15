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

        <iframe frameborder="0"  width="100%" height="375" marginheight="0" marginwidth="0" scrolling="no" src="//maps.google.com/maps?f=q&amp;source=s_q&amp;hl=en&amp;geocode=&amp;q=1116+Lancaster+Ave,+Bryn+Mawr,+PA+19010&amp;aq=&amp;sll=40.0246174,-75.3281122&amp;sspn=0.006887,0.009999&amp;vpsrc=6&amp;ie=UTF8&amp;hq=&amp;hnear=1116+Lancaster+Ave,+Bryn+Mawr,+PA+19010&amp;ll=40.0246174,-75.3281122&amp;spn=0.006887,0.009999&amp;z=14&amp;iwloc=A&amp;output=embed" width="100%"></iframe>
        <small><a href="//maps.google.com/maps?f=q&amp;source=embed&amp;hl=en&amp;geocode=&amp;q=1116+Lancaster+Ave,+Bryn+Mawr,+PA+19010&amp;aq=&amp;sll=40.0246174,-75.3281122&amp;sspn=0.006887,0.009999&amp;vpsrc=6&amp;ie=UTF8&amp;hq=&amp;hnear=1116+Lancaster+Ave,+Bryn+Mawr,+PA+19010&amp;ll=40.0246174,-75.3281122&amp;spn=0.006887,0.009999&amp;z=14&amp;iwloc=A" >View Larger Map</a></small></p>

        <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>

        <?php print render($content['field_body']); ?>
      </div>
      <div class="col-sm-2 col-sm-offset-1 menu-column">
        <?php print render($menu); ?>
      </div>
    </div>

  </div>

</div>
