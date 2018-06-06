#include "CMDParser.h"
#include <sstream>
#include <iomanip>

CMDParser::CMDParser(int argc, char * argv[], const std::vector<std::string> &keys)
{
    error_code = 0;
	for (int i = 0; i < keys.size(); ++i)
	{
		std::vector<std::string> splited;
		int splitNum = stringSpliter(keys[i], splited);

		cmdInfo[splited[0]] = splited[2];

		// Get argument
		std::stringstream ssarg(splited[0]);
		// Get keyWord
		std::stringstream sskey(splited[1]);
		std::string key;
		sskey >> key;
		std::string args;
		while (ssarg >> args)
		{
			cmdKey[args] = key;
		}
	}

	appPath = argv[0];
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (cmdKey.find(arg) == cmdKey.end())
		{
			error_code = 1;
			break;
		}

		if (cmdKey[arg][0] == '@')
		{
			i++;
			if (i < argc)
			{
				keyVal[cmdKey[arg].substr(1, cmdKey[arg].size()-1)] = argv[i];
			}
		}
		else
		{
			keyVal[cmdKey[arg]] = "";
		}
	}
}

CMDParser::CMDParser()
{
}


CMDParser::~CMDParser()
{
}

std::string CMDParser::about()
{
	std::ostringstream oss;
	oss << "Application Help Info For " << appPath << std::endl;
	oss << std::left << std::setw(15) << "argument" << "Info" << std::endl;
	for(auto c: cmdInfo)
		oss << std::left << std::setw(15) << c.first << c.second << std::endl;
	return oss.str();
}

std::string CMDParser::operator[](const std::string & key)
{
	return keyVal[key];
}

bool CMDParser::has(const std::string &s)
{
	return keyVal.find(s) != keyVal.end();
}

int CMDParser::error()
{
	return error_code;
}

