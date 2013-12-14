angular.module('sheepsheadApp', []).controller('SheepsheadScoreCtrl', function ($scope, $http) {
	$scope.playerCount = 0;
	$scope.playerScores = [];
	
	$scope.addPlayer = function () {
		var index = $scope.playerCount++;
		$scope.playerScores.push({
			nameId: 'player' + index + 'Name',
			name: '',
			scoreId: 'player' + index + 'Score',
			score: 0
		});
	};
	
	for (number = 0; number < 6; ++number)
		$scope.addPlayer();
	
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

