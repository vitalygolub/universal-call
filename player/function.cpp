#include "function.h"
#include <cstring>

function::function():
parsed(false)
{
}

function::function(std::istream  &src):
parsed(false)
{
	std::string tmp;
	std::getline(src, tmp);
	std::vector<size_t> separators;
	
	std::string pattern = " ,(){}",token;
	
	for (size_t i = 0; i < tmp.length(); i++)
	{

		if (pattern.find(tmp[i], 0) != std::string::npos)
			separators.push_back(i);
	
	}
	separators.push_back(tmp.length());
	if (separators.size() < 5)	//not a log record
		return;

	size_t curr = 0;
	auto next = separators.begin();
	
	token = tmp.substr(curr, *next - curr);
	argument a(token, false);
	this->return_type = a;
	curr = *next++ + 1;
	token = tmp.substr(curr, *next - curr);
	if (token == "*")
	{
		a.byref = true;
		curr = *next++ + 1;
		token = tmp.substr(curr, *next - curr);
	}
	this->conventions = token;
	curr = *next++ + 1;
	token = tmp.substr(curr, *next - curr);
	this->name = token;
	//arguments

	if (tmp[*next] = '(')
	{
		do
		{
			curr = *next++ + 1;
			token = tmp.substr(curr, *next - curr);
			a.type = token;
			
			if (tmp[*next] != ',' && tmp[*next] != ')')
			{
				a.byref = true;
				curr = *next++ + 1;
				token = tmp.substr(curr, *next - curr);
			}
			else
			{
				a.byref = false;
			}
			if (a.type == "void")	//special case
			{
				if (!a.byref)
					break;	//that's allm, function has no arguments
				
			}
			else if(a.type.length() )
				this->arguments.push_back(a);

		} while (tmp[*next] != ')');	//end of argument list
	}
	//else ?

	auto curarg = this->arguments.begin();
	auto endarg = this->arguments.end();

	if (arguments.size())
	{
		if (tmp[*next++] = '{')	//data
		{
			do
			{
				curr = *next++ + 1;
				token = tmp.substr(curr, *next - curr);
				(*curarg++).setdata(token);
			} while (endarg != curarg && tmp[*next] != '}');	//end of data
		}
		//else ?
		//make binary data
		for (auto it = arguments.begin(); it != arguments.end(); it++)
		{
			if ((*it).byref)
			{
				(this->data).push_back((int)(&(*it).data[0]));
			}
			else
			{
				//align to int
				int len = (*it).data.size();
				len = (len % sizeof(int)) ? (len / sizeof(int)) + 1 : (len / sizeof(int));
				this->data.resize(this->data.size() + len);
				std::memcpy(&this->data[data.size() - len], &(*it).data[0], (*it).data.size());
			}
		}
	}
	parsed = true;
}

std::string function::get_conventions()
{
	return this->conventions;
}

function::~function()
{
}


int function::get_datalength()
{
	return this->data.size()*sizeof(int);
}


void * function::get_data()
{
	return (void *)&(this->data[0]) ;
}

const char * function::get_name()
{
	return this->name.c_str();
}
