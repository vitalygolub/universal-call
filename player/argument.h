#pragma once
#include <vector>
class argument
{
public:
	argument();
	~argument();
	argument::argument(std::string type_name, bool isbyref, int datalen, const char * datastr);
	bool byref;
	int len;
	std::vector<char> data;	
	std::string type;		//absolutely useless thing
};

