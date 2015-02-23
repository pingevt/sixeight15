<?php
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      //print render($content);
    ?>

    <div class="row">

      <div class="col-sm-3 col-sm-push-9">
        <div class="visible-xs-block"><?php print render($content['field_sermon_date']); ?></div>
        <?php print render($content['field_sermon_image']); ?>
      </div>

      <div class="col-sm-5 col-sm-pull-3 desc-col">
        <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
        <?php print render($content['field_sermon_series']); ?>
        <?php print render($content['field_speaker']); ?>
        <?php print render($content['field_sermon_scripture_passage']); ?>
      </div>

      <div class="col-sm-4 col-sm-pull-3 dwnld-col">
        <div class="hidden-xs"><?php print render($content['field_sermon_date']); ?></div>
        <?php print render($content['field_sermon_audio']); ?>
        <?php print render($content['field_sermon_slides']); ?>
        <?php print render($content['field_sermon_text']); ?>
        <?php print render($content['field_sermon_activity']); ?>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-12">
        <button class="btn btn-link sermon-desc-collapse-btn" type="button" id="collapse-desc-<?php print $node->nid; ?>-trigger" data-toggle="collapse" data-target="#collapse-desc-<?php print $node->nid; ?>" aria-expanded="false" aria-controls="collapse-desc-<?php print $node->nid; ?>">
          <span>open</span> description <i class="fa fa-arrow-up fa-rotate-180"></i>
        </button>


        <div class="collapse sermon-desc-collapse" id="collapse-desc-<?php print $node->nid; ?>">
          <?php print render($content['field_sermon_description']); ?>
        </div>
      </div>
    </div>
  </div>

</div>
