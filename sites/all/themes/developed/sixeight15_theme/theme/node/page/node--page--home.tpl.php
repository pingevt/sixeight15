<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>

    <?php print render($content['home_page_carousel']); ?>

    <div class="row">
      <div class="col-sm-10 col-md-offset-1">
        <?php print render($content['field_body']); ?>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-10 col-md-offset-1">
        <?php print render($content['home_page_blocks']); ?>
      </div>
    </div>

  </div>

</div>
