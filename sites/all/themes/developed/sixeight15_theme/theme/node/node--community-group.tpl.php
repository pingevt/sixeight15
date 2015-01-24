<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

  <?php print render($content['field_cg_image']); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      //print render($content);
    ?>

    <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
    <?php print render($content['field_cg_people']); ?>
    <?php print render($content['field_cg_email']); ?>
    <?php print render($content['field_cg_where']); ?>
    <?php print render($content['field_cg_when']); ?>
    <?php print render($content['field_cg_partner']); ?>
  </div>

</div>
