#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>



int resultPartOne(int distances[1000][12]) {
	int gamma = 0;
	int sum = 0;
	int epsilon = 0;
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 1000; ++j) {
			sum = sum + distances[j][i];
		}
		if (sum > 500) {
			gamma += pow(2, (11 - i));
		}
		else {
			epsilon += pow(2, (11 - i));
		}
		sum = 0;
	}
	return gamma * epsilon;
}

int resultPartTwoOxygen(int m[1000][12]) {
	std::set<int> indToIgnore;
	std::vector<int> indNull;
	std::vector<int> indOne;
	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 1000; j++)
		{
			if (indToIgnore.count(j) == 0) {
				if (m[j][i] == 1) {
					indOne.push_back(j);
				}
				else {
					indNull.push_back(j);
				}
			}
		}
		if (indOne.size() >= indNull.size()) {
			for (auto i : indNull) {
				indToIgnore.insert(i);
			}
		}
		else {
			for (auto i : indOne) {
				indToIgnore.insert(i);
			}
		}
		indOne.clear();
		indNull.clear();
		if (indToIgnore.size() == 999) {
			for (size_t i = 0; i < 1000; i++)
			{
				int oxygen = 0;
				if (indToIgnore.count(i) == 0) {
					for (size_t j = 0; j < 12; j++)
					{
						oxygen += pow(2, 11 - j) * m[i][j];
					}
					return oxygen;
				}
			}
		}
	}
}

int resultPartTwoCO(int m[1000][12]) {
	std::set<int> indToIgnore;
	std::vector<int> indNull;
	std::vector<int> indOne;
	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 1000; j++)
		{
			if (indToIgnore.count(j) == 0) {
				if (m[j][i] == 1) {
					indOne.push_back(j);
				}
				else {
					indNull.push_back(j);
				}
			}
		}
		if (indOne.size() >= indNull.size()) {
			for (auto i : indOne) {
				indToIgnore.insert(i);
			}
		}
		else {
			for (auto i : indNull) {
				indToIgnore.insert(i);
			}
		}
		indOne.clear();
		indNull.clear();
		if (indToIgnore.size() == 999) {
			for (size_t i = 0; i < 1000; i++)
			{
				int oxygen = 0;
				if (indToIgnore.count(i) == 0) {
					for (size_t j = 0; j < 12; j++)
					{
						oxygen += pow(2, 11 - j) * m[i][j];
					}
					return oxygen;
				}
			}
		}
	}
}



int resultPartTwo(int m[1000][12]) {
	int oxygen = resultPartTwoOxygen(m);
	int co = resultPartTwoCO(m);
	return oxygen * co;
}


int main()
{
	std::ifstream infile;
	infile.open("./inputDayThree.txt");
	int resultTaskOne = 0;
	int resultTaskTwo = 0;
	int row = 0;
	std::string s;
	int distances[1000][12];
	while (infile >> s) {
		for (int i = 0; i < s.length(); i++)
		{
			distances[row][i] = (int)s[i] - 48;
		}
		row += 1;
	}

	std::cout << "Part one: " << resultPartOne(distances) << "\n"; //2595824
	std::cout << "Part two: " << resultPartTwo(distances); //2135254
}
