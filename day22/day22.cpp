#include <iostream>
#include <fstream>
#include <tuple>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>

struct InputStep
{
	bool on;
	std::pair<int, int> x, y, z;
};

std::vector<InputStep> steps;

void readInput(const std::string& filename)
{
	std::ifstream file(filename);
	std::string onOff;
	auto x = 'x', y = 'y', z = 'z', equals = '=', dot = '.', comma = ',';

	InputStep step;
	while (file >> onOff >> x >> equals >> step.x.first >> dot >> dot >> step.x.second >> comma >>
		y >> equals >> step.y.first >> dot >> dot >> step.y.second >> comma >>
		z >> equals >> step.z.first >> dot >> dot >> step.z.second)
	{
		step.on = onOff == "on";
		steps.push_back(step);
	}
}

auto DoPartOne(void)
{
	std::set<std::tuple<int, int, int>> grid;
	for (auto& step : steps)
		if (std::abs(step.x.first) <= 50 && std::abs(step.y.first) <= 50 && std::abs(step.z.first) <= 50)
			for (auto x = step.x.first; x <= step.x.second; x++)
				for (auto y = step.y.first; y <= step.y.second; y++)
					for (auto z = step.z.first; z <= step.z.second; z++)
						if (step.on)
							grid.insert(std::make_tuple(x, y, z));
						else
							grid.erase(std::make_tuple(x, y, z));

	return grid.size();
}

auto DoPartTwo()
{
	// Find all the "seams" for each axis (x, y, z boundaries where on/off could possibly change).
	std::vector<int> xSeam, ySeam, zSeam;
	for (auto& step : steps)
	{
		xSeam.push_back(step.x.first); xSeam.push_back(step.x.second + 1);
		ySeam.push_back(step.y.first); ySeam.push_back(step.y.second + 1);
		zSeam.push_back(step.z.first); zSeam.push_back(step.z.second + 1);
	}

	// Sort the seams for each axis
	sort(xSeam.begin(), xSeam.end());
	sort(ySeam.begin(), ySeam.end());
	sort(zSeam.begin(), zSeam.end());

	// Use the seams to partition 3D space, where each point in the partition has same on/off.
	// Create this 3D vector, sized at runtime, to hold on/off for all the partitions.
	std::vector<std::vector<std::vector<bool>>> partitions(
		xSeam.size(),
		std::vector<
		std::vector<bool>>(
			ySeam.size(),
			std::vector<bool>(
				zSeam.size())));

	// Play back the input steps to determine the on/off for each partition - multiple
	// adjacent partitions may be affected at each step.
	for (auto& step : steps)
	{
		auto xMin = lower_bound(xSeam.begin(), xSeam.end(), step.x.first) - xSeam.begin();
		auto xMax = lower_bound(xSeam.begin(), xSeam.end(), step.x.second + 1) - xSeam.begin();

		auto yMin = lower_bound(ySeam.begin(), ySeam.end(), step.y.first) - ySeam.begin();
		auto yMax = lower_bound(ySeam.begin(), ySeam.end(), step.y.second + 1) - ySeam.begin();

		auto zMin = lower_bound(zSeam.begin(), zSeam.end(), step.z.first) - zSeam.begin();
		auto zMax = lower_bound(zSeam.begin(), zSeam.end(), step.z.second + 1) - zSeam.begin();

		for (auto i = xMin; i < xMax; i++)
			for (auto j = yMin; j < yMax; j++)
				for (auto k = zMin; k < zMax; k++)
					partitions[i][j][k] = step.on;
	}

	// For all partitions that are "on", sum the volume of points they contain.
	auto retval = 0LL;
	for (auto i = 0; i < xSeam.size() - 1; i++)
		for (auto j = 0; j < ySeam.size() - 1; j++)
			for (auto k = 0; k < zSeam.size() - 1; k++)
				if (partitions[i][j][k])
					retval += (long long)(xSeam[i + 1] - xSeam[i]) * (ySeam[j + 1] - ySeam[j]) * (zSeam[k + 1] - zSeam[k]);

	return retval;
}

int main()
{
	readInput("input.txt");

	auto part1 = DoPartOne();
	std::cout << "Part 1: " << part1 << std::endl;

	auto part2 = DoPartTwo();
	std::cout << "Part 2: " << part2 << std::endl;

	assert(part1 == 652209);
	assert(part2 == 1217808640648260);
	return 0;
}