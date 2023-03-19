#include <json\json.h>
#include <fstream>
#include <iostream>
class UserReader {
private:
	Json::Value ReadUsersFile()
	{
		// open JSON file
		std::ifstream usersFile("users.json");
		if (!usersFile.is_open()) {
			std::cerr << "Error: could not open users file." << std::endl;
			return -1;
		}

		Json::Value root;
		usersFile >> root;

		return root;
	}
public:
	int ReadUsersInfo() {
		Json::Value users = ReadUsersFile();

		if (users["users"].isNull()) {
			std::cerr << "Error: user or password is missing in the users file." << std::endl;
			return -1;
		}

		// extract and return user
		std::string user = users["users"]["user"].asString();
		std::cout << user;
		return 1;
	}
};