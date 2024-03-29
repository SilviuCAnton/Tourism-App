#include "Tests.h"
#include "Service.h"
#include <assert.h>
#include <algorithm>
#include "Exceptions.h"
#include "Wishlist.h"
#include <iostream>

namespace FunctionalityTest {
	void testAdd() {
		FileRepository myRepo{"testRepo.txt"};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 500);
		myService.addOffer("Oferta2", "Bali", "type1", 500);
		assert(std::cout << myService.getAllOffers().at(0));
		std::cout.clear();
		assert(myService.getAllOffers().size() == 2);
		try {
			myService.addOffer("Oferta2", "Bali", "type1", 500);
			assert(false);
		}
		catch (const DuplicateItemException& de) {
			assert(std::cout << de);
			std::cout.clear();
		}
		try {
			myService.addOffer("sfsdf", "sdsdf", "", 500);
			assert(false);
		}
		catch (const ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("fdssdd", "", "gdffgdfg", 500);
			assert(false);
		}
		catch (const ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("", "dsffds", "dssdfd", 500);
			assert(false);
		}
		catch (const ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}

		try {
			myService.addOffer("ddfs", "dfsdfs", "gsdsdg", -500);
			assert(false);
		}
		catch (const ValidException& ve) {
			assert(std::cout << ve);
			std::cout.clear();
		}
		myRepo.emptyRepo();
	}

	void testModify() {
		FileRepository myRepo{ "testRepo.txt" };
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta1", "Bali", "type1", 500);
		myService.addOffer("Oferta2", "Bali", "type1", 500);
		assert(myService.getAllOffers().size() == 2);
		myService.modifyOffer(1, "Oferta3", "New York", "type2", 500);
		assert(myService.getAllOffers().at(1).getDestination() == "New York");
		assert(myService.getAllOffers().at(1).getType() == "type2");
		assert(myService.getAllOffers().at(1).getName() == "Oferta3");
		assert(myService.getAllOffers().at(1).getPrice() == 500);
		try {
			myService.modifyOffer(2, "Oferta3", "New York", "type2", 500);
			assert(false);
		}
		catch (const DuplicateItemException& de) {
			assert(std::cout << de);
			std::cout.clear();
		}
		myRepo.emptyRepo();
	}

	void testRemove() {
		FileRepository myRepo{ "testRepo.txt" };
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
		catch (const InexistentItemException& iie) {
			assert(std::cout << iie);
			std::cout.clear();
		}
		myRepo.emptyRepo();
	}

	void testFind() {
		FileRepository myRepo{ "testRepo.txt" };
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
		myRepo.emptyRepo();
	}

	void testFilters() {
		FileRepository myRepo{ "testRepo.txt" };
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
		myRepo.emptyRepo();
	}

	void testSortings() {
		FileRepository myRepo{ "testRepo.txt" };
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta2", "Bali", "type2", 250);
		myService.addOffer("Oferta1", "Bali", "type1", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		std::vector<Offer> result = myService.sortByName();
		assert(result.at(0).getName() == "Oferta1" && result.at(2).getDestination() == "New York" && result.at(4).getName() == "Vacanta3");
		result = myService.sortByDestination();
		assert(result.at(0).getDestination() == "Bali" && result.at(4).getDestination() == "New York");
		result = myService.sortByTypeAndPrice();
		assert(result.at(1).getType() == "type2" && result.at(1).getPrice() == 725.25 && result.at(4).getPrice() == 5005.3);
		myRepo.emptyRepo();
	}

	void testWishlist() {
		FileRepository myRepo{ "testRepo.txt" };
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta2", "Bali", "type2", 250);
		myService.addOffer("Oferta1", "Bali", "type1", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		myService.populateWishlist(3);
		assert(myService.getWishlistSize() == 3);
		myService.emptyWishlist();
		assert(myService.getWishlistSize() == 0);
		myService.addToWishlist(5);
		myService.addToWishlist(3);
		myService.exportWishlistCSV("WishlistExportTest");

		try {
			myService.addToWishlist(3);
			assert(false);
		}
		catch (const DuplicateItemException&) {
			assert(true);
		}

		try {
			myService.addToWishlist(8);
			assert(false);
		}
		catch (const InexistentItemException&) {
			assert(true);
		}

		Wishlist wishlist2{};
		Wishlist myWishlist{};
		wishlist2.populateWishlist(3, myService.getAllOffers());
		myWishlist = wishlist2;
		assert(myWishlist == wishlist2);
		wishlist2.populateWishlist(3, myService.getAllOffers());
		assert(!(myWishlist == wishlist2));
		wishlist2 = wishlist2;
		assert(wishlist2.getSize() == 3);

		assert(myService.getWishlist().at(0).getName() == "Vacanta3" && myService.getWishlist().at(1).getType() == "type3");
		assert(myService.getWishlistSize() == 2);
		myService.emptyWishlist();
		assert(myService.getWishlistSize() == 0);
		myRepo.emptyRepo();
	}

	void testStatistics() {
		FileRepository myRepo{ "testRepo.txt" };
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta2", "Bali", "type2", 250);
		myService.addOffer("Oferta1", "Bali", "type1", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		std::vector<TypeCountDTO> stat = myService.typeStatistic();
		std::for_each(stat.begin(), stat.end(), [](const auto& dto) {
			if (dto.getType() == "type3") {
				assert(dto.getCount() == 2);
			}

			if (dto.getType() == "type1") {
				assert(dto.getCount() == 1);
			}

			if (dto.getType() == "type2") {
				assert(dto.getCount() == 2);
			}
		});
		myRepo.emptyRepo();
	}

	void testUndo() {
		FileRepository myRepo{ "testRepo.txt" };
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		myService.addOffer("Oferta2", "Bali", "type2", 250);
		myService.addOffer("Oferta1", "Bali", "type1", 500.24);
		myService.addOffer("Vacanta1", "New York", "type3", 6000);
		myService.addOffer("Vacanta2", "Dubai", "type2", 725.25);
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);

		myService.undo();
		myService.addOffer("Vacanta3", "Dubai", "type3", 5005.3);
		try {
			myService.redo();
			assert(false);
		}
		catch (const ValidException&) {
			assert(true);
		}

		myService.modifyOffer(1, "Oferta6", "Bali", "type2", 250);
		myService.undo();
		myService.modifyOffer(1, "Oferta6", "Bali", "type2", 250);
		try {
			myService.redo();
			assert(false);
		}
		catch (const ValidException&) {
			assert(true);
		}

		myService.undo();
		myService.redo();
		assert(myService.getAllOffers().at(4).getName() == "Oferta6");
	
		myService.undo();
		myService.redo();
		assert(myService.getAllOffers().size() == 5);
		try {
			myService.redo();
			assert(false);
		}
		catch (const ValidException&) {
			assert(true);
		}
		myService.undo(); // Undo la modify
		myService.undo(); // Undo la add
		assert(myService.getAllOffers().size() == 4);
		myService.redo(); // Redo la add
		myService.undo(); 
		myService.removeOffer(1);
		assert(myService.getAllOffers().size() == 3);
		myService.undo();
		myService.redo();
		myService.undo();
		myService.undo();
		myService.undo();
		myService.undo();
		myService.undo();
		try {
			myService.undo();
			assert(false);
		}
		catch (const ValidException&) {
			assert(true);
		}
		assert(myService.getAllOffers().size() == 0);

		myRepo.emptyRepo();
	}

	void testProbabilityRepo() {
		ProbabilityRepo myRepo{1};
		OfferValidator myValidator{};
		Service myService{ myRepo, myValidator };
		try {
			myService.addOffer("Oferta2", "Bali", "type2", 250);
			assert(false);
		}
		catch (ValidException&) {
			assert(true);
		}
		try {
			myService.modifyOffer(1,"Oferta1", "Bali", "type2", 250);
			assert(false);
		}
		catch (ValidException&) {
			assert(true);
		}
		try {
			myService.removeOffer(1);
			assert(false);
		}
		catch (InexistentItemException&) {
			assert(true);
		}

		ProbabilityRepo myRepo1{ 0 };
		OfferValidator myValidator1{};
		Service myService1{ myRepo1, myValidator1 };

		try {
			myService1.addOffer("Oferta2", "Bali", "type2", 250);
			myService1.addOffer("Oferta5", "Bali", "type2", 2530);
			myService1.modifyOffer(1, "Oferta1", "Bali", "type2", 250);
			myService1.removeOffer(1);
			assert(true);
		}
		catch (ValidException&) {
			assert(false);
		}

	}

	void testAll() {
		testAdd();
		testModify();
		testRemove();
		testFind();
		testFilters();
		testSortings();
		testWishlist();
		testStatistics();
		testUndo();
		testProbabilityRepo();
		system("cls");
	}
}