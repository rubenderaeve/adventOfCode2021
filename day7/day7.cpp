#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
	std::cout << "Hello World!\n";
	std::string tmp;
	std::vector<int> v;
	std::ifstream file("input.txt");
	while (std::getline(file, tmp, ',')) {
		v.push_back(stoi(tmp));
	}

	//Part One
	size_t n = v.size() / 2;
	std::nth_element(v.begin(), v.begin() + n, v.end());
	int median = v[n];
	int fuel = 0;
	for (int& pos : v)
	{
		fuel += std::abs((int)(pos - median));
	}
	std::cout << "PartOne: " << fuel << std::endl;

	// Part Two
	std::vector<int> costForStep;
	costForStep.push_back(0);
	for (size_t i = 1; i < *std::max_element(v.begin(), v.end()); i++)
	{
		costForStep.push_back(costForStep[costForStep.size() - 1] + i);
	}
	std::vector<int> fuelsExpensive;
	double mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
	for (size_t i = (int)mean - 1; i < (int)mean + 1; i++)
	{
		int fuel = 0;
		for (int& pos : v)
		{
			fuel += costForStep[std::abs((int)(pos - i))];
		}
		fuelsExpensive.push_back(fuel);
	}
	int minElementPartTwo = *std::min_element(fuelsExpensive.begin(), fuelsExpensive.end());
	std::cout << "PartTwo: " << minElementPartTwo;
}

