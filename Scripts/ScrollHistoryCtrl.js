var app = angular.module('sheepsheadApp', []);
app.directive('whenScrolled', function () {
	return function ($scope, element, attr) {
		window.onscroll = function () {
			var body = $('body')[0];
			var height = body.offsetHeight;
			var position = body.scrollTop;
			if ((position + 1000) > height) {
				$scope.$apply(attr.whenScrolled);
			}
		};
	};
});
app.controller('ScrollHistoryCtrl', function ($scope) {
	$scope.reports = [];
	var skip = 10;
	var more = true;
	$scope.addReports = function (reports) {
		if (reports.length == 0) {
			more = false;
		} else {
			for (var index = 0; index < reports.length; ++index) {
				++skip;
				$scope.reports.push(reports[index]);
			}
			$scope.$digest();
		}
	};
	$scope.loadMore = function () {
		if (more) {
			$.get('/sheepshead.cgi', { action: 'load-history', skip: skip })
				.done(function (data) {
					$scope.addReports(data.reports);
				});
		}
	};
});

