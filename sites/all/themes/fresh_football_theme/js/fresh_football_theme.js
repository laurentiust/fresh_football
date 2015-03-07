(function($) {

	$(document).ready(function() {
		
		var buttons = [
				['', 'Back to login'],
				['Forgot password?', 'Join us'],
				['Back to login', '']
			];

		// add placeholder, because..... drupal
		$('input.form-text').each( function() {
			$(this).attr('placeholder', $(this).prev().text());
		});

		$('#fresh-football-pass-form').insertBefore( $('#user-login') );
		$('#home-page form').wrapAll('<div class="owl" />');

		$(".owl").owlCarousel({
			navigation : true,
			singleItem: true,
			slideSpeed: 300,
			addClassActive : true,
			rewindNav : false,
			pagination : false,
			afterMove: function() {
				var id = $('.owl-item.active').find('form').attr('id');
				var button_values = buttons[ $('.owl-item.active').index() ];
				$('body')
					.removeClass('fresh-football-pass user-register user-login')
					.addClass( id.replace('-form', '') );
				$('.owl-prev', '.owl-buttons').text( button_values[0] );
				$('.owl-next', '.owl-buttons').text( button_values[1] );
			} 
		});

		var owl = $(".owl").data('owlCarousel');
		owl.jumpTo(1);

		var intervalID = setInterval(fetchData, 60000);

		function fetchData() {
			$.ajax({
				url: '/api/get-teams',
				//url: '/sites/all/themes/fresh_football_theme/js/test.json',
				type: 'POST',
				dataType: 'json',
				contentType: 'application/json',
			}).done( function(data) {
				renderPlayers( data.teams || { "teams": [[], []] } );
			}).fail( function() {
				renderPlayers( [[], []] );
			});
		}

		function renderPlayers( players ) {
			var $field = $('.fresh-football-field');
			$field.empty();

			$.each(players, function(i,team) {
				var $field_side = $('<div/>').addClass('field-side').appendTo( $field );
				var $penalty_area = $('<div/>').addClass('penalty-area').appendTo( $field_side );
				var $goal_area = $('<div/>').addClass('goal-area').appendTo( $field_side );
				var $list = $('<ul/>').addClass('team-' + (i+1)).appendTo( $field_side );
				for (var i = 0; i < 5; i++) {
					var player = team[i];
					var photo = player ? (player.picture || 'sites/all/themes/fresh_football_theme/images/default-player.png') : 'sites/all/themes/fresh_football_theme/images/empty-slot.png';
					var $item = $('<li/>').appendTo( $list );
					var $link = $('<a/>').appendTo( $item );
					var $photo = $('<img/>').attr('src', photo).appendTo( $link );
					if ( player ) {
						var $name = $('<span/>').text(player.name).appendTo( $link );
					}
				}
				$field_side.height( $field_side.width() * 0.75 );
			});
		}

		function throttle(fn, threshhold, scope) {
			threshhold || (threshhold = 250);
			var last,
				deferTimer;
			return function () {
				var context = scope || this;
				var now = +new Date,
				args = arguments;
				if (last && now < last + threshhold) {
					clearTimeout(deferTimer);
					deferTimer = setTimeout(function () {
						last = now;
						fn.apply(context, args);
					}, threshhold);
				} else {
					last = now;
					fn.apply(context, args);
				}
			};
		}

		var updateFieldPitch = throttle(function() {
			if ( $('.field-side').length ) {
				$('.field-side').each( function() {
					$(this).height( $(this).width() * 0.75 );
				});
			}
		}, 100);

		// monitor resize on window and update the football pitch if exists
		$(window).on('resize', updateFieldPitch);

		fetchData();

	});

})(jQuery);