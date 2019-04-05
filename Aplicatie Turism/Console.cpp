#include "Console.h"
#include <iostream>
#include "Exceptions.h"
#include <exception>


Console::Console(const Service& service) : service{ service } {
}

void Console::displayMenu() const {
	std::cout << "Alegeti una dintre urmatoarele optiuni:" << std::endl;
	std::cout << "1 Adaugare oferta" << std::endl;
	std::cout << "2 Modificare oferta" << std::endl;
	std::cout << "3 Stergere oferta" << std::endl;
	std::cout << "4 Cautare dupa nume" << std::endl;
	std::cout << "5 Filtrare dupa destinatie" << std::endl;
	std::cout << "6 Filtrare dupa pret" << std::endl;
	std::cout << "7 Sortare crescator dupa nume" << std::endl;
	std::cout << "8 Sortare crescator dupa destinatie" << std::endl;
	std::cout << "9 Sortare crescator dupa tip si descrescator dupa pret" << std::endl;
	std::cout << "0 Inchideti aplicatia" << std::endl;
	std::cout << "Introduceti o optiune: ";
}

void Console::printList(const std::vector<Offer>& offers) const {
	std::cout << std::endl;
	std::cout << "Offers:" << std::endl;
	for (const auto& offer : offers) {
		std::cout << offer << std::endl;
	}
	std::cout << std::endl;
}

void Console::printResultList(const std::vector<Offer>& offers) const {
	std::cout << std::endl;
	std::cout << "Result:" << std::endl;
	for (const auto& offer : offers) {
		std::cout << offer << std::endl;
	}
	std::cout << std::endl;
}

void Console::addOfferUI() {
	double price;
	std::string name, destination, type;
	try {
		std::getchar();
		std::cout << "Introduceti nume: "; std::getline(std::cin, name, '\n');
		std::cout << "Introduceti destinatie: "; std::getline(std::cin, destination, '\n');
		std::cout << "Introduceti tip: "; std::getline(std::cin, type, '\n');
		if (name.size() == 0 || destination.size() == 0 || type.size() == 0)
			throw std::domain_error("Campurile nu pot fi vide!!!");
		std::cout << "Introduceti pret: "; std::cin >> price;
		if (std::cin.fail()) {
			std::cin.clear();
			std::string ignoreLine;
			std::getline(std::cin, ignoreLine);
			throw std::domain_error("Input nevalid!!!");
		}
		this->service.addOffer(name, destination, type, price);
		std::cout << "Oferta a fost adaugata!" << std::endl << std::endl;
	} 
	catch (DuplicateItemException die) {
		std::cout << std::endl << die << std::endl << std::endl;
	}
	catch (ValidException& ve) {
		std::cout << std::endl << ve << std::endl << std::endl;
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::modifyOfferUI() {
	double price;
	int id;
	std::string name, destination, type;
	try {
		std::cout << "Introduceti id: "; std::cin >> id;
		if (std::cin.fail()) {
			std::cin.clear();
			std::string ignoreLine;
			std::getline(std::cin, ignoreLine);
			throw std::domain_error("Input nevalid!!!");
		}
		std::getchar();
		std::cout << "Introduceti nume nou: "; std::getline(std::cin, name, '\n');
		std::cout << "Introduceti destinatie noua: "; std::getline(std::cin, destination, '\n');
		std::cout << "Introduceti tip nou: "; std::getline(std::cin, type, '\n');
		if (name.size() == 0 || destination.size() == 0 || type.size() == 0)
			throw std::domain_error("Campurile nu pot fi vide!!!");
		std::cout << "Introduceti pret nou: "; std::cin >> price;
		if (std::cin.fail()) {
			std::cin.clear();
			std::string ignoreLine;
			std::getline(std::cin, ignoreLine);
			throw std::domain_error("Input nevalid!!!");
		}
		this->service.modifyOffer(id, name, destination, type, price);
		std::cout << std::endl << "Oferta a fost modificata!" << std::endl << std::endl;
	} 
	catch (DuplicateItemException& die) {
		std::cout << std::endl << die << std::endl << std::endl;
	} 
	catch (ValidException& ve) {
		std::cout << std::endl << ve << std::endl << std::endl;
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::removeOfferUI() {
	int id;
	try {
		std::cout << "Introduceti id: "; std::cin >> id;
		if (std::cin.fail()) {
			std::cin.clear();
			std::string ignoreLine;
			std::getline(std::cin, ignoreLine);
			throw std::domain_error("Input nevalid!!!");
		}
		this->service.removeOffer(id);
		std::cout << std::endl << "Oferta a fost stearsa!" << std::endl << std::endl;
	}
	catch (InexistentItemException& iee) {
		std::cout << std::endl << iee << std::endl << std::endl;
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::findByNameUI() const {
	std::string name;
	try {
		std::getchar();
		std::cout << "Introduceti nume: "; std::getline(std::cin, name, '\n');
		if (name.size() == 0)
			throw std::domain_error("Nume nu poate fi vid!!!");

		std::vector<Offer> foundOffers = service.findByName(name);
		if (foundOffers.size() == 0) {
			std::cout << std::endl << "Nu sunt oferete cu numele dat!!!" << std::endl << std::endl;
		}
		else {
			printResultList(foundOffers);
		}
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::filterByDestinationUI() const {
	std::string destination;
	try {
		std::getchar();
		std::cout << "Introduceti destinatie: "; std::getline(std::cin, destination, '\n');
		if (destination.size() == 0)
			throw std::domain_error("Destinatie nu poate fi vida!!!");

		std::vector<Offer> filteredOffers = service.filterByDestination(destination);
		if (filteredOffers.size() == 0) {
			std::cout << std::endl << "Nu sunt oferete cu destinatia data!!!" << std::endl << std::endl;
		}
		else {
			printResultList(filteredOffers);
		}
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::filterByPriceUI() const {
	double price;
	try {
		std::cout << "Introduceti pretul: "; std::cin >> price;
		if (std::cin.fail()) {
			std::cin.clear();
			std::string ignoreLine;
			std::getline(std::cin, ignoreLine);
			throw std::domain_error("Input nevalid!!!");
		}

		std::vector<Offer> filteredOffers = service.filterByPrice(price);
		if (filteredOffers.size() == 0) {
			std::cout << std::endl << "Nu sunt oferete cu pretul dat!!!" << std::endl << std::endl;
		}
		else {
			printResultList(filteredOffers);
		}
	}
	catch (std::domain_error& de) {
		std::cout << std::endl << de.what() << std::endl << std::endl;
	}
}

void Console::sortByNameUI() const {
	std::vector<Offer> sortedOffers = service.sortByName();
	printResultList(sortedOffers);
}

void Console::sortByDestinationUI() const {
	std::vector<Offer> sortedOffers = service.sortByDestination();
	printResultList(sortedOffers);
}

void Console::sortByTypeAndPriceUI() const {
	std::vector<Offer> sortedOffers = service.sortByTypeAndPrice();
	printResultList(sortedOffers);
}

void Console::run() {
	int choice{ -1 };
	while (true) {
		printList(service.getAllOffers());
		displayMenu();
		try {
			std::cin >> choice;
			if (std::cin.fail()) {
				std::cin.clear();
				std::string ignoreLine;
				std::getline(std::cin, ignoreLine);
				throw std::domain_error("Input nevalid!!!");
			}
		} 
		catch (std::domain_error& de) {
			std::cout << std::endl << de.what() << std::endl << std::endl;
			continue;
		}

		if (choice == 0) {
			break;
		}

		switch (choice) {
		case 1:
			addOfferUI();
			break;
		case 2:
			modifyOfferUI();
			break;
		case 3:
			removeOfferUI();
			break;
		case 4:
			findByNameUI();
			break;
		case 5:
			filterByDestinationUI();
			break;
		case 6:
			filterByPriceUI();
			break;
		case 7:
			sortByNameUI();
			break;
		case 8:
			sortByDestinationUI();
			break;
		case 9:
			sortByTypeAndPriceUI();
			break;
		case 10:
			printList(service.getAllOffers());
			break;
		default:
			std::cout << std::endl << "Optiunea nu exista!!!" << std::endl << std::endl;
			break;
		}
	}
}