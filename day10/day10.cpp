#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>


auto ReadInput(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;
	std::vector<std::vector<char>> input;
	while (std::getline(file, line)) {
		input.push_back(std::vector<char>());
		for (auto& ch : line) {
			input.back().push_back(ch);
		}
	}
	return input;
}

auto PartOneTwo(std::vector<std::vector<char>> input) {
	long long resOne = 0;
	long long resTwo = 0;
	std::map<char, char> match{ {')','('},{']','['},{'}','{'},{'>','<'} };
	std::map<char, int> pointsOne{ { ')', 3 }, { ']',57 }, { '}',1197 }, { '>',25137 } };
	std::map<char, int> pointsTwo{ { '(', 1 }, { '[',2 }, { '{',3 }, { '<',4 } };
	std::vector<long long> scoreLines;
	for (int row = 0; row < input.size(); row++) {
		std::vector<char> line;
		bool corrupt = false;
		for (int col = 0; col < input[row].size(); col++)
		{
			if (pointsOne.count(input[row][col])) {
				if (line.back() != match[input[row][col]]) {
					resOne += pointsOne[input[row][col]];
					corrupt = true;
					break;
				}
				else {
					line.pop_back();
				}
			}
			else {
				line.push_back(input[row][col]);
			}
		}
		auto resLine = 0LL;
		if (!corrupt && line.size() > 0) {
			for (int i = line.size() - 1; i > -1; i--)
			{
				resLine = resLine * 5 + pointsTwo[line[i]];
			}
			scoreLines.push_back(resLine);
		}
	}
	std::sort(scoreLines.begin(), scoreLines.end());
	resTwo = scoreLines[scoreLines.size() / 2];
	return std::make_pair(resOne, resTwo);
}

int main() {
	std::cout << "Day10\n";
	auto input = ReadInput("input.txt");
	auto res = PartOneTwo(input);
	std::cout << "partOne: " << res.first << std::endl; // 413733
	std::cout << "partTwo: " << res.second << std::endl; // 3354640192 
};
