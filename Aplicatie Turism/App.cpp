//Main module of the app
#include "Console.h"
#include "Tests.h"
#include "MyList.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC

int main() {
	{
		FunctionalityTest::testAll();
		OfferValidator myValidator{};
		Repository myRepo{};
		Service myService{ myRepo, myValidator };
		Console myConsole{ myService };
		myConsole.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}