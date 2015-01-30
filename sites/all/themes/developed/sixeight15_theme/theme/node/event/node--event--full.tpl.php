<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
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
          if (isset($content['field_event_image'])) {
            print render($content['field_event_image']);
            print '<hr class="double">';
          }
        ?>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-7 col-md-offset-1">
        <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>

        <?php print render($content); ?>
      </div>
      <div class="col-sm-2 col-sm-offset-1 menu-column">
        <?php print render($menu); ?>
      </div>
    </div>

  </div>

</div>
