<?php
dpm($carousel);
?>
<div id="<?php print $carousel['#id']; ?>" class="carousel slide" data-ride="carousel">
  <!-- Indicators -->
  <ol class="carousel-indicators">
    <?php
      foreach ($carousel['#items'] as $i => $item) {
        print '<li data-target="#' . $carousel['#id'] . '" data-slide-to="' . $i . '" ';
        if ($i == 0) print 'class="active"';
        print '></li>';
      }
    ?>
  </ol>

  <!-- Wrapper for slides -->
  <div class="carousel-inner" role="listbox">
    <?php
      foreach ($carousel['#items'] as $i => $item) {
        print '<div class="item';
        if ($i == 0) print ' active';
        print '">';

        print $item['img'];

        print '</div>';
      }
    ?>
  </div>

  <!-- Controls -->
  <!--
  <a class="left carousel-control" href="#<?php print $carousel['#id']; ?>" role="button" data-slide="prev">
    <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
    <span class="sr-only">Previous</span>
  </a>
  <a class="right carousel-control" href="#<?php print $carousel['#id']; ?>" role="button" data-slide="next">
    <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
    <span class="sr-only">Next</span>
  </a>
  -->
</div>
