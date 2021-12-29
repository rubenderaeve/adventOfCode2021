#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>

auto xMinTarget = 0, xMaxTarget = 0, yMinTarget = 0, yMaxTarget = 0;

// If target is hit, returns the maximum height reached. If not hit, returns -1.
auto TestVelocities(int xv, int yv)
{
	auto x = 0, y = 0, maxHeight = 0;

	while (y >= yMinTarget)
	{
		maxHeight = std::max(maxHeight, y);

		x += xv, y += yv;

		if (x >= xMinTarget && x <= xMaxTarget && y >= yMinTarget && y <= yMaxTarget)
			return maxHeight;

		if (xv > 0)
			xv--;
		else if (xv < 0)
			xv++;

		yv--;
	}

	return -1;
}

auto ProcessInput(const std::string& filename)
{
	std::ifstream file("input.txt");
	std::string target, areaColon;
	auto x = 'x', y = 'y', equals = '=', dot = '.', comma = ',';

	file >> target >> areaColon >> x >> equals >> xMinTarget >> dot >> dot >>
		xMaxTarget >> comma >> y >> equals >> yMinTarget >> dot >> dot >> yMaxTarget;

	auto hits = 0, maxHeight = 0;
	auto xvStart = std::min(1, xMinTarget), xvEnd = std::max(-1, xMaxTarget);

	for (auto xv = xvStart; xv <= xvEnd; xv++)
	{
		for (auto yv = yMinTarget; yv <= -yMinTarget; yv++)
		{
			auto height = TestVelocities(xv, yv);
			if (height > -1)
			{
				maxHeight = std::max(maxHeight, height);
				hits++;
			}
		}
	}

	return std::make_pair(maxHeight, hits);
}

int main()
{
	auto result = ProcessInput("input.txt");

	std::cout << "Part 1: " << result.first << std::endl;
	std::cout << "Part 2: " << result.second << std::endl;
}