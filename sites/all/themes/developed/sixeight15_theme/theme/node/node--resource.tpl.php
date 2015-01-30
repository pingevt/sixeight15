<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

  <div class="row">
    <div class="content col-sm-9"<?php print $content_attributes; ?>>
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
      <p class="info">Update: <span><?php print format_date($changed, 'custom', 'm.d.Y'); ?></span> | Format: <span><?php print $format; ?></span></p>
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        hide($content['field_resource_image']);
        print render($content['field_resource_summary']);
      ?>
    </div>

    <div class="col-sm-3">
      <?php
      if (isset($content['field_resource_image'])) {
        print render($content['field_resource_image']);
      }
      ?>
    </div>
  </div>

  <?php
    switch($node->resource_type) {
    case 'url':
    case 'file':

      $node->resource_link['options']['attributes']['class'][] = 'full-block-link';
      print l('', $node->resource_link['path'], $node->resource_link['options']);

      break;
    case 'image':
      if (isset($content['field_resource_image']['#access']) && $content['field_resource_image']['#access'] == TRUE) {
        $options = array(
          'label' => 'hidden',
          'type' => 'resource_image_download',
        );
        $dl_link = field_view_field('node', $node, 'field_resource_image', $options);

        $content['main_dl_link'][] = $dl_link;
        $content['main_dl_link']['#prefix'] = '<div class="original-download-link">';
        $content['main_dl_link']['#suffix'] = '</div>';
      }
?>
    <button type="button" class="btn btn-primary btn-link full-block-link" data-toggle="modal" data-target="#resource-modal-<?php print $node->nid ?>"></button>

    <!-- Modal -->
    <div class="modal fade resource-modal" id="resource-modal-<?php print $node->nid ?>" tabindex="-1" role="dialog" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
         <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
            <h4 class="modal-title"><?php print $title; ?></h4>
          </div>
          <div class="modal-body">
            <?php
              $modal_img = field_view_field('node', $node, 'field_resource_image', array(
                'label' => 'hidden',
                'type' => 'image',
              ));
              print render($modal_img);
              print render($content['main_dl_link']);
              print render($content['field_resource_alt_img_formats']);
            ?>
          </div>
        </div>
      </div>
    </div>

<?php
      break;
    case 'video':
?>
    <button type="button" class="btn btn-primary btn-link full-block-link" data-toggle="modal" data-target="#resource-modal-<?php print $node->nid ?>"></button>

    <!-- Modal -->
    <div class="modal fade resource-modal" id="resource-modal-<?php print $node->nid ?>" tabindex="-1" role="dialog" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
         <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
            <h4 class="modal-title"><?php print $title; ?></h4>
          </div>
          <div class="modal-body">
            <?php
              print render($content['field_resource_video_url']);
            ?>
          </div>
        </div>
      </div>
    </div>

<?php
      break;
    }
  ?>
</div>

