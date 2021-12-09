#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>

int main()
{
	std::cout << "Day8\n";
	std::string line;
	std::ifstream file("input.txt");
	int resPartOne = 0;
	int resPartTwo = 0;
	std::map<std::vector<int>, int> freqToN;
	freqToN[std::vector<int>{ 4, 6, 7, 8, 8, 9}] = 0;
	freqToN[std::vector<int>{8, 9 }] = 1;
	freqToN[std::vector<int>{4, 7, 7, 8, 8 }] = 2;
	freqToN[std::vector<int>{7, 7, 8, 8, 9 }] = 3;
	freqToN[std::vector<int>{6, 7, 8, 9 }] = 4;
	freqToN[std::vector<int>{6, 7, 7, 8, 9 }] = 5;
	freqToN[std::vector<int>{4, 6, 7, 7, 8, 9 }] = 6;
	freqToN[std::vector<int>{8, 8, 9 }] = 7;
	freqToN[std::vector<int>{4, 6, 7, 7, 8, 8, 9 }] = 8;
	freqToN[std::vector<int>{6, 7, 7, 8, 8, 9 }] = 9;

	while (std::getline(file, line)) {
		std::string delimiter = " | ";
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			std::stringstream inputStr(token);
			std::string input;
			std::map<char, int> charToF;
			while (std::getline(inputStr, input, ' ')) {
				for (auto& ch : input) {
					charToF[ch] = charToF.count(ch) ? charToF[ch] + 1 : 1;
				}
			}

			line.erase(0, pos + delimiter.length());
			std::stringstream lineStr(line);
			std::string tmp;
			int pow = 3;
			int number = 0;
			while (std::getline(lineStr, tmp, ' ')) {
				if (tmp.length() == 2 || tmp.length() == 3 || tmp.length() == 4 || tmp.length() == 7) {
					resPartOne++;
				}
				std::vector<int> digit;
				for (auto& ch : tmp) {
					digit.push_back(charToF[ch]);
				}
				std::sort(digit.begin(), digit.end());
				number += freqToN[digit] * std::pow(10, pow);
				pow--;
			}
			resPartTwo += number;
		}
	}
	std::cout << "partone: " << resPartOne << std::endl;
	std::cout << "partwo: " << resPartTwo;
}


