#include "AplicatieTurism.h"
#include <QtWidgets/QApplication>
#include <Tests.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FunctionalityTest::testAll();
	OfferValidator myValidator{};
	FileRepository myRepo{ "repository.txt" };
	Wishlist myWishlist{};
	Service myService{ myRepo, myValidator, myWishlist };
	AplicatieTurism w{ myService };
	w.show();
	return a.exec();
}
