#include "Service.h"
#include "Exceptions.h"
#include <algorithm>

Service::Service(Repository& repository, const OfferValidator& validator) : Observable(), repository{ repository }, validator{ validator }, undoIndex{ -1 } {
}

void Service::addOffer(std::string name, std::string destination, std::string type, double price) {
	const int newOfferId = this->repository.getMaxId() + 1;
	Offer newOffer{ newOfferId, name, destination, type, price };

	this->validator.validate(newOffer);

	const std::vector<Offer>& offers = this->repository.getAll();
	for (const auto& offer : offers) {
		if (offer == newOffer) {
			throw DuplicateItemException("Oferta exista deja!!!");
		}
	}

	this->repository.store(newOffer);

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoAdd>(repository, newOffer));
	undoIndex = undoList.size() - 1;
	notifyObservers();
}

void Service::modifyOffer(int id, std::string name, std::string destination, std::string type, double price) {
	Offer newOffer{ id, name, destination, type, price };
	Offer originalOffer{ 0,"","","",0 };
	this->validator.validate(newOffer);

	const std::vector<Offer>& offers = this->repository.getAll();
	for (const auto& offer : offers) {
		if (offer == newOffer) {
			throw DuplicateItemException("Oferta exista deja!!!");
		}
	}

	for (const auto& offer : getAllOffers()) {
		if (newOffer.getId() == offer.getId()) {
			originalOffer = offer;
		}
	}

	this->repository.update(newOffer);

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoModify>(repository, originalOffer, newOffer));
	undoIndex = undoList.size() - 1;
	notifyObservers();
}

void Service::removeOffer(int id) {
	Offer myOffer{ 0,"","","",0 };

	for (const auto& offer : getAllOffers()) {
		if (id == offer.getId()) {
			myOffer = offer;
		}
	}

	Offer off = findById(id);
	this->repository.deleteElement(id);

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoRemove>(repository, myOffer));
	undoIndex = undoList.size() - 1;
	wishlist.removeFromWishlist(off);
	notifyObservers();
	}

const std::vector<Offer>& Service::getAllOffers() const {
	return this->repository.getAll();
}

const Offer & Service::findById(int id) {
	for (const auto& offer : getAllOffers()) {
		if (offer.getId() == id) {
			return offer;
		}
	}
	throw InexistentItemException("Oferta cu id-ul cautat nu exista!!");
}

std::vector<Offer> Service::findByName(std::string sequence) const {
	std::vector<Offer> filteredOffers;
	const std::vector<Offer>& offers = this->repository.getAll();

	std::copy_if(offers.begin(), offers.end(), std::back_inserter(filteredOffers), [&sequence](const auto& offer) {
		return offer.getName().find(sequence) != std::string::npos;
	});

	return filteredOffers;
}

std::vector<Offer> Service::filterByDestination(std::string destination) const {
	std::vector<Offer> filteredOffers;
	const std::vector<Offer>& offers = this->repository.getAll();

	std::copy_if(offers.begin(), offers.end(), std::back_inserter(filteredOffers), [&destination](const auto& offer) {
		return offer.getDestination() == destination;
	});

	return filteredOffers;
}

std::vector<Offer> Service::filterByPrice(double price) const {
	std::vector<Offer> filteredOffers;
	const std::vector<Offer>& offers = this->repository.getAll();

	std::copy_if(offers.begin(), offers.end(), std::back_inserter(filteredOffers), [&price](const auto& offer) {
		return offer.getPrice() <= price;
	});

	return filteredOffers;
}

std::vector<Offer> Service::sortByName() const {
	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		std::string str1 = offer1.getName();
		std::string str2 = offer2.getName();
		std::transform(str1.begin(), str1.end(), str1.begin(), tolower);
		std::transform(str2.begin(), str2.end(), str2.begin(), tolower);
		return str1 <= str2;
	});

	return copyOffers;
}

std::vector<Offer> Service::sortByDestination() const {

	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		std::string s1 = offer1.getDestination();
		std::string s2 = offer2.getDestination();
		std::transform(s1.begin(), s1.end(), s1.begin(), tolower);
		std::transform(s2.begin(), s2.end(), s2.begin(), tolower);
		return s1 < s2;
	});

	return copyOffers;
}

std::vector<Offer> Service::sortByTypeAndPrice() const {
	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		if (offer1.getType() != offer2.getType()) {
			std::string s1 = offer1.getType();
			std::string s2 = offer2.getType();
			std::transform(s1.begin(), s1.end(), s1.begin(), tolower);
			std::transform(s2.begin(), s2.end(), s2.begin(), tolower);
			return s1 < s2;
		}
		return offer1.getPrice() >= offer2.getPrice();
	});

	return copyOffers;
}

void Service::addToWishlist(int id) {
	bool found{ false };
	for (const auto& offer : repository.getAll()) {
		if (offer.getId() == id) {
			wishlist.addToWishlist(offer);
			found = true;
			break;
		}
	}
	if (!found) {
		throw InexistentItemException("Oferta cu id-ul dat nu exista!!!");
	}
}

void Service::emptyWishlist() noexcept {
	wishlist.emptyWishlist();
}

void Service::populateWishlist(int n) {
	wishlist.populateWishlist(n, repository.getAll());
}

const std::vector<Offer>& Service::getWishlist() const noexcept {
	return wishlist.getAll();
}

const int Service::getWishlistSize() const noexcept {
	return wishlist.getSize();
}

std::vector<TypeCountDTO> Service::typeStatistic() const {
	std::vector<TypeCountDTO> result{};
	std::map<std::string, int> statistic;
	const std::vector<Offer>& offers = getAllOffers();

	std::for_each(offers.begin(), offers.end(), [&statistic](const auto& offer) {
		auto it = statistic.find(offer.getType());
		if (it == statistic.end()) {
			statistic[offer.getType()] = 1;
		}
		else {
			statistic[offer.getType()]++;
		}
	}); 

	std::for_each(statistic.begin(), statistic.end(), [&result](const auto& myMapPair) {
		TypeCountDTO myDTO{ myMapPair.first, myMapPair.second };
		result.push_back(myDTO);
	});

	return result;
}

void Service::undo() {
	if (undoIndex < 0) {
		throw ValidException("Nu se mai poate face undo!!!");
	}
	undoList.at(undoIndex)->doUndo();
	undoIndex--;
	notifyObservers();
}

void Service::redo() {
	if (undoIndex == undoList.size() - 1) {
		throw ValidException("Nu se mai poate face redo!!!");
	}
	undoList.at(undoIndex + 1)->doRedo();
	undoIndex++;
	notifyObservers();
}

void Service::exportWishlistCSV(std::string saveName) const {
	wishlist.exportCSV(saveName);
}

void Service::subscribeToWishlist(Observer * obs) {
	wishlist.addObserver(obs);
}

void Service::unsubscribeFromWishlist(Observer * obs) {
	wishlist.removeSubscriber(obs);
}
