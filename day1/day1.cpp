#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <ranges>
#include <vector>
#include <numeric>

int main()
{
	std::ifstream infile;
	infile.open("./inputDayOne.txt");
	int number;
	std::list<int> input;
	int resultTaskOne = 0;
	int resultTaskTwo = 0;
	int previous = 4000000;
	while (infile >> number) {
		input.push_back(number);
		resultTaskOne += number > previous ? 1 : 0;
		previous = number;
	}

	std::vector<int> v{ std::begin(input), std::end(input) };
	for (size_t i = 3; i < input.size(); i++)
	{
		resultTaskTwo += v[i] > v[i - 3] ? 1 : 0;
	}

	std::cout << "Task one:  " << resultTaskOne;
	std::cout << "\nTask two:  " << resultTaskTwo;


}

