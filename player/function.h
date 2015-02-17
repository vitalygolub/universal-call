#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "argument.h"

class function
{
public:
	function();
	~function();
	function(std::istream &);
	std::string get_conventions();
	int get_datalength();
	void * get_data();
	const char * get_name();
	bool parsed;
private:
	std::string conventions;
	std::string name;
	std::vector<argument> arguments;
	argument return_type;
	std::vector<int> data;
};

