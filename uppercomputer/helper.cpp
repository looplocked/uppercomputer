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

string MatToStr(Mat m) {
	string res = "";
	for (int i = 0; i < m.rows; i++) {
		res += "[";
		for (int j = 0; j < m.cols; j++) {
			res += to_string(m.at<double>(i, j)) + ", ";
		}
		res += "]\n";
	}
	return res;
}