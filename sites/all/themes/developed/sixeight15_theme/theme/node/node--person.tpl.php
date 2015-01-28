
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <!--<h2<?php print $title_attributes; ?>><?php print $title; ?></h2> -->
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>

    <div class="row">
      <div class="col-sm-4">
        <?php print render($content['field_person_image']); ?>
      </div>
      <div class="col-sm-8">

        <?php print render($content); ?>

      </div>
    </div>
  </div>

</div>
