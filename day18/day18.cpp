#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Token
{
	bool isNum; // true means n is a number
	int n; // can be '[' or ']' or ',' or a number
};

inline bool operator==(const Token& lhs, const Token& rhs)
{
	return lhs.isNum == rhs.isNum && lhs.n == rhs.n;
}

const Token openBracket{ false, '[' }, comma{ false, ',' }, closeBracket{ false, ']' };

struct Snailfish : std::vector<Token>
{
	Snailfish& operator+=(const Snailfish& rhs)
	{
		insert(begin(), openBracket);
		push_back(comma);

		for (auto& n : rhs)
			push_back(n);

		push_back(closeBracket);
		reduce();
		return *this;
	}

	auto getMagnitude()
	{
		while (size() > 4)
		{
			iterator it = findRegularPair();
			if (it == end())
				break;

			// Collapse pair
			auto n1 = (it + 1)->n, n2 = (it + 3)->n;

			it = erase(it, it + 4);
			it->isNum = true;
			it->n = 3 * n1 + 2 * n2;
		}

		return (*this)[0].n;
	}

private:
	iterator findRegularPair()
	{
		if (size() > 4)
			for (auto it = begin(); it + 4 != end(); it++)
				if (*it == openBracket && (it + 1)->isNum && *(it + 2) == comma && (it + 3)->isNum && *(it + 4) == closeBracket)
					return it;

		return end();
	}

	auto findRegularPairInsideFourBracketPairs()
	{
		auto bracketCount = 0;
		for (auto it = begin(); it != end(); it++)
		{
			if (*it == openBracket)
			{
				if (++bracketCount <= 4)
					continue;

				if ((it + 1)->isNum && *(it + 2) == comma && (it + 3)->isNum && *(it + 4) == closeBracket)
					return it;
			}
			else if (*it == closeBracket)
				--bracketCount;
		}

		return end();
	}

	void tryAddToPreviousNum(iterator it, int n)
	{
		for (; it != begin(); --it)
			if (it->isNum)
			{
				it->n += n;
				break;
			}
	}

	void tryAddToNextNum(iterator it, int n)
	{
		for (; it != end(); it++)
			if (it->isNum)
			{
				it->n += n;
				break;
			}
	}

	auto tryExplode()
	{
		auto it = findRegularPairInsideFourBracketPairs();
		if (it == end()) return false;

		tryAddToPreviousNum(it, (it + 1)->n);
		tryAddToNextNum(it + 5, (it + 3)->n);

		// Erase regular pair and leave last bracket for replace
		it = erase(it, it + 4);
		*it = { true, 0 };
		return true;
	}

	auto trySplit()
	{
		for (auto it = begin(); it != end(); ++it)
			if (it->isNum && it->n > 9)
			{
				auto n = it->n;
				it = erase(it);
				insert(it, { openBracket, {true, n / 2}, comma, {true, n / 2 + n % 2}, closeBracket });
				return true;
			}

		return false;
	}

	void reduce()
	{
		while (tryExplode() || trySplit());
	}
};

std::stringstream& operator>>(std::stringstream& i, Snailfish& sf)
{
	auto c = ' ';

	while (i >> c)
	{
		if (isdigit(c))
			sf.push_back(Token{ true, c - '0' });
		else
			sf.push_back(Token{ false, c });
	}

	return i;
}

auto readInput(const std::string& filename)
{
	std::ifstream file(filename);
	std::vector<Snailfish> sfs;

	std::string s;
	while (file >> s)
	{
		std::stringstream ss(s);
		Snailfish sf;

		ss >> sf;
		sfs.push_back(sf);
	}

	return sfs;
}

auto doPart1(const std::vector<Snailfish>& sfs)
{
	Snailfish total;
	for (auto sf : sfs)
		if (total.empty())
			std::swap(total, sf);
		else
			total += sf;

	return total.getMagnitude();
}

auto doPart2(std::vector<Snailfish>& sfs)
{
	auto retval = 0;
	for (auto i = 0; i < sfs.size(); i++)
		for (auto j = 0; j < sfs.size(); j++)
			if (i != j)
				retval = std::max(retval, doPart1({ sfs[i], sfs[j] }));

	return retval;
}

int main()
{
	auto sfs = readInput("input.txt");

	auto part1 = doPart1(sfs);
	std::cout << "Part 1: " << part1 << std::endl;
	assert(part1 == 4469);

	auto part2 = doPart2(sfs);
	std::cout << "Part 2: " << part2 << std::endl;
	assert(part2 == 4770);

	return 0;
}