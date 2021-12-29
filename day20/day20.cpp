#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <cassert>

struct Image
{
	char defaultPixels;
	std::set<std::pair<int, int>> exceptions;
};

auto NewPixel(const Image& image, int row, int col, const std::string& algo)
{
	auto n = 0;
	for (auto i = -1; i <= 1; i++)
		for (auto j = -1; j <= 1; j++)
		{
			n <<= 1;
			if (image.exceptions.find(std::make_pair(row + i, col + j)) != image.exceptions.end())
				n |= 1;
		}

	return algo[(image.defaultPixels == '.') ? n : (n ^ 0x1ff)];
}

void DoStep(Image& image, std::string& algo)
{
	auto minRow = INT_MAX, maxRow = INT_MIN, minCol = INT_MAX, maxCol = INT_MIN;
	for (auto& i : image.exceptions)
	{
		minRow = std::min(minRow, i.first);
		maxRow = std::max(maxRow, i.first);
		minCol = std::min(minCol, i.second);
		maxCol = std::max(maxCol, i.second);
	}

	Image nextImage;
	auto index = (image.defaultPixels == '.') ? 0 : 511;
	nextImage.defaultPixels = (algo[index] == '.') ? '.' : '#';

	for (auto row = minRow - 2; row <= maxRow + 2; row++)
		for (auto col = minCol - 2; col <= maxCol + 2; col++)
			if (NewPixel(image, row, col, algo) != nextImage.defaultPixels)
				nextImage.exceptions.insert(std::make_pair(row, col));

	image = nextImage;
}

auto ProcessInput(const std::string& filename)
{
	Image inputImage{ '.' };
	std::ifstream file(filename);
	std::string algo, s;

	file >> algo;

	auto row = 0;
	while (file >> s)
	{
		for (auto col = 0; col < s.length(); col++)
			if (s[col] == '#')
				inputImage.exceptions.insert(std::make_pair(row, col));
		row++;
	}

	for (auto i = 0; i < 2; i++)
		DoStep(inputImage, algo);

	auto part1 = inputImage.exceptions.size();

	for (int i = 0; i < 48; i++)
		DoStep(inputImage, algo);

	return std::make_pair(part1, inputImage.exceptions.size());
}

int main()
{
	auto result = ProcessInput("input.txt");
	std::cout << "Part 1: " << result.first << std::endl;
	std::cout << "Part 2: " << result.second << std::endl;

	assert(result.first == 4928);
	assert(result.second == 16605);
	return 0;
}