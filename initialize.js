$(document).ready(function () {
	$('.name-lookup').autocomplete({
		source: function (request, response) {
			$.get('/sheepshead.cgi', { action: 'name-lookup', query: request.term })
				.done(function (data) {
					response(data.names);
				});
		}
	});
});

