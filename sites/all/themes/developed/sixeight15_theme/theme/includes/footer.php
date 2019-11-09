
<footer class="footer">
  <div class="container">
    <div class="row">
      <div class="col-sm-5 col-sm-offset-1">
        <h5>Six:Eight Vineyard Church</h5>

        <div class="row">
          <div class="col-sm-6">
            <p class="address">
            1116 Lancaster Avenue<br />
            Bryn Mawr, PA 19010<br />
            610-525-7514</p>

            <!--

            <p class="address"><span class="address-label">Office/Mailing:</span><br />
            134 Sibley Ave<br />
            Ardmore, PA 19003<br />
            610-733-8856</p>
          </div>
          <div class="col-sm-6">
            <p class="address"><span class="address-label">Meeting:</span><br />
            1116 Lancaster Avenue<br />
            Bryn Mawr, PA 19010</p>

            -->
          </div>
        </div>

        <ul class="social-icon-menu">
          <li><?php print $facebook; ?></li>
          <li><?php print $twitter; ?></li>
          <li><?php print $vimeo; ?></li>
        </ul>

        <?php if ($user->uid == 0): ?>
          <p class="admin-login-link"><a href="/user"> Admin Login <i class="fa fa-sign-in"></i></a></p>
        <?php endif; ?>

      </div>
      <div class="col-sm-5 text-right">

<div id="newsletter-signup">
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
    </div>


    <div class="row">
      <div class="col-sm-5 col-sm-offset-1">
        <p class="copywrite-data">&copy; <?php print date('Y'); ?> Six:Eight Vineyard Church<br />
        <span>Act</span> Justly. <span>Love</span> Mercy. <span>Walk</span> Humbly.</p>
      </div>
      <div class="col-sm-5 text-right">
        <p class="vineyard-usa-link"><?php print $vineyard_footer_link; ?></p>
      </div>
    </div>

    <?php print render($page['footer']); ?>
  </div>
</footer>
