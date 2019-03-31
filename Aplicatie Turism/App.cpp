//Main module of the app
#include "Console.h"
#define _CRTDBG_MAP_ALLOC

int main() {
	{
		OfferValidator myValidator{};
		Repository myRepo{};
		Service myService{ myRepo, myValidator };
		Console myConsole{ myService };
		myConsole.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}