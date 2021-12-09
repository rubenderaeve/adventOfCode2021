#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

int partone(std::vector<std::vector<int>> hM) {
	int cm = hM[0].size() - 1;
	int rm = hM.size() - 1;
	std::vector<int>lowPoints;
	int sum = 0;
	for (int i = 0; i < hM.size(); i++) {
		for (int j = 0; j < hM[0].size(); j++) {
			if (hM[i][j] < hM[i][std::min(j + 1, cm)] || j == cm) {
				if (hM[i][j] < hM[std::min(i + 1, rm)][j] || i == rm) {
					if (hM[i][j] < hM[i][std::max(j - 1, 0)] || j == 0) {
						if (hM[i][j] < hM[std::max(i - 1, 0)][j] || i == 0) {
							lowPoints.push_back(hM[i][j]);
							sum += hM[i][j] + 1;
						}
					}
				}
			}
		}
	}
	return sum;
}

std::set<std::vector<int>> checkAround(std::vector<std::vector<int>> hM, int i, int j, std::set<std::vector<int>> area) {
	int cm = hM[0].size() - 1;
	int rm = hM.size() - 1;
	if (hM[i][j] < 9 && area.count(std::vector<int>{i, j}) == 0) {
		area.insert(std::vector<int>{i, j});
		if (i != 0) {
			if (hM[i - 1][j] < 9 && area.count(std::vector<int>{i - 1, j}) == 0) {
				auto areaLeft = checkAround(hM, i - 1, j, area);
				area.insert(areaLeft.begin(), areaLeft.end());
			}
		}
		if (i != rm) {
			if (hM[i + 1][j] < 9 && area.count(std::vector<int>{i + 1, j}) == 0) {
				auto areaRight = checkAround(hM, i + 1, j, area);
				area.insert(areaRight.begin(), areaRight.end());
			}
		}
		if (j != 0) {
			if (hM[i][j - 1] < 9 && area.count(std::vector<int>{i, j - 1}) == 0) {
				auto areaUp = checkAround(hM, i, j - 1, area);
				area.insert(areaUp.begin(), areaUp.end());
			}
		}
		if (j != cm) {
			if (hM[i][j + 1] < 9 && area.count(std::vector<int>{i, j + 1}) == 0) {
				auto areaDown = checkAround(hM, i, j + 1, area);
				area.insert(areaDown.begin(), areaDown.end());
			}
		}
	}
	return area;
}


int partTwo(std::vector<std::vector<int>> hM) {
	std::set<std::vector<int>>cF;
	std::set<std::vector<int>> area;
	std::vector<int> sizes;
	int cm = hM[0].size() - 1;
	int rm = hM.size() - 1;
	std::vector<int>basins;
	for (int i = 0; i < hM.size(); i++) {
		for (int j = 0; j < hM[0].size(); j++) {
			if (cF.count(std::vector<int>{i, j}) == 0 && hM[i][j]!=9) {
				std::set<std::vector<int>> checked = checkAround(hM, i, j, area);
				sizes.push_back(checked.size());
				cF.insert(checked.begin(), checked.end());
			}
		}
	}
	std::sort(sizes.begin(), sizes.end(), std::greater<int>());
	int sum = 1;
	for (size_t i = 0; i < 3; i++)
	{
		sum = sum * sizes[i];
	}
	return sum;
}

int main()
{
	std::cout << "Day8\n";
	std::string line;
	std::ifstream file("input.txt");
	std::vector<std::vector<int>> hM;
	while (std::getline(file, line)) {
		std::vector<int>digit;
		for (auto& ch : line) {
			digit.push_back((int)ch - 48);
		}
		hM.push_back(digit);
	}
	std::cout << "partOne: " << partone(hM) << std::endl;
	std::cout << "partTwo: " << partTwo(hM) << std::endl;
}

