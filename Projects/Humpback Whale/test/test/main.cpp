#include "test.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SkeletonKey w;
	w.show();
	return a.exec();
}
