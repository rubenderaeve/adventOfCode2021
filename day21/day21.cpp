#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <cassert>

struct PlayerState
{
	int pos, score;
};

auto ReadInput(const std::string& filename)
{
	std::ifstream file("input.txt");
	std::string player, n, starting, position;
	auto input = std::make_pair(0, 0);

	file >> player >> n >> starting >> position >> input.first;
	file >> player >> n >> starting >> position >> input.second;
	return input;
}

auto RollDie()
{
	static auto die = 0;

	if (++die > 100) die = 1;
	return die;
}

auto DoPartOne(std::pair<int, int>& pos)
{
	std::array<PlayerState, 2> psa{ PlayerState{pos.first, 0}, PlayerState{pos.second, 0} };
	auto rollCount = 0;

	for (auto curr = 0, other = 1; ; std::swap(curr, other))
	{
		auto total = RollDie() + RollDie() + RollDie();
		rollCount += 3;

		psa[curr].pos = (psa[curr].pos + total - 1) % 10 + 1;
		psa[curr].score += psa[curr].pos;

		if (psa[curr].score >= 1000)
			return psa[other].score * rollCount;
	}
}

long long wins[2];
int waysToRollValue[10];

void recur(std::array<PlayerState, 2> psa, int turn = 0, long long waysToReachThisState = 1)
{
	for (auto roll = 3; roll <= 9; roll++)
	{
		auto newPsa = psa;
		auto& ps = newPsa[turn];
		auto newWays = waysToReachThisState * waysToRollValue[roll];

		ps.pos += roll;
		if (ps.pos > 10)
			ps.pos -= 10;

		ps.score += ps.pos;

		if (ps.score >= 21)
			wins[turn] += newWays;
		else
			recur(newPsa, 1 - turn, newWays);
	}
}

auto DoPartTwo(std::pair<int, int>& pos)
{
	for (auto i = 1; i <= 3; i++)
		for (auto j = 1; j <= 3; j++)
			for (auto k = 1; k <= 3; k++)
				waysToRollValue[i + j + k]++;

	std::array<PlayerState, 2> psa{ PlayerState{pos.first, 0}, PlayerState{pos.second, 0} };
	recur(psa);
	return std::max(wins[0], wins[1]);
}

int main()
{
	auto positions = ReadInput("input.txt");

	auto part1 = DoPartOne(positions);
	std::cout << "Part 1: " << part1 << std::endl;

	auto part2 = DoPartTwo(positions);
	std::cout << "Part 2: " << part2 << std::endl;

	assert(part1 == 752247);
	assert(part2 == 221109915584112);
	return 0;
}