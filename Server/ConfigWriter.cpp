#include <json\json.h>
#include <fstream>
#include <iostream>

class ConfigWriter {
private:
	Json::Value writeConfigFile()
	{
		// open JSON file
		std::ifstream configFile("config.json");
		if (!configFile.is_open()) {
			std::cerr << "Error: could not open config file." << std::endl;
			return -1;
		}

		Json::Value root;
		configFile >> root;

		return root;
	}
public:
	int writeServerPort() {
		Json::Value config = writeConfigFile();

		if (config["port"].isNull()) {
			std::cerr << "Error: port number is missing in the config file." << std::endl;
			return -1;
		}

		// extract and return server port
		int serverPort = config["port"].asInt();
		return serverPort;
	}
};