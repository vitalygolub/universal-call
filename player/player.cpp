#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "argument.h"

void parse_and_call(char *);

template<int N> struct stackframe	//stack frame for universal calls, just syntax constraction to push to stack 
{
public: 
	int b[N]; 
	typedef int(*functype)(stackframe<N>);	
		//type of universal function  for current stack
	//stackframe(){ memset(b, 0, sizeof(stackframe)); }

	// type 
	FARPROC get_func_pointer(const char * funcname)
	{
		static HMODULE module = NULL;
		if (module == NULL)
			module = LoadLibraryA("library.dll");

		return GetProcAddress(module, funcname);
	}

	void parse_and_call(char * line)
	{
		std::stringstream ss(line);
		std::string buf;
		std::string fnname;
		std::string type_name;

		stackframe<N>::functype fn;
		if (ss >> fnname)		//token 0 is function name
			fn = (functype)this->get_func_pointer(fnname.c_str());
		else
			return;

		if (fn == NULL)
		{
			std::cout << "Function " << fnname << " not found" << std::endl;
			exit(1);
		}

		std::vector<argument> arguments;
		bool byref = false;
		int len = 0;

		while (ss >> type_name) //type name is useless, but will preserve
		{
			byref = false; len = 0;

			ss >> buf;	//* after type name or data
			if (buf == "*")
			{
				byref = true;
				ss >> buf;
				len = std::stoi(buf);
				ss >> buf;
			}
			else
			{
				len = buf.length() >> 1;	//TODO: will be better to comparewith typename, but next time
				byref = false;
			}
			arguments.insert(arguments.end(), argument(type_name, byref, len, buf.c_str()));
		}

		std::cout << "Function " << fnname << " has " << arguments.size() << " arguments" << std::endl;

		int *stack_ptr = this->b;

		for (int i = 0; i < arguments.size(); i++)
		{
			if (arguments[i].byref)
			{
				*stack_ptr = (int)(&(arguments[i].data[0]));	//copy pointer
				stack_ptr++;
			}
			else
			{
				//copy data to stack frame
				memcpy(stack_ptr, &(arguments[i].data[0]), arguments[i].len);
				stack_ptr += arguments[i].len >> 2;
			}
		}
		std::cout << "Function returned " << fn(*this) << std::endl;
	}


};

//stackframe<20>::functype  get_func_pointer(const char *);

int main(int argc, char* argv[])
{
	std::ifstream logfile;
	static char sline[256];
	logfile.open("log.txt", std::ofstream::in);
	while (!logfile.eof())
	{
		logfile.getline(sline, 256);
		stackframe<20> sf;
		sf.parse_and_call(sline);
		
	}
	return 0;
}


