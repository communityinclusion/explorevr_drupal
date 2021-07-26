(function ($) {

  Drupal.behaviors.PanelsAccordionStyle = {
    attach: function (context, settings) {
      for (region_id in Drupal.settings.accordion) {
        var accordion = Drupal.settings.accordion[region_id];
        if (jQuery('#'+region_id).hasClass("ui-accordion")) {
          jQuery('#'+region_id).accordion("refresh");
        } else {
          jQuery('#'+region_id).accordion(accordion.options);
        }
      }
    }
  };

})(jQuery);
;
(function ($) {
	Drupal.behaviors.backtotop = {
		attach: function(context) {
			var exist= jQuery('#backtotop').length;
      if(exist == 0) {
        $("body", context).once(function() {
          $(this).append("<button id='backtotop'>"+Drupal.t(Drupal.settings.back_to_top.back_to_top_button_text)+"</button>");
        });
      }
			$(window).scroll(function() {
				if($(this).scrollTop() > Drupal.settings.back_to_top.back_to_top_button_trigger) {
					$('#backtotop').fadeIn();
				} else {
					$('#backtotop').stop(true).fadeOut();
				}
			});

      $('#backtotop', context).once(function() {
			  $(this).click(function() {
			    $("html, body").bind("scroll mousedown DOMMouseScroll mousewheel keyup", function() {
            $('html, body').stop();
          });
          $('html,body').animate({ scrollTop: 0 }, 1200, 'easeOutQuart', function() {
            $("html, body").unbind("scroll mousedown DOMMouseScroll mousewheel keyup");
          });
          return false;
			  });
			});
		}
	};
})(jQuery);
;
