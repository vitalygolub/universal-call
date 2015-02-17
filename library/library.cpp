// library.cpp : Defines the exported functions for the DLL application.
//
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>

std::string to_binary(void * data, int len);

#define BYREF(len,value)	 to_binary( (void *)(value), (len * sizeof(*value)) ) 
#define BYVAL(value)		 to_binary ( (void *)(&value) , sizeof(value) )
#include <windows.h>
bool debug = 0;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern int SetDebug(void)
{
	debug = 1;
	return 0;
}

extern int __cdecl GetFMBParams(char *aComPort, long *aBaudRate, int *aFMB_Disable, int *aAuto_Open, int *aFMB_Debug)
{
	if (debug)
	{
		std::ofstream logfile;
		logfile.open("log.txt", std::ofstream::out | std::ofstream::app);
		logfile
			<< __FUNCSIG__ << "{"
			<< BYREF(strlen(aComPort) + 1, aComPort) << ","
			<< BYREF(1, aBaudRate) << ","
			<< BYREF(1, aFMB_Disable) << ","
			<< BYREF(1, aAuto_Open) << ","
			<< BYREF(1, aFMB_Debug) << "}"
			<< std::endl;
			
		logfile.close();
	}
	std::cout << __FUNCTION__
		<< " aComPort = \"" << aComPort << "\"" << std::endl;

	
	return 42;

}

extern  int __stdcall  NVF_AddPayment(long *aStatus, int tender_number, double amount, char* acomments)
{
	if (debug)
	{
		std::ofstream logfile;
		logfile.open("log.txt", std::ofstream::out | std::ofstream::app);
		logfile
			<< __FUNCSIG__ << "{"
			<< BYREF(1, aStatus) << ","
			<< BYVAL(tender_number) << ","
			<< BYVAL(amount) << ","
			<< BYREF(strlen(acomments) + 1, acomments) << "}"
			<< std::endl;
		logfile.close();
	}

	std::cout << __FUNCTION__ << " tender_number = " << tender_number
		<< " amount = " << amount
		<< " acoments = \"" << acomments << "\"" << std::endl;

	return 25;
}

extern  int __stdcall NVF_Cashier(long *aStatus, char *cashier_name)
{
	if (debug)
	{
		std::ofstream logfile;
		logfile.open("log.txt", std::ofstream::out | std::ofstream::app);
		logfile
			<< __FUNCSIG__ << "{"
			<< BYREF(1, aStatus) << ","
			<< BYREF(strlen(cashier_name) + 1, cashier_name) << "}"
			<< std::endl;
			

		logfile.close();
	}
	std::cout << __FUNCTION__ << "  " << " cahier_name = \"" << cashier_name << "\"" << std::endl;
	return 123;
}

std::string  to_binary(void * data, int len)
{
	std::string tmp;
	char *pdata = (char *)data;
	char c;

	for (int i = 0, j = 0; i < len; i++, j = i << 1)
	{
		c = (pdata[i] >> 4) & 0x0f;
		c = (c < 10) ? c + '0' : c + 'A' - 10;
		tmp += c;
		c = pdata[i] & 0x0f;
		c = (c < 10) ? c + '0' : c + 'A' - 10;
		tmp += c;

	}

	return tmp;
}


int iamvoid(void)
{
	std::cout << "I Am Weasel^w void" << std::endl;
	if (debug)
	{
		std::ofstream logfile;
		logfile.open("log.txt", std::ofstream::out | std::ofstream::app);
		logfile
			<< __FUNCSIG__ << "{}"
			<< std::endl;

		logfile.close();
	}
	return 0;
}