#include "argument.h"

argument::argument()
	: byref(false)
{
}

argument::argument(std::string type_name, bool isbyref)
	: type(type_name)
	, byref(isbyref)
{
}

int argument::setdata(const std::string datastr)
{

	for (int i = 0; i < strlen(datastr.c_str()); i += 2)
	{
		char c =
			((datastr[i] < 'A' ? datastr[i] & 0xf : datastr[i] - 'A' + 10) << 4) +
			(datastr[i + 1] < 'A' ? datastr[i + 1] & 0xf : datastr[i + 1] - 'A' + 10);
		data.push_back( c);
	
	}
	return data.size();
}

argument::~argument()
{
}


