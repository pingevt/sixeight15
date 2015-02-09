<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
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





<div id="header-bar">
  <div class="container">
    <div class="row">
      <div class="col-sm-9">
        <ul>
          <li><?php print l('Times & Locations', ''); ?></li>
          <li><?php print $facebook; ?></li>
          <li><?php print $twitter; ?></li>
          <li><?php print $vimeo; ?></li>
        </ul>
      </div>

      <div class="col-sm-3">
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
        <div class="row menu-row">
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

        <?php print render($page['content']); ?>
      </section>

    </div>
  </div>
</div>


<footer class="footer">
  <div class="container">
    <div class="row">
      <div class="col-sm-5 col-sm-offset-1">
        <h5>Six:Eight Vineyard Church</h5>

        <div class="row">
          <div class="col-sm-6">
            <p class="address"><span class="address-label">Office:</span><br />
            134 Sibley Ave<br />
            Ardmore, PA 19003</p>
          </div>
          <div class="col-sm-6">
            <p class="address"><span class="address-label">Meeting:</span><br />
            241 E. Lancaster Ave<br />
            Wynnewood, PA 19096</p>
          </div>
        </div>

        <ul class="social-icon-menu">
          <li><?php print $facebook; ?></li>
          <li><?php print $twitter; ?></li>
          <li><?php print $vimeo; ?></li>
        </ul>

      </div>
      <div class="col-sm-5 text-right">

<!-- Begin MailChimp Signup Form -->
<link href="//cdn-images.mailchimp.com/embedcode/classic-081711.css" rel="stylesheet" type="text/css">
<div id="mc_embed_signup">
<form action="//sixeight.us1.list-manage.com/subscribe/post?u=701991a51894b17f831833155&amp;id=75bb132ec6" method="post" id="mc-embedded-subscribe-form" name="mc-embedded-subscribe-form" class="validate" target="_blank" novalidate>
    <div id="mc_embed_signup_scroll">
	<h2>Subscribe to our Newsletter</h2>
<div class="indicates-required"><span class="asterisk">*</span> indicates required</div>
<div class="mc-field-group">
	<label for="mce-EMAIL">Email Address  <span class="asterisk">*</span>
</label>
	<input type="email" value="" name="EMAIL" class="required email" id="mce-EMAIL" placeholder="Email Address:" />
</div>
<div class="mc-field-group">
	<label for="mce-FNAME">First Name </label>
	<input type="text" value="" name="FNAME" class="" id="mce-FNAME" placeholder="First Name:" />
</div>
<div class="mc-field-group">
	<label for="mce-LNAME">Last Name </label>
	<input type="text" value="" name="LNAME" class="" id="mce-LNAME" placeholder="Last Name:" />
</div>
	<div id="mce-responses" class="clear">
		<div class="response" id="mce-error-response" style="display:none"></div>
		<div class="response" id="mce-success-response" style="display:none"></div>
	</div>    <!-- real people should not fill this in and expect good things - do not remove this or risk form bot signups-->
    <div style="position: absolute; left: -5000px;"><input type="text" name="b_701991a51894b17f831833155_75bb132ec6" tabindex="-1" value=""></div>
    <div class="clear"><input type="submit" value="Subscribe" name="subscribe" id="mc-embedded-subscribe" class="button"></div>
    </div>
</form>
</div>
<script type='text/javascript' src='//s3.amazonaws.com/downloads.mailchimp.com/js/mc-validate.js'></script><script type='text/javascript'>(function($) {window.fnames = new Array(); window.ftypes = new Array();fnames[0]='EMAIL';ftypes[0]='email';fnames[1]='FNAME';ftypes[1]='text';fnames[2]='LNAME';ftypes[2]='text';}(jQuery));var $mcj = jQuery.noConflict(true);</script>
<!--End mc_embed_signup-->

      </div>
    </div>


    <div class="row">
      <div class="col-sm-5 col-sm-offset-1">
        <p class="copywrite-data">&copy; <?php print date('Y'); ?> Six:Eight Vineyard Church<br />
        <span>Act</span> justly. <span>Love</span> Mercy. <span>Walk</span> Humbly.</p>
      </div>
      <div class="col-sm-5 text-right">
        <p class="vineyard-usa-link"><?php print $vineyard_footer_link; ?></p>
      </div>
    </div>

    <?php print render($page['footer']); ?>
  </div>
</footer>

