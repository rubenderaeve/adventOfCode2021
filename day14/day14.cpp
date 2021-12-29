#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
#include <cassert>



auto diffMaxMin(std::map<std::pair<char, char>, long long>& pairCounts, const std::string& polyTemp)
{
	std::map<char, long long> letter_counts_x2;

	for (auto& pc : pairCounts)
	{
		letter_counts_x2[pc.first.first] += pc.second;
		letter_counts_x2[pc.first.second] += pc.second;
	}

	// every letter got counted twice except front/back - add these again before halving
	letter_counts_x2[polyTemp.front()]++;
	letter_counts_x2[polyTemp.back()]++;

	auto max = LLONG_MIN, min = LLONG_MAX;
	for (auto& lc_x2 : letter_counts_x2)
	{
		if (lc_x2.second > max) max = lc_x2.second;
		if (lc_x2.second < min) min = lc_x2.second;
	}

	return (max - min) / 2;
}


auto PartOneTwo(std::vector<std::pair<std::pair<char, char>, char>>& insertionRules, std::string& polyTemp) {
	std::map<std::pair<char, char>, long long> pairCounts;
	for (auto i = 0; i < polyTemp.length() - 1; i++)
		pairCounts[std::make_pair(polyTemp[i], polyTemp[i + 1])]++;

	long long resOne;
	for (auto i = 0; i < 40; i++) {

		std::map<std::pair<char, char>, long long> pairs_added_in_this_step;

		for (auto& rule : insertionRules)
		{
			auto from = rule.first;
			auto count_iter = pairCounts.find(from);

			if (count_iter != pairCounts.end())
			{
				auto left = from.first, right = from.second, center = rule.second;
				pairs_added_in_this_step[std::make_pair(left, center)] += count_iter->second;
				pairs_added_in_this_step[std::make_pair(center, right)] += count_iter->second;
				pairCounts.erase(count_iter);
			}
		}

		for (auto& added_pair : pairs_added_in_this_step)
			pairCounts[added_pair.first] += added_pair.second;

		if (i == 9) {
			resOne = diffMaxMin(pairCounts, polyTemp);
		}
	}

	return std::make_pair(resOne, diffMaxMin(pairCounts, polyTemp));
}



auto ReadInput(const std::string& fileName) {
	std::ifstream file(fileName);
	int i = 0;
	std::string line;
	std::vector<std::pair<std::pair<char, char>, char>> insertionRules;
	std::string polyTemp;
	while (std::getline(file, line)) {
		if (i == 0) {
			polyTemp = line;
			i++;
			continue;
		}
		size_t pos = 0;
		std::string delimiter = " -> ";
		pos = line.find(delimiter);
		if (pos != std::string::npos) {
			std::string token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			insertionRules.push_back(std::make_pair(std::make_pair(token[0], token[1]), line[0]));
		}
	}
	return std::make_pair(insertionRules, polyTemp);
}


int main()
{
	auto input = ReadInput("input.txt");
	auto result = PartOneTwo(input.first, input.second);

	std::cout << "Part 1: " << result.first << std::endl;
	std::cout << "Part 2: " << result.second << std::endl;

}
