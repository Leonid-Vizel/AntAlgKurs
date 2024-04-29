#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void all_combinations(vector<int> nums);

std::vector<std::pair<int, int>> posVec = {
		std::make_pair(50, 50),
		std::make_pair(100, 50),
		std::make_pair(150, 50),
		std::make_pair(1750, 50),
		std::make_pair(1750, 100),
		std::make_pair(1750, 150),
		std::make_pair(1750, 800),
		std::make_pair(1750, 850),
		std::make_pair(100, 850),
		std::make_pair(50, 850)
};

int main() {
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	all_combinations(nums);
	return 0;
}

void printPath(std::vector<int> path) {
	for (int i = 0; i < path.size(); ++i) {
		std::cout << path[i];
		if (i != path.size() - 1)
		{
			std::cout << " -> ";
		}
	}
	std::cout << endl;
}

int calculateDistance(std::vector<int> path) {
	int totalDistance = 0;
	int x1, x2, y1, y2;
	for (int i = 0; i < path.size() - 1; ++i) {
		x1 = posVec[path[i]].first;
		y1 = posVec[path[i]].second;
		x2 = posVec[path[i + 1]].first;
		y2 = posVec[path[i + 1]].second;
		totalDistance += abs(x2 - x1) + abs(y2 - y1);
	}
	return totalDistance;
}

void all_combinations(vector<int> nums) {
	int minLength = INT_MAX;
	vector<int> minVector;

	do {
		vector<int> currentVector = { 0 };
		for (int num : nums) {
			currentVector.push_back(num);
		}
		currentVector.push_back(0);
		int length = calculateDistance(currentVector);
		if (length < minLength)
		{
			minLength = length;
			minVector = currentVector;
		}
	} while (next_permutation(nums.begin(), nums.end()));

	cout << "MIN: " << minLength << endl;
	printPath(minVector);
}
