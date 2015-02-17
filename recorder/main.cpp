#include <iostream>
#include <fstream>

extern int __stdcall NVF_Cashier(long *aStatus, char *cashier_name);
extern int __stdcall NVF_AddPayment(long *aStatus, int tender_number, double amount, char* acomments);
extern int __cdecl GetFMBParams(char *aComPort, long *aBaudRate, int *aFMB_Disable, int *aAuto_Open, int *aFMB_Debug);
extern int __cdecl iamvoid(void);
extern int SetDebug(void);

std::fstream &a(int &c, double **e)
{
	std::cout << __FUNCSIG__ << std::endl;
	std::fstream f;
	return  f;
	
}

int main(int argc, char* argv[])
{
	int res,rc;
	char outstr[50];
	long BaudRate=1234;
	int FMB_Disable=1, Auto_Open=2, FMB_Debug=3;
	char ComPort[]="/dev/XZtty01";
	
	long status;
	int tender_number = 4;
	double amount = 1.23;
	char * comments = "hello";

	std::remove("log.txt"); //remove log file, test only with new records 
	SetDebug();

	rc = GetFMBParams(ComPort, &BaudRate, &FMB_Disable, &Auto_Open, &FMB_Debug);
	rc = NVF_AddPayment(&status, tender_number, amount, comments);
	rc = NVF_Cashier(&status, "cashier 1");
	rc = iamvoid();
	int c = 10;
	double e = 20, *pe = &e;
	
	a(c, &pe);
	return 0;
}

