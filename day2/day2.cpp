#include <iostream>
#include <fstream>

int main()
{
	std::ifstream infile;
	infile.open("./inputDayTwo.txt");
	int value;
	int resultTaskOne = 0;
	int resultTaskTwo = 0;
	int depth = 0;
	int depthTwo = 0;
	int hor = 0;
	std::string direction;
	while (infile >> direction >> value) {
		if (direction == "forward") {
			hor += value;
			depthTwo += (depth * value);
		}
		else if (direction == "down") {
			depth += value;
		}
		else if (direction == "up") {
			depth -= value;
		}
		resultTaskOne = hor * depth;
		resultTaskTwo = hor * depthTwo;
	}

	std::cout << "Part one: " << resultTaskOne << "\n";
	std::cout << "Part two: " << resultTaskTwo;
}

