var app = angular.module('sheepsheadApp', []);
app.controller('PlayerGamesCtrl', function ($scope) {
	$('.form-control[name="player"]').autocomplete({
		source: function (request, response) {
			$.get('/sheepshead.cgi', { action: 'name-lookup', query: request.term })
				.done(function (data) {
					response(data.names);
				});
		}
	});
	$scope.player = window.initialData;
});

