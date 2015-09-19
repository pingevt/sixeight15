<?php include_once($inc_header); ?>

<div class="drupal-admin-stuff">
  <div class="container">
    <div class="row">
      <?php print render($title_prefix); ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
    </div>
  </div>
</div>

<div class="main-container">
  <div class="container">
    <header role="banner" id="page-header">
      <?php if (!empty($site_slogan)): ?>
        <p class="lead"><?php print $site_slogan; ?></p>
      <?php endif; ?>

      <?php print render($page['header']); ?>
    </header> <!-- /#page-header -->

    <div class="row">

      <section<?php print $content_column_class; ?>>
        <a id="main-content"></a>

        <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
        <?php endif; ?>
        <div class="col-md-10 col-md-offset-1">
          <?php print render($page['content']); ?>
        </div>
      </section>

    </div>
  </div>
</div>

<?php include_once($inc_footer); ?>
