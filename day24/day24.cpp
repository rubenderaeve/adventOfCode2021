#include <iostream>
#include <sstream>

auto PartOne()
{
	for (auto w1 = 9; w1 > 0; w1--)
	{
		for (auto w2 = 9; w2 > 0; w2--)
		{
			for (auto w3 = 9; w3 > 0; w3--)
			{
				auto w4 = w3 - 7;
				if (w4 < 1 || w4 > 9) continue;

				for (auto w5 = 9; w5 > 0; w5--)
				{
					auto w6 = w5 + 1;
					if (w6 < 1 || w6 > 9) continue;

					for (auto w7 = 9; w7 > 0; w7--)
					{
						for (auto w8 = 9; w8 > 0; w8--)
						{
							auto w9 = w8 + 5;
							if (w9 < 1 || w9 > 9) continue;

							for (auto w10 = 9; w10 > 0; w10--)
							{
								auto w11 = w10;
								if (w11 < 1 || w11 > 9) continue;

								auto w12 = w7 + 8;
								if (w12 < 1 || w12 > 9) continue;

								auto w13 = w2 + 7;
								if (w13 < 1 || w13 > 9) continue;

								auto w14 = w1 - 8;
								if (w14 < 1 || w14 > 9) continue;

								std::stringstream ss;
								ss << w1 << w2 << w3 << w4 << w5 << w6 << w7 << w8 << w9 << w10 << w11 << w12 << w13 << w14;
								return ss.str();
							}
						}
					}
				}
			}
		}
	}
	return std::string();
}

auto PartTwo()
{
	for (auto w1 = 1; w1 <= 9; w1++)
	{
		for (auto w2 = 1; w2 <= 9; w2++)
		{
			for (auto w3 = 1; w3 <= 9; w3++)
			{
				auto w4 = w3 - 7;
				if (w4 < 1 || w4 > 9) continue;

				for (auto w5 = 1; w5 <= 9; w5++)
				{
					auto w6 = w5 + 1;
					if (w6 < 1 || w6 > 9) continue;

					for (auto w7 = 1; w7 <= 9; w7++)
					{
						for (auto w8 = 1; w8 <= 9; w8++)
						{
							auto w9 = w8 + 5;
							if (w9 < 1 || w9 > 9) continue;

							for (auto w10 = 1; w10 <= 9; w10++)
							{
								auto w11 = w10;
								if (w11 < 1 || w11 > 9) continue;

								auto w12 = w7 + 8;
								if (w12 < 1 || w12 > 9) continue;

								auto w13 = w2 + 7;
								if (w13 < 1 || w13 > 9) continue;

								auto w14 = w1 - 8;
								if (w14 < 1 || w14 > 9) continue;

								std::stringstream ss;
								ss << w1 << w2 << w3 << w4 << w5 << w6 << w7 << w8 << w9 << w10 << w11 << w12 << w13 << w14;
								return ss.str();
							}
						}
					}
				}
			}
		}
	}
	return std::string();
}

int main()
{
	std::cout << "Part one: " << PartOne() << std::endl;
	std::cout << "Part two: " << PartTwo() << std::endl;
}