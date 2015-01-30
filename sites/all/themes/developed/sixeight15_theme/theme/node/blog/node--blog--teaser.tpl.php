<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php print render($content['field_blog_image']); ?>

    <div class="row">

      <div class="col-xs-10">
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>

        <?php if ($display_submitted): ?>
          <div class="submitted">
            <?php print $submitted; ?>
          </div>
        <?php endif; ?>

        <?php print render($content); ?>

        <a href="<?php print $node_url; ?>" class="read-more">read more <i class="fa fa-arrow-right"></i></a>
      </div>

      <div class="col-xs-2">
        <div class="date">
          <?php print $date; ?>
        </div>
      </div>

    </div>
  </div>
</div>
