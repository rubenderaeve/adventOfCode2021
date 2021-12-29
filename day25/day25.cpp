#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

auto doStep(std::vector<std::vector<char>>& map, std::vector<std::tuple<int, int>>& emptySpots) {
	int row;
	int col;
	bool somethingMoved = true;
	int iterations = 0;
	while (somethingMoved) {
		iterations++;
		somethingMoved = false;
		auto mapOld(map);
		for (int i = 0; i < emptySpots.size(); i++)
		{
			std::tie(row, col) = emptySpots[i];
			int colEdit = (col - 1 + map[row].size()) % map[row].size();
			if (mapOld[row][colEdit] == '>') {
				emptySpots[i] = std::make_tuple(row, colEdit);
				map[row][colEdit] = '.';
				map[row][col] = '>';
				somethingMoved = true;
			}
		}
		for (int i = 0; i < emptySpots.size(); i++)
		{
			std::tie(row, col) = emptySpots[i];
			int rowEdit = (row - 1 + map.size()) % map.size();
			if (mapOld[rowEdit][col] == 'v') {
				emptySpots[i] = std::make_tuple(rowEdit, col);
				map[rowEdit][col] = '.';
				map[row][col] = 'v';
				somethingMoved = true;
			}
		}
	}
	return iterations;
}


auto process_input(const std::string& filename)
{
	std::vector<std::vector<char>> map;
	std::ifstream file(filename);
	std::string line;
	std::vector<std::tuple<int, int>> emptySpots;
	int rw = 0;
	while (std::getline(file, line)) {
		std::vector<char> row;
		int col = 0;
		for (auto c : line) {
			row.push_back(c);
			if (c == '.') emptySpots.push_back(std::make_tuple(rw, col));
			col++;
		}
		map.push_back(row);
		rw++;
	}
	return std::make_pair(map, emptySpots);
}

int main()
{
	auto result = process_input("input.txt");
	auto numberOfSteps = doStep(result.first, result.second);
	std::cout << "Part 1: " << numberOfSteps << std::endl;
	return 0;
}