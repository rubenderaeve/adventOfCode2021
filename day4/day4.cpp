#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

int findResultPartOne(std::vector<int> drawNumbers, std::map<int, std::vector<std::set<int>>> boards) {
	std::vector<int> numbersToDelete;
	bool bingo = false;
	int bingoNumber;

	for (auto number : drawNumbers) {
		numbersToDelete.push_back(number);
		for (auto board : boards) {
			for (auto setIt : board.second) {
				for (auto num : numbersToDelete) {
					setIt.erase(num);
					if (setIt.size() == 0) {
						bingo = true;
						bingoNumber = num;
					}
				}
			}
			if (bingo) {
				int sum = 0;
				std::set<int> bingoSet = board.second.back();
				for (auto num : numbersToDelete) {
					bingoSet.erase(num);
				}
				for (auto numIt : bingoSet) {

					sum += numIt;
				}
				return bingoNumber * sum;
			}
		}
	}
}

int findResultPartTwo(std::vector<int> drawNumbers, std::map<int, std::vector<std::set<int>>> boards) {
	std::vector<int> numbersToDelete;
	bool bingo = false;
	int bingoNumber;
	int numberOfBoards = boards.size();
	std::set<int> boardIgnore;

	for (auto number : drawNumbers) {
		numbersToDelete.push_back(number);
		for (auto board : boards) {
			if (boardIgnore.count(board.first) == 0) {
				for (auto setIt : board.second) {
					for (auto num : numbersToDelete) {
						setIt.erase(num);
						if (setIt.size() == 0) {
							bingo = true;
							bingoNumber = num;
							boardIgnore.insert(board.first);
							break;
						}
					}
				}
			}
			if (bingo) {
				if (boardIgnore.size() == boards.size()) {
					int sum = 0;
					std::set<int> bingoSet = board.second.back();
					for (auto num : numbersToDelete) {
						bingoSet.erase(num);
					}
					for (auto numIt : bingoSet) {

						sum += numIt;
					}
					return bingoNumber * sum;
				}
				else {
					bingo = false;
				}

			}
		}
	}
}

int main() {
	std::cout << "Day 4\n";
	std::string line;
	std::ifstream file("input.txt");
	std::vector<int> drawNumbers;
	std::map<int, std::vector<std::set<int>>> boards;
	int n = 5;
	int matrixTemp[5][5];
	std::vector<std::set<int>> vectorTemp;
	std::set<int> setRowTemp;
	std::set<int> setColTemp;
	std::set<int> allNumbersOfBoard;
	int r = 0;
	int c = 0;
	int boardID = 0;
	bool firstLinePassed = false;

	// Reading input and storing boards in a vector of columns and row sets.
	while (std::getline(file, line)) {
		std::stringstream lineStr(line);
		std::string tmp;
		if (!firstLinePassed) {
			while (std::getline(lineStr, tmp, ',')) {
				drawNumbers.push_back(stoi(tmp));
			}
		}
		if (line != "" and line != "end") {
			if (firstLinePassed) {
				c = 0;
				while (std::getline(lineStr, tmp, ' ')) {
					if (tmp != "") {
						matrixTemp[r][c] = stoi(tmp);
						c++;
					}
				}
				r++;
			}
		}
		firstLinePassed = true;
		if (line == "" || line == "end") {
			if (boardID > 0) {
				for (size_t i = 0; i < n; i++)
				{
					for (size_t j = 0; j < n; j++)
					{
						setRowTemp.insert(matrixTemp[i][j]);
						setColTemp.insert(matrixTemp[j][i]);
						allNumbersOfBoard.insert(matrixTemp[i][j]);
					}
					vectorTemp.push_back(setRowTemp);
					vectorTemp.push_back(setColTemp);
					setRowTemp.clear();
					setColTemp.clear();
				}
				vectorTemp.push_back(allNumbersOfBoard);
				boards[boardID] = vectorTemp;
				allNumbersOfBoard.clear();
				vectorTemp.clear();
			}
			boardID += 1;
			r = 0;
		}

	}
	std::cout << "PartOne: " << findResultPartOne(drawNumbers, boards) << std::endl;
	std::cout << "PartTwo: " << findResultPartTwo(drawNumbers, boards);
}
