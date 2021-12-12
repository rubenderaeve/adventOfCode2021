#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

int partOneOrTwo = 1;

std::unordered_map<std::string, std::set<std::string>> edges;
std::stack<std::unordered_map<std::string, int>> paths;
int finishedPaths = 0;

void followEdge(std::set<std::string> subPoints, bool pointAlreadyInPath) {
	auto path = paths.top();
	for (auto& point : subPoints) {
		if (!path.empty() && pointAlreadyInPath && path.find(point) != path.end()) continue;
		paths.push(path);
		if (point != "end") {
			if (!isupper(point[0])) {
				++paths.top()[point];
				followEdge(edges[point], pointAlreadyInPath ? true : paths.top()[point] == partOneOrTwo);
			}
			else followEdge(edges[point], pointAlreadyInPath);
		}
		else finishedPaths++;
		paths.pop();
	}
}

void ReadInput(std::string fileName) {
	std::ifstream file(fileName);
	std::string edge;
	while (std::getline(file, edge)) {
		std::stringstream edgestr(edge);
		std::string pos;
		std::vector<std::string> posOneTwo;
		while (std::getline(edgestr, pos, '-')) { posOneTwo.push_back(pos); }
		if (posOneTwo[1] != "start" && posOneTwo[0] != "end")
			edges[posOneTwo[0]].insert(posOneTwo[1]);
		if (posOneTwo[0] != "start" && posOneTwo[1] != "end")
			edges[posOneTwo[1]].insert(posOneTwo[0]);
	}
}

int main() {
	ReadInput("input.txt");
	paths.push(std::unordered_map<std::string, int>());
	followEdge(edges["start"], false);
	std::cout << "paths: " << finishedPaths;
}
