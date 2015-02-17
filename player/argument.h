#pragma once
#include <vector>
class argument
{
public:
	argument();
	~argument();
	argument::argument(std::string type_name, bool isbyref);
	bool byref;
	std::vector<char> data;	
	std::string type;		//absolutely useless thing
	int setdata(const std::string indata);
};

