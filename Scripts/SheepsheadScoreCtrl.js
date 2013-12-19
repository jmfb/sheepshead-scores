var app = angular.module('sheepsheadApp', []);
app.directive('onRepeatDone', function () {
	return {
		link: function ($scope, element, attributes) {
			$scope.$emit(attributes['onRepeatDone'], element);
		}
	}; 
});
app.controller('SheepsheadScoreCtrl', function ($scope, $http) {
	$scope.$on('autocomplete', function (event, element) {
		element.find('.name-lookup').autocomplete({
			source: function (request, response) {
				$.get('/sheepshead.cgi', { action: 'name-lookup', query: request.term })
					.done(function (data) {
						response(data.names);
					});
			}
		});
	});
	
	$scope.playerCount = 0;
	$scope.playerScores = [];
	
	$scope.addPlayer = function () {
		var index = $scope.playerCount++;
		var nameId = 'player' + index + 'Name';
		$scope.playerScores.push({
			nameId: nameId,
			name: '',
			scoreId: 'player' + index + 'Score',
			score: 0
		});
	};

	for (number = 0; number < 6; ++number)
		$scope.addPlayer(false);
	
	$scope.getPositivePointSpread = function () {
		return $scope.playerScores.filter(function (playerScore) {
			return playerScore.score > 0;
		}).reduce(function (total, playerScore) {
			return total + playerScore.score;
		}, 0);
	};
	
	$scope.getCheckSum = function () {
		return $scope.playerScores.reduce(function (total, playerScore) {
			return total + playerScore.score;
		}, 0);
	};
	
	$scope.getPlayerCount = function () {
		return $scope.playerScores.filter(function (playerScore) {
			return playerScore.name > '';
		}).length;
	};
	
	$scope.isValid = function () {
		return $scope.getCheckSum() == 0 &&
			$scope.getPlayerCount() >= 5;
	};
});

