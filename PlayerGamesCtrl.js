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
	
	$scope.player = window.player;
	
	var context = document.getElementById("playerChart").getContext("2d");
	var chart = new Chart(context).Line(window.graphData, window.graphOptions);
});

