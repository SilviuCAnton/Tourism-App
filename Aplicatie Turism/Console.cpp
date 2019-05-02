//#include "Console.h"
//#include <iostream>
//#include "Exceptions.h"
//#include <exception>
//#include <algorithm>
//
//
//Console::Console(Service& service) noexcept : service{ service } {
//}
//
//void Console::displayMenu() const {
//	std::cout << "Alegeti una dintre urmatoarele optiuni:" << std::endl;
//	std::cout << "1  Adaugare oferta" << std::endl;
//	std::cout << "2  Modificare oferta" << std::endl;
//	std::cout << "3  Stergere oferta" << std::endl;
//	std::cout << "4  Cautare dupa nume" << std::endl;
//	std::cout << "5  Filtrare dupa destinatie" << std::endl;
//	std::cout << "6  Filtrare dupa pret" << std::endl;
//	std::cout << "7  Sortare crescator dupa nume" << std::endl;
//	std::cout << "8  Sortare crescator dupa destinatie" << std::endl;
//	std::cout << "9  Sortare crescator dupa tip si descrescator dupa pret" << std::endl;
//	std::cout << "10 Optiuni wishlist" << std::endl;
//	std::cout << "11 Situatie tipuri oferte" << std::endl;
//	std::cout << "12 Undo" << std::endl;
//	std::cout << "13 Redo" << std::endl;
//	std::cout << "0  Inchideti aplicatia" << std::endl;
//	std::cout << "Introduceti o optiune: ";
//}
//
//void Console::printWishlist(const std::vector<Offer>& offers) const {
//	std::cout << std::endl;
//	std::cout << "Wishlist:" << std::endl;
//	for (const auto& offer : offers) {
//		std::cout << offer << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Console::typeStatisticsUI() const {
//	std::vector<TypeCountDTO> stat = service.typeStatistic();
//	std::cout << std::endl;
//	std::cout << "Situatie tipuri oferte:" << std::endl;
//	std::for_each(stat.begin(), stat.end(), [](const auto& dto) {
//		std::cout << dto.getType() << ":" << dto.getCount() << std::endl;
//	});
//}
//
//void Console::printList(const std::vector<Offer>& offers) const {
//	std::cout << std::endl;
//	std::cout << "Offers:" << std::endl;
//	for (const auto& offer : offers) {
//		std::cout << offer << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Console::printResultList(const std::vector<Offer>& offers) const {
//	std::cout << std::endl;
//	std::cout << "Result:" << std::endl;
//	for (const auto& offer : offers) {
//		std::cout << offer << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Console::addOfferUI() {
//	double price{ 0 };
//	std::string name, destination, type;
//	if (std::getchar()) {};
//	std::cout << "Introduceti nume: "; std::getline(std::cin, name, '\n');
//	std::cout << "Introduceti destinatie: "; std::getline(std::cin, destination, '\n');
//	std::cout << "Introduceti tip: "; std::getline(std::cin, type, '\n');
//	if (name.size() == 0 || destination.size() == 0 || type.size() == 0)
//		throw std::domain_error("Campurile nu pot fi vide!!!");
//	std::cout << "Introduceti pret: "; std::cin >> price;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//	this->service.addOffer(name, destination, type, price);
//	std::cout << "Oferta a fost adaugata!" << std::endl << std::endl;
//}
//
//void Console::modifyOfferUI() {
//	double price{ 0 };
//	int id{ 0 };
//	std::string name, destination, type;
//
//	std::cout << "Introduceti id: "; std::cin >> id;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//
//	if (std::getchar()) {};
//	std::cout << "Introduceti nume nou: "; std::getline(std::cin, name, '\n');
//	std::cout << "Introduceti destinatie noua: "; std::getline(std::cin, destination, '\n');
//	std::cout << "Introduceti tip nou: "; std::getline(std::cin, type, '\n');
//	if (name.size() == 0 || destination.size() == 0 || type.size() == 0)
//		throw std::domain_error("Campurile nu pot fi vide!!!");
//
//	std::cout << "Introduceti pret nou: "; std::cin >> price;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//
//	this->service.modifyOffer(id, name, destination, type, price);
//	std::cout << std::endl << "Oferta a fost modificata!" << std::endl << std::endl;
//}
//
//void Console::removeOfferUI() {
//	int id;
//
//	std::cout << "Introduceti id: "; std::cin >> id;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//	this->service.removeOffer(id);
//	std::cout << std::endl << "Oferta a fost stearsa!" << std::endl << std::endl;
//}
//
//void Console::findByNameUI() const {
//	std::string name;
//
//	if (std::getchar()) {};
//	std::cout << "Introduceti nume: "; std::getline(std::cin, name, '\n');
//	if (name.size() == 0)
//		throw std::domain_error("Nume nu poate fi vid!!!");
//
//	std::vector<Offer> foundOffers = service.findByName(name);
//	if (foundOffers.size() == 0) {
//		std::cerr << std::endl << "Nu sunt oferete cu numele dat!!!" << std::endl << std::endl;
//	}
//	else {
//		printResultList(foundOffers);
//	}
//}
//
//void Console::filterByDestinationUI() const {
//	std::string destination;
//
//	if (std::getchar()) {};
//	std::cout << "Introduceti destinatie: "; std::getline(std::cin, destination, '\n');
//	if (destination.size() == 0)
//		throw std::domain_error("Destinatie nu poate fi vida!!!");
//
//	std::vector<Offer> filteredOffers = service.filterByDestination(destination);
//	if (filteredOffers.size() == 0) {
//		std::cerr << std::endl << "Nu sunt oferete cu destinatia data!!!" << std::endl << std::endl;
//	}
//	else {
//		printResultList(filteredOffers);
//	}
//}
//
//void Console::filterByPriceUI() const {
//	double price;
//
//	std::cout << "Introduceti pretul: "; std::cin >> price;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//
//	std::vector<Offer> filteredOffers = service.filterByPrice(price);
//	if (filteredOffers.size() == 0) {
//		std::cerr << std::endl << "Nu sunt oferete cu pretul dat!!!" << std::endl << std::endl;
//	}
//	else {
//		printResultList(filteredOffers);
//	}
//}
//
//void Console::sortByNameUI() const {
//	std::vector<Offer> sortedOffers = service.sortByName();
//	printResultList(sortedOffers);
//}
//
//void Console::sortByDestinationUI() const {
//	std::vector<Offer> sortedOffers = service.sortByDestination();
//	printResultList(sortedOffers);
//}
//
//void Console::sortByTypeAndPriceUI() const {
//	std::vector<Offer> sortedOffers = service.sortByTypeAndPrice();
//	printResultList(sortedOffers);
//}
//
//void Console::addToWishlistUI() {
//	int id{ 0 };
//
//	printList(service.getAllOffers());
//
//	std::cout << "Introduceti id-ul ofertei: "; std::cin >> id;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//
//	service.addToWishlist(id);
//	std::cout << "Oferta a fost adaugata in wishlist!" << std::endl;
//}
//
//void Console::emptyWishlistUI() {
//	service.emptyWishlist();
//	std::cout << "Wishlistul a fost golit!" << std::endl;
//}
//
//void Console::populateWishlistUI() {
//	int number{ 0 };
//
//	std::cout << "Introduceti numarul de oferte: "; std::cin >> number;
//	if (std::cin.fail()) {
//		std::cin.clear();
//		std::string ignoreLine;
//		std::getline(std::cin, ignoreLine);
//		throw std::domain_error("Input nevalid!!!");
//	}
//
//	service.populateWishlist(number);
//	std::cout << "Wishlistul a fost pupulat!" << std::endl;
//}
//
//void Console::undoUI() {
//	service.undo();
//}
//
//void Console::redoUI() {
//	service.redo();
//}
//
//void Console::exportWishlistUI() const {
//	std::string saveName;
//	std::cout << "Introduceti numele salvarii: ";
//	std::cin >> saveName;
//	service.exportWishlistCSV(saveName);
//	std::cout << "Wishlistul a fost salvat!" << std::endl;
//}
//
//void Console::run() {
//	int choice{ -1 };
//	int choiceWishlist{ -1 };
//	while (true) {
//		printWishlist(service.getWishlist());
//		displayMenu();
//		try {
//			const auto f = [&choice]() {
//				std::cin >> choice;
//				if (std::cin.fail()) {
//					std::cin.clear();
//					std::string ignoreLine;
//					std::getline(std::cin, ignoreLine);
//					throw std::domain_error("Input nevalid!!!");
//				}};
//			f();
//		} 
//		catch (const std::domain_error& de) {
//			std::cout << std::endl << de.what() << std::endl << std::endl;
//			continue;
//		}
//
//		if (choice == 0) {
//			break;
//		}
//
//		try {
//			switch (choice) {
//			case 1:
//				addOfferUI();
//				break;
//
//			case 2:
//				modifyOfferUI();
//				break;
//
//			case 3:
//				removeOfferUI();
//				break;
//
//			case 4:
//				findByNameUI();
//				break;
//
//			case 5:
//				filterByDestinationUI();
//				break;
//
//			case 6:
//				filterByPriceUI();
//				break;
//
//			case 7:
//				sortByNameUI();
//				break;
//
//			case 8:
//				sortByDestinationUI();
//				break;
//
//			case 9:
//				sortByTypeAndPriceUI();
//				break;
//
//			case 10:
//				std::cout << "Alegeti una dintre urmatoarele optiuni:" << std::endl;
//				std::cout << "1  Adauga la wishlist" << std::endl;
//				std::cout << "2  Goleste wishlist" << std::endl;
//				std::cout << "3  Populeaza wishlist cu oferte random" << std::endl;
//				std::cout << "4  Exporta wishlist" << std::endl;
//				std::cout << "0  Inapoi";
//				std::cout << "Introduceti o optiune: ";
//
//				try {
//					const auto f = [&choiceWishlist]() {
//						std::cin >> choiceWishlist;
//						if (std::cin.fail()) {
//							std::cin.clear();
//							std::string ignoreLine;
//							std::getline(std::cin, ignoreLine);
//							throw std::domain_error("Input nevalid!!!");
//						}};
//					f();
//				}
//				catch (const std::domain_error& de) {
//					std::cout << std::endl << de.what() << std::endl << std::endl;
//					continue;
//				}
//
//				switch (choiceWishlist) {
//				case 1:
//					addToWishlistUI();
//					break;
//
//				case 2:
//					emptyWishlistUI();
//					break;
//
//				case 3:
//					populateWishlistUI();
//					break;
//
//				case 4:
//					exportWishlistUI();
//					break;
//
//				case 0:
//					break;
//
//				default:
//					std::cerr << std::endl << "Optiunea nu exista!!!" << std::endl << std::endl;
//					break;
//				}
//
//				break;
//
//			case 11:
//				typeStatisticsUI();
//				break;
//
//			case 12:
//				undoUI();
//				break;
//			
//			case 13:
//				redoUI();
//				break;
//
//			default:
//				std::cerr << std::endl << "Optiunea nu exista!!!" << std::endl << std::endl;
//				break;
//			}
//		}
//		catch (const std::domain_error de) {
//			std::cerr << std::endl << de.what() << std::endl << std::endl;
//		}
//		catch (const InexistentItemException& iee) {
//			std::cerr << std::endl << iee << std::endl << std::endl;
//		}
//		catch (const DuplicateItemException& die) {
//			std::cerr << std::endl << die << std::endl << std::endl;
//		}
//		catch (const ValidException& ve) {
//			std::cerr << std::endl << ve << std::endl << std::endl;
//		}
//		
//	}
//}