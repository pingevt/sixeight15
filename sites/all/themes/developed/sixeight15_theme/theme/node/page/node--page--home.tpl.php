<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>

    <?php print render($content['home_page_carousel']); ?>

    <hr class="double" />

    <div class="row">
      <div class="col-sm-10 col-md-offset-1">
        <?php print render($content['field_body']); ?>
        <hr class="double" />
      </div>
    </div>

    <div class="row">
      <div class="col-sm-10 col-md-offset-1">
        <?php print ($content['home_page_blocks']); ?>
      </div>
    </div>

  </div>

</div>
