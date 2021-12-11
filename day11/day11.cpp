#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>


auto ReadInput(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;
	std::vector<std::vector<int>> grid;
	while (std::getline(file, line)) {
		grid.push_back(std::vector<int>());
		for (auto& ch : line) {
			grid.back().push_back((int)ch - 48);
		}
	}
	return grid;
}


void DoStep(std::vector<std::vector<int>>& grid, int i, int j) {
	if (grid[i][j] == 10) {
		for (auto k = -1; k <= 1; k++)
			for (auto h = -1; h <= 1; h++)
			{
				if (k == 0 && h == 0)
					continue;

				auto new_i = i + k, new_j = j + h;

				if (new_i < 0 || new_i > grid.size() - 1 ||
					new_j < 0 || new_j > grid[new_i].size() - 1)
					continue;

				grid[new_i][new_j]++;
				DoStep(grid, new_i, new_j);
			}
	}
}


auto PartOneTwo(std::vector<std::vector<int>> grid) {
	int totalFlashes = 0;
	auto simulations = 100;
	auto res = std::make_pair(0, 0);
	for (size_t k = 0; k < simulations || !res.second; k++)
	{
		for (size_t i = 0; i < grid.size(); i++)
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				grid[i][j] += 1;
				DoStep(grid, i, j);
			}

		int flashes = 0;
		for (size_t i = 0; i < grid.size(); i++)
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] > 9) {
					flashes++;
					grid[i][j] = 0;
				}
			}
		totalFlashes += flashes;

		if (k == simulations - 1)
			res.first = totalFlashes;
		if (flashes == grid.size() * grid[0].size())
			res.second = k + 1;
	}
	return res;
}

int main() {
	std::cout << "Day11\n";
	auto grid = ReadInput("input.txt");
	auto res = PartOneTwo(grid);
	std::cout << "partOne: " << res.first << std::endl;
	std::cout << "partTwo: " << res.second << std::endl;
	assert(res.first == 1591);
	assert(res.second == 314);
}
