<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix col-md-4 col-sm-6"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
    <h3<?php print $title_attributes; ?>><?php print $title; ?></h3>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
</div>
