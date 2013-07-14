<div class="main">
	<div class="page">
		<div class="header">
                  <?php if ($logo): ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
                      <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                    </a>
                  <?php endif; ?>
                <p class="header_p">Таврический Национальный Университет <br/> <span>им. В.И.Вернадского</span><br>Факультет управления</p>
           	<div class="top_menu">
            	<div class="top_menu_container">
                    <?php print strip_tags(render($page['header_menu']), '<a>'); ?>
                </div>
<div class="top_menu_yellow">
        <div class="flags">
            <?php print render($page['language_box']); ?>
        </div>
        <div class="search_block">
            <?php print render($page['search_box']); ?>
        </div>
        
</div>
          </div>
        </div>
        <div class="middle">
            <div class="menu">  

                   <div class="menu_bg"></div>
                        <div class="menu_links">
                            <?php if ($secondary_menu) { print theme('links__system_secondary_menu', array('links' => $secondary_menu)); echo '<br />';}?>
                            <?php print strip_tags(render($page['left_menu']), '<a>'); ?>
                            <?php print render($page['left_menu_contacts']); ?>
                        </div>   
              </div>           
        </div>
        <div class="widget">
                <div class="widget_left_top"></div>
                <div class="widget_top"></div>               
                <div class="widget_left_bottom"></div>   
                <div class="widget_bottom"></div>     
        </div>
        <div class="second_level">        	       
            <div class="second_level_content">    
            	<div class="min-height"></div>  
                <div class="second_level_text">
       <?php if ($breadcrumb): ?>
       <div id="breadcrumb"><?php print $breadcrumb; ?></div>
       <?php endif; ?>

       <?php print $messages; ?>

            <div id="main-wrapper"><div id="main" class="clearfix">

           <div id="content" class="column"><div class="section">
             <a id="main-content"></a>
             <?php print render($title_prefix); ?>
             <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
             <?php print render($title_suffix); ?>
             <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
             <?php print render($page['help']); ?>
             <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
             <?php print render($page['content']); ?>
             <?php print $feed_icons; ?>
           </div></div> <!-- /.section, /#content -->   
                   </div>
           </div>     
       </div>
       </div>

  </div>
          <div class="search_box">
        	<p></p>
       	  <div class="search_left"></div>
            <div class="search_form">
                <form>
                    <div align="right"><br />
                     2012 © Таврический национальный университет им. В. И. Вернадского              </div>
                </form>
            </div>
            <div class="search_right"></div>
        </div>          
    <div class="page_down"> 
     	
    </div>
  </div>
</div>
 <script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-36660959-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>
