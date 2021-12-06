#include <iostream>
#include <string>
#include <fstream>
#include <map>

long long partOne(std::map<long long, long long> currentDay, long long days) {
	std::map<long long, long long> nextDay;
	for (size_t i = 0; i < days; i++)
	{
		for (size_t i = 0; i < currentDay.size(); i++)
		{
			if (i == 0) {
				nextDay[6] = currentDay[i];
				nextDay[8] = currentDay[i];
			}
			else {
				nextDay[i - 1] = nextDay.count(i - 1) ? nextDay[i - 1] + currentDay[i] : currentDay[i];
			}
		}
		currentDay = nextDay;
		nextDay.clear();
	}
	long long sum = 0;
	for (auto const& x : currentDay)
	{
		sum += x.second;
	}
	return sum;
}

int main()
{
	std::cout << "Day 6\n";
	std::string tmp;
	std::map<long long, long long> currentDay;
	std::ifstream file("input.txt");
	while (std::getline(file, tmp, ',')) {
		currentDay[stoi(tmp)] = currentDay.count(stoi(tmp)) ? currentDay[stoi(tmp)] + 1 : 1;
	}
	std::cout << "Part one: " << partOne(currentDay, 80) << std::endl;
	std::cout << "Part two: " << partOne(currentDay, 256);
}

