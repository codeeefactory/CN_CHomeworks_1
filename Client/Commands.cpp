#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;
class Commands {
private:

public:
	int commandreader(string command) {
		vector<string> cmds;
		
		cmds.push_back("^ signin\\s + (? = .{8, 20}$)(? ![_.])(? !.*[_.] {2})[a - zA - Z0 - 9._] + (? < ![_.])\\s + (? = .*[A - Za - z])(? = .*\d)(? = .*[@$!% *# ? &])[A - Za - z\d@$!% *# ? &]{8, }$");
		cmds.push_back("^ signup\\s + (? = .{8, 20}$)(? ![_.])(? !.*[_.] {2})[a - zA - Z0 - 9._] + (? < ![_.])");
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


		for (size_t i = 0; i <=1; i++)
		{

			std::regex commandRegex(cmds[i]);
			std::smatch match;
			if (!std::regex_match(command, match, commandRegex)) {
				std::cerr << "Error: invalid command format." << std::endl;
				return -1;
		}
		
		}

	}
};