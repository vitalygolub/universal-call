#include "argument.h"

argument::argument()
	: byref(false)
	, len(0)
{
}

argument::argument(std::string type_name, bool isbyref, int datalen, const char * datastr )
	: type(type_name)
	,byref(isbyref)
	, len(datalen)
{
	
	for (int i = 0; i < strlen(datastr); i += 2)
	{
		char c =
			((datastr[i] < 'A' ? datastr[i] & 0xf : datastr[i] - 'A' + 10) << 4) +
			(datastr[i + 1] < 'A' ? datastr[i + 1] & 0xf : datastr[i + 1] - 'A' + 10);
		data.insert(data.end(), c);
	
	}
}

argument::~argument()
{
}
