angular.module('sheepsheadApp', []).controller('SheepsheadScoreCtrl', function ($scope, $http) {
	$scope.player1Name = '';
	$scope.player1Score = 0;
	$scope.player2Name = '';
	$scope.player2Score = 0;
	$scope.player3Name = '';
	$scope.player3Score = 0;
	$scope.player4Name = '';
	$scope.player4Score = 0;
	$scope.player5Name = '';
	$scope.player5Score = 0;
	$scope.player6Name = '';
	$scope.player6Score = 0;
	
	$scope.getPositivePointSpread = function () {
		var pointSpread = 0;
		if ($scope.player1Score > 0)
			pointSpread += $scope.player1Score;
		if ($scope.player2Score > 0)
			pointSpread += $scope.player2Score;
		if ($scope.player3Score > 0)
			pointSpread += $scope.player3Score;
		if ($scope.player4Score > 0)
			pointSpread += $scope.player4Score;
		if ($scope.player5Score > 0)
			pointSpread += $scope.player5Score;
		if ($scope.player6Score > 0)
			pointSpread += $scope.player6Score;
		return pointSpread;
	};
	
	$scope.getCheckSum = function() {
		return $scope.player1Score +
			$scope.player2Score +
			$scope.player3Score +
			$scope.player4Score +
			$scope.player5Score +
			$scope.player6Score;
	};
	
	$scope.isValid = function() {
		return $scope.getCheckSum() == 0 &&
			$scope.player1Name > '' &&
			$scope.player2Name > '' &&
			$scope.player3Name > '' &&
			$scope.player4Name > '' &&
			$scope.player5Name > '';
	};
});

