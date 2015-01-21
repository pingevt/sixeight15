<?php
  // dpm($item);
?>


<div class="row flyin-menu" id="<?php print $item['#flyin-id']; ?>" data-target="<?php print $item['#flyin-id']; ?>">
  <div class="col-md-5">
    <span class="menu-message"><?php print $item['#title']; ?></span>
  </div>
  <div class="col-md-6">
    <div class="row">
      <?php print drupal_render_children($item); ?>
    </div>
  </div>
</div>
