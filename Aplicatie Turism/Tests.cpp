#include "Tests.h"
#include "Service.h"
#include <assert.h>
#include "Exceptions.h"
#include <iostream>

namespace FunctionalityTest {
	void testAdd() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 500);
		myService.addOffer("Oferta2", "Bali", "type1", 500);
		assert(std::cout << myService.getAllOffers()[0]);
		std::cout.clear();
		assert(myService.getAllOffers().size() == 2);
		try {
			myService.addOffer("Oferta2", "Bali", "type1", 500);
			assert(false);
		}
		catch (DuplicateItemException& de) {
			assert(std::cout << de);
			std::cout.clear();
		}
		try {
			myService.addOffer("sfsdf", "sdsdf", "", 500);
			assert(false);
		}
		catch (ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("fdssdd", "", "gdffgdfg", 500);
			assert(false);
		}
		catch (ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("", "dsffds", "dssdfd", 500);
			assert(false);
		}
		catch (ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("ddfs", "dfsdfs", "gsdsdg", -500);
			assert(false);
		}
		catch (ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}
	}

	void testModify() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 500);
		myService.addOffer("Oferta2", "Bali", "type1", 500);
		assert(myService.getAllOffers().size() == 2);
		myService.modifyOffer(1, "Oferta3", "New York", "type2", 500);
		assert(myService.getAllOffers()[1].getDestination() == "New York");
		assert(myService.getAllOffers()[1].getType() == "type2");
		assert(myService.getAllOffers()[1].getName() == "Oferta3");
		assert(myService.getAllOffers()[1].getPrice() == 500);
		try {
			myService.modifyOffer(2, "Oferta3", "New York", "type2", 500);
			assert(false);
		}
		catch (DuplicateItemException& de) {
			assert(std::cout << de);
			std::cout.clear();
		}
	}

	void testRemove() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 500);
		myService.addOffer("Oferta2", "Bali", "type1", 500);
		myService.removeOffer(2);
		assert(myService.getAllOffers().size() == 1);
		try {
			myService.removeOffer(2);
			assert(false);
		}
		catch (InexistentItemException& iie) {
			assert(std::cout << iie);
			std::cout.clear();
		}
	}

	void testFind() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 250);
		myService.addOffer("Oferta2", "Bali", "type2", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		std::vector<Offer> result = myService.findByName("fert");
		assert(result.size() == 2);
		result = myService.findByName("canta");
		assert(result.size() == 3);
		result = myService.findByName("lili");
		assert(result.size() == 0);
	}

	void testFilters() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 250);
		myService.addOffer("Oferta2", "Bali", "type2", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		std::vector<Offer> result = myService.filterByDestination("Dubai");
		assert(result.size() == 2);
		result = myService.filterByDestination("New York");
		assert(result.size() == 1);
		result = myService.filterByDestination("lala");
		assert(result.size() == 0);
		result = myService.filterByPrice(5000);
		assert(result.size() == 3);
		result = myService.filterByPrice(6000);
		assert(result.size() == 5);
		result = myService.filterByPrice(249);
		assert(result.size() == 0);
	}

	void testSortings() {
		Repository myRepo{};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 250);
		myService.addOffer("Oferta2", "Bali", "type2", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		std::vector<Offer> result = myService.sortByName();
		assert(result[0].getName() == "Oferta1" && result[2].getDestination() == "New York" && result[4].getName() == "Vacanta3");
		result = myService.sortByDestination();
		assert(result[0].getDestination() == "Bali" && result[4].getDestination() == "New York");
		result = myService.sortByTypeAndPrice();
		assert(result[1].getType() == "type2" && result[1].getPrice() == 725.25 && result[4].getPrice() == 5005.3);
	}

	void testAll() {
		testAdd();
		testModify();
		testRemove();
		testFind();
		testFilters();
		testSortings();
	}
}