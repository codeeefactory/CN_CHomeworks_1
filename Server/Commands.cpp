#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

class Commands {
private:

public:
	int setTime() {
		// read command from user
		std::string command;
		std::cout << "Command: ";
		std::getline(std::cin, command);

		// parse command
		std::regex commandRegex("^setTime\\s+(\\d{2}-\\d{2}-\\d{4})$");
		std::smatch match;
		if (!std::regex_match(command, match, commandRegex)) {
			std::cerr << "Error: invalid command format." << std::endl;
			return -1;
		}

		// extract argument
		std::string argument = match[1].str();

		// validate argument as date
		std::regex dateRegex("^\\d{2}-\\d{2}-\\d{4}$");
		if (!std::regex_match(argument, dateRegex)) {
			std::cerr << "Error: invalid date format." << std::endl;
			return -1;
		}

		std::cerr << argument << std::endl;
		return 0;
	}
};