#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include "ClientCommands.h"
using namespace std;
class ClientCommands {
private:

public:
	int commandreader(string command) {
		vector<string> cmds;

		cmds.push_back("^ signin\s+\w+\s+\w+$");
		cmds.push_back("^signup\\s+\w+");
		cmds.push_back("1");
		cmds.push_back("2");
		cmds.push_back("3");
		cmds.push_back("4");
		cmds.push_back("5");
		cmds.push_back("6");
		cmds.push_back("7");
		cmds.push_back("8");
		cmds.push_back("9");
		cmds.push_back("0");

		std::regex commandRegex("signin\\s+\\w+\\s+\\w+");
		std::smatch match;
		if (!std::regex_match(command, match, commandRegex)) {
			std::cerr << "Error: invalid command format." << std::endl;
			return -1;
		}

		string argument2 = match[2].str();
		string argument1 = match[1].str();

		return 0;
	}
};