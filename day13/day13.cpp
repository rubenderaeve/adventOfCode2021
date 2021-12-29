#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>

auto PartOneAndTwo(std::set<std::pair<int, int>> paper, std::vector<std::pair<char, int>> instr) {
	auto partOne = -1;
	for (auto fold : instr) {
		std::set<std::pair<int, int>> paperAfterFold;
		for (auto point : paper) {

			if (fold.first == 'x' && point.first > fold.second)
				point.first = fold.second * 2 - point.first;
			else if (fold.first == 'y' && point.second > fold.second)
				point.second = fold.second * 2 - point.second;

			paperAfterFold.insert(point);
		}
		if (partOne == -1)
			partOne = paperAfterFold.size();

		paper = paperAfterFold;
	}
	return std::make_pair(partOne, paper);
}


std::ostream& operator<<(std::ostream& o, const std::set<std::pair<int, int>>& paper)
{
	auto max_x = INT_MIN, max_y = INT_MIN;
	for (auto& point : paper)
		max_x = std::max(point.first, max_x), max_y = std::max(point.second, max_y);

	for (auto y = 0; y <= max_y; y++)
	{
		for (auto x = 0; x <= max_x; x++)
			o << (paper.find(std::make_pair(x, y)) == paper.end() ? '.' : '#');

		o << std::endl;
	}
	return o << std::endl;
}


auto ReadInput(const std::string& filename) {
	std::ifstream file(filename);
	std::string	line;
	std::set<std::pair<int, int>> paper;
	std::vector<std::pair<char, int>> instr;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		if (line.substr(0, 4) == "fold") {
			std::string fold, along;
			auto xOrY = 'x', equal = '=';
			auto number = 0;
			ss >> fold >> along >> xOrY >> equal >> number;
			instr.push_back(std::make_pair(xOrY, number));
		}
		else if (line.length() > 0) {
			auto x = 0, y = 0;
			char comma = ',';
			ss >> x >> comma >> y;
			paper.insert(std::make_pair(x, y));
		}
	}
	return std::make_pair(paper, instr);
}



int main() {
	auto input = ReadInput("input.txt");
	auto result = PartOneAndTwo(input.first, input.second);
	std::cout << "Part One:" << result.first << std::endl;
	std::cout << "Part two:" << std::endl << result.second;
}
