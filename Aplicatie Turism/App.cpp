//Main module of the app
#include "Console.h"
#include "Tests.h"
#include "MyList.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC

int main() {
	{
		List<int> myList{};
		myList.insert(0, 5);
		myList.insert(0, 4);
		for (auto x : myList) {
			std::cout << x;
		}
		myList.remove(myList.begin());
		if (myList.size() != 1)
			return 0;
		myList.remove(myList.begin());
		if (!myList.isEmpty()) {
			return 0;
		}
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