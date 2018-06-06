#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <map>
#include <string>
#include <vector>

class CMDParser
{
public:
	CMDParser(int argc, char* argv[], const std::vector<std::string> &keys);
	CMDParser();
	~CMDParser();

	std::string about();

	std::string operator[](const std::string &key);

	bool has(const std::string &s);

	int error();
private:
	std::map<std::string, std::string> keyVal;
	std::map<std::string, std::string> cmdKey;
	std::map<std::string, std::string> cmdInfo;

	std::string appPath;

	int error_code;	// error = 0: No Error
					// error = 1: Cannot Parser

	std::string lastError;
};

inline int stringSpliter(const std::string &input, std::vector<std::string> &res)
{
	res.clear();
	int pos = 0;
	while (1)
	{
		int end = input.size() - 1;
		if (pos >= end)
		{
			break;
		}
		for (int i = pos; i < input.size(); ++i)
		{
			if (input[i] == '|')
			{
				end = i;
				break;
			}
		}

		if ((end - pos) > 0)
		{
			res.push_back(input.substr(pos, end - pos));
		}

		pos = end + 1;
	}
	return res.size();
}
#endif
