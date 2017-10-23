#include "uppercomputer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uppercomputer w;
	w.show();
	return a.exec();
}
