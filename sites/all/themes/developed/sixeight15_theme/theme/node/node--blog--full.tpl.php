<?php
//dpm($content);
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="row">
    <div class="col-sm-1">
      <div class="date">
        <?php print $date; ?>
      </div>
    </div>

    <div class="col-sm-11 col-md-10">

      <?php print render($title_prefix); ?>
      <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>

      <div class="content"<?php print $content_attributes; ?>>

        <?php print render($content['field_blog_image']); ?>

        <div class="row">
          <div class="col-md-10">
            <?php print render($content['field_blog_content']); ?>
          </div>
          <div class="col-md-2">
            <?php print render($menu); ?>
            <?php print render($content['field_blog_topics']); ?>
          </div>
        </div>

      </div>
    </div>
  </div>

</div>
