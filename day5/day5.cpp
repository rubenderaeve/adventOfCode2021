#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>

int main()
{
	std::cout << "Day 5\n";
	std::string line;
	std::ifstream file("input.txt");
	std::map<std::tuple <int, int>, int> floorPartOne;
	std::map<std::tuple <int, int>, int> floorPartTwo;

	while (std::getline(file, line)) {
		std::string delimiter = " -> ";
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
		}
		int x1 = stoi(token.substr(0, token.find(',')));
		int y1 = stoi(token.substr(token.find(',') + 1, token.length() - token.find(',') - 1));
		int x2 = stoi(line.substr(0, line.find(',')));
		int y2 = stoi(line.substr(line.find(',') + 1, line.length() - line.find(',') - 1));
		if (x1 == x2) {
			for (size_t i = std::min(y1, y2); i <= std::max(y1, y2); i++)
			{
				std::tuple<int, int> key = std::make_tuple(x1, i);
				floorPartOne[key] = floorPartOne.count(key) ? floorPartOne[key] + 1 : 1;
				floorPartTwo[key] = floorPartTwo.count(key) ? floorPartTwo[key] + 1 : 1;
			}
		}
		if (y1 == y2) {
			for (size_t i = std::min(x1, x2); i <= std::max(x1, x2); i++)
			{
				std::tuple<int, int> key = std::make_tuple(i, y1);
				floorPartOne[key] = floorPartOne.count(key) ? floorPartOne[key] + 1 : 1;
				floorPartTwo[key] = floorPartTwo.count(key) ? floorPartTwo[key] + 1 : 1;
			}
		}
		if (std::abs(x1 - x2) == std::abs(y1 - y2)) {
			for (size_t i = 0; i <= std::abs(x1 - x2); i++)
			{
				std::tuple<int, int> key = std::make_tuple(x1 - (x1 - x2) / (std::abs(x1 - x2)) * i, y1 - (y1 - y2) / (std::abs(y1 - y2)) * i);
				floorPartTwo[key] = floorPartTwo.count(key) ? floorPartTwo[key] + 1 : 1;
			}
		}
	}
	int numberOfDangerousPoins = 0;
	int numberOfDangerousPoinsPartTwo = 0;
	for (auto const& x : floorPartOne)
	{
		if (x.second > 1) {
			numberOfDangerousPoins += 1;
		}
	}
	for (auto const& x : floorPartTwo)
	{
		if (x.second > 1) {
			numberOfDangerousPoinsPartTwo += 1;
		}
	}
	std::cout << "numberOfPointsPartOne: " << numberOfDangerousPoins << std::endl;
	std::cout << "numberOfPointsPartTwo: " << numberOfDangerousPoinsPartTwo << std::endl;
}

