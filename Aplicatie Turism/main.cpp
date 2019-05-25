#include "GUI.h"
#include <QtWidgets/QApplication>
#include <Tests.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FunctionalityTest::testAll();
	OfferValidator myValidator{};
	FileRepository myRepo{ "repository.txt" };
	Service myService{ myRepo, myValidator };
	GUI myGUI{ myService };
	myGUI.show();
	return a.exec();
}
