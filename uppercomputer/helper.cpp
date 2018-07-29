#include "helper.h"

void printLog(string log) {
	ofstream fout;
	SYSTEMTIME sys;
	::GetLocalTime(&sys);

	fout.open("log.txt", ios_base::in | ios_base::app);
	fout << "[" << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "." << sys.wMilliseconds << "]\t" << log << endl;
	fout.close();
}

void deleteLog() {
	ofstream fout;
	fout.open("log.txt", ofstream::out | ofstream::trunc);
	fout.close();
}