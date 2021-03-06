<?php

/**
 *  col-md-10 col-md-offset-1 col-sm-12
 */

?>
<div class="<?php print $classes; ?>">
  <div class="row">
    <div class="col-sm-9 col-md-9 col-lg-7 col-lg-offset-1">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if ($header): ?>
        <div class="view-header">
          <?php print $header; ?>
        </div>
      <?php endif; ?>
    </div>
    <div class=" col-sm-3 col-md-3 col-lg-2 col-lg-offset-1 menu-column">
      <?php print render($menu); ?>
    </div>
  </div>

  <div class="row">
    <div class="col-md-3 col-md-push-9 col-lg-2 col-lg-push-9">
      <?php if ($exposed): ?>
        <div class="view-filters">
          <?php print $exposed; ?>
        </div>
      <?php endif; ?>
    </div>

    <div class="col-md-9 col-md-pull-3 col-lg-7 col-lg-pull-1 view-content">
      <?php if ($attachment_before): ?>
        <div class="attachment attachment-before">
          <?php print $attachment_before; ?>
        </div>
      <?php endif; ?>

      <?php if ($rows): ?>
        <div class="view-content">
          <?php print $rows; ?>
        </div>
      <?php elseif ($empty): ?>
        <div class="view-empty">
          <?php print $empty; ?>
        </div>
      <?php endif; ?>

      <?php if ($pager): ?>
        <?php print $pager; ?>
      <?php endif; ?>

      <?php if ($attachment_after): ?>
        <div class="attachment attachment-after">
          <?php print $attachment_after; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>


  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
