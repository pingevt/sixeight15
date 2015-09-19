<?php
global $user;

if ($user->uid == 1): ?>

<div class="hidden-xs hidden-sm hidden-md" style="color: white; background: black; position: fixed; left: 0; bottom: 0; z-index: 99999; padding: 6px;">
LARGE
</div>
<div class="hidden-xs hidden-sm hidden-lg" style="color: white; background: black; position: fixed; left: 0; bottom: 0; z-index: 99999; padding: 6px;">
MEDIUM
</div>
<div class="hidden-xs hidden-md hidden-lg" style="color: white; background: black; position: fixed; left: 0; bottom: 0; z-index: 99999; padding: 6px;">
SMALL
</div>
<div class="hidden-sm hidden-md hidden-lg" style="color: white; background: black; position: fixed; left: 0; bottom: 0; z-index: 99999; padding: 6px;">
X_SMALL
</div>

<?php endif; ?>



<nav id="mobileMenu" class="navmenu navmenu-default navmenu-fixed-left offcanvas" role="navigation" >
  <?php print $search; ?>

  <hr />

  <?php if (!empty($mobile_nav)): ?>
    <?php print render($mobile_nav); ?>
  <?php endif; ?>
</nav>

<div id="header-bar">
  <div class="container">
    <div class="row">
      <div class="col-sm-9">

        <button type="button" class="navbar-toggle" data-toggle="offcanvas" data-target="#mobileMenu" data-canvas="body">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button>

        <ul>
          <li><?php print l('Times & Locations', 'node/2'); ?></li>
          <li><?php print $facebook; ?></li>
          <li><?php print $twitter; ?></li>
          <li><?php print $vimeo; ?></li>
        </ul>
      </div>

      <div class="col-sm-3 hidden-xs">
        <?php print $search; ?>
      </div>
    </div>
  </div>
</div>

<header id="navbar" role="banner" class="">
  <div class="container">
    <div class="row menu-row-wrapper">
      <div class="col-xs-10 col-xs-offset-1 col-sm-6 col-sm-offset-3 col-md-4 col-md-offset-0 double-border">
        <a href="/" ><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="img-responsive" /></a>
      </div>
      <div class="col-xs-12 col-sm-12 col-md-8 menu-col-wrapper">
        <div class="row">
          <div class="col-md-12">
            <p class="tagline">Act Justly. Love Mercy. Walk Humbly.</p>
          </div>
        </div>
        <div class="row menu-row hidden-xs">
          <div class="col-md-12">
            <nav role="navigation">
              <?php if (!empty($primary_nav)): ?>
                <?php print render($primary_nav); ?>
              <?php endif; ?>
            </nav>
          </div>
        </div>
      </div>
      </div>
  </div>

  <?php if (!empty($secondary_nav)): ?>
    <?php print render($secondary_nav); ?>
  <?php endif; ?>

</header>