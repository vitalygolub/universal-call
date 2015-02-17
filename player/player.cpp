#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "argument.h"
#include "function.h"


FARPROC get_func_pointer(const char * funcname)
{
	static HMODULE module = NULL;
	if (module == NULL)
		module = LoadLibraryA("library.dll");

	return GetProcAddress(module, funcname);
}

template<int N> struct stackframe	//stack frame for universal calls, just syntax constraction to push to stack 
{
public: 
	int b[N]; 
	typedef int(__stdcall *functype_stdcall)(stackframe<N>);
	typedef int(__cdecl *functype_cdecl)(stackframe<N>);

	void call(const char *func_name, void * stackdata, int stacklen, const std::string conventions)
	{

		auto fn = get_func_pointer(func_name);
		if (fn != NULL)
		{
			memcpy(&this->b[0], stackdata, stacklen);
			
			if (conventions == "__stdcall")
			{
				std::cout << "Function returned " << ((functype_stdcall)fn)(*this) << std::endl;
			}
			if (conventions == "__cdecl")
			{
				std::cout << "Function returned " << ((functype_cdecl)fn)(*this) << std::endl;
			}

		}
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
		std::istream *my = &logfile;

		stackframe<20> sf ;

		stackframe<9> *psf09 = (stackframe<9> *) &sf;
		stackframe<8> *psf08 = (stackframe<8> *) &sf;
		stackframe<7> *psf07 = (stackframe<7> *) &sf;
		stackframe<6> *psf06 = (stackframe<6> *) &sf;
		stackframe<5> *psf05 = (stackframe<5> *) &sf;
		stackframe<4> *psf04 = (stackframe<4> *) &sf;
		stackframe<3> *psf03 = (stackframe<3> *) &sf;
		stackframe<2> *psf02 = (stackframe<2> *) &sf;
		stackframe<1> *psf01 = (stackframe<1> *) &sf;
		stackframe<0> *psf00 = (stackframe<0> *) &sf;
	

		function *f;
		while (!my->eof())
		{
			f = new function(*my);
			if (f->parsed)
			{
				switch (f -> get_datalength() / sizeof(int))
				{
				case 0:
					psf00->call(f->get_name(), NULL, 0, f->get_conventions());
					break;
				case 1:
					psf01->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 2:
					psf02->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 3:
					psf03->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 4:
					psf04->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 5:
					psf05->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 6:
					psf06->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 7:
					psf07->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 8:
					psf08->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				case 9:
					psf09->call(f->get_name(), f->get_data(), f->get_datalength(), f->get_conventions());
					break;
				}
			}
			delete(f);
		}


		
		
		
	}
	return 0;
}


