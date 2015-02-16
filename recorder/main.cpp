#include <iostream>
#include <fstream>

extern int NVF_Cashier(long *aStatus, char *cashier_name);
extern int NVF_AddPayment(long *aStatus, int tender_number, double amount, char* acomments);
extern int GetFMBParams(char *aComPort, long *aBaudRate, int *aFMB_Disable, int *aAuto_Open, int *aFMB_Debug);
extern int SetDebug(void);


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

	
	return 0;
}

