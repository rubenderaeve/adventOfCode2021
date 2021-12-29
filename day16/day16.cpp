#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

auto HexToBin(char c)
{
	const static std::string binary[] =
	{
		"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
		"1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
	};

	return binary[std::string("0123456789ABCDEF").find(c)];
}

auto ReadNumericField(std::stringstream& ss, int length)
{
	std::string temp;
	while (length--)
	{
		char c;
		if (!(ss >> c))
			return -1;
		temp.push_back(c);
	}

	return stoi(temp, nullptr, 2);
}

auto ReadCharsIntoString(std::stringstream& ss, int length)
{
	std::string retval;
	char c;

	while (length--)
	{
		ss >> c;
		retval.push_back(c);
	}

	return retval;
}

struct Packet
{
	enum PacketType { Sum, Product, Minimum, Maximum, Literal, GreaterThan, LessThan, EqualTo };
	int version;
	PacketType type;
	long long literal; // only applies if packet type is Literal
	std::vector<Packet*> children;

	int GetVersionSum()
	{
		auto sum = version;
		for (auto c : children)
			sum += c->GetVersionSum();
		return sum;
	}

	long long evaluate()
	{
		auto sum = 0LL, product = 1LL, minimum = LLONG_MAX, maximum = LLONG_MIN;

		switch (type)
		{
		case Sum:
			for (auto c : children)
				sum += c->evaluate();
			return sum;

		case Product:
			for (auto c : children)
				product *= c->evaluate();
			return product;

		case Minimum:
			for (auto c : children)
			{
				auto temp = c->evaluate();
				minimum = std::min(temp, minimum);
			}
			return minimum;

		case Maximum:
			for (auto c : children)
			{
				auto temp = c->evaluate();
				maximum = std::max(temp, maximum);
			}
			return maximum;

		case Literal:
			return literal;

		case GreaterThan:
			return children[0]->evaluate() > children[1]->evaluate() ? 1 : 0;

		case LessThan:
			return children[0]->evaluate() < children[1]->evaluate() ? 1 : 0;

		case EqualTo:
			return children[0]->evaluate() == children[1]->evaluate() ? 1 : 0;

		default:
			return -1;
		}
	}
};

std::vector<Packet*> ReadPackets(std::stringstream& ss, bool readToEnd = false)
{
	std::vector<Packet*> retval;

	for (;;)
	{
		auto version = ReadNumericField(ss, 3);
		if (version == -1)
			break;

		Packet* p = new Packet();
		p->version = version;
		p->type = Packet::PacketType(ReadNumericField(ss, 3));

		if (p->type == Packet::Literal)
		{
			auto flag = '1';
			p->literal = 0;

			while (flag == '1')
			{
				ss >> flag;
				auto fourBits = ReadNumericField(ss, 4);
				p->literal = (p->literal << 4) + fourBits;
			}
		}
		else
		{
			char lenTypeId;
			ss >> lenTypeId;

			if (lenTypeId == '0')
			{
				auto subPacketsLength = ReadNumericField(ss, 15);
				auto subpackets = ReadCharsIntoString(ss, subPacketsLength);

				std::stringstream subss(subpackets);
				p->children = ReadPackets(subss, true);
			}
			else
			{
				auto numSubPackets = ReadNumericField(ss, 11);
				for (int i = 0; i < numSubPackets; i++)
					p->children.push_back(ReadPackets(ss)[0]);
			}
		}

		retval.push_back(p);
		if (!readToEnd)
			break;
	}

	return retval;
}

auto ProcessInput(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;
	file >> line;

	std::string binary;
	for (auto c : line)
		binary += HexToBin(c);

	std::stringstream ss(binary);

	Packet* p = ReadPackets(ss, false)[0];
	return std::make_pair(p->GetVersionSum(), p->evaluate());
}

int main()
{
	auto result = ProcessInput("input.txt");

	std::cout << "Part 1: " << result.first << std::endl;
	std::cout << "Part 2: " << result.second << std::endl;
}