//Main module of the app
#include "Console.h"
#include "Tests.h"
#include "MyList.h"
#include "Wishlist.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC

int main() {
	{
		FunctionalityTest::testAll();
		OfferValidator myValidator{};
		FileRepository myRepo{"repository.txt"};
		//ProbabilityRepo myRepo{ 0.5 };
		Wishlist myWishlist{};
		Service myService{ myRepo, myValidator, myWishlist };
		Console myConsole{ myService };
		myConsole.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}