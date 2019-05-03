#include "Service.h"
#include "Exceptions.h"
#include <algorithm>

Service::Service(Repository& repository, const OfferValidator& validator, const Wishlist&) : repository{ repository }, validator{ validator }, wishlist{ wishlist }, undoIndex{ -1 } {
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

	//const UndoAdd* undoPointer = new UndoAdd{ repository, newOffer };

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoAdd>(repository, newOffer));
	undoIndex = undoList.size() - 1;
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
	//const UndoModify* undoPointer = new UndoModify{ repository, originalOffer, newOffer };

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoModify>(repository, originalOffer, newOffer));
	undoIndex = undoList.size() - 1;
}

void Service::removeOffer(int id) {
	Offer myOffer{ 0,"","","",0 };

	for (const auto& offer : getAllOffers()) {
		if (id == offer.getId()) {
			myOffer = offer;
		}
	}

	this->repository.deleteElement(id);

	//const UndoRemove* undoPointer = new UndoRemove{ repository, myOffer };

	while (undoIndex != undoList.size() - 1) {
		undoList.pop_back();
	}

	undoList.push_back(std::make_unique<UndoRemove>(repository, myOffer));
	undoIndex = undoList.size() - 1;
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

	/*std::for_each(offers.begin(), offers.end(), [&filteredOffers, &sequence](const auto& offer) {
		if (offer.getName().find(sequence) != std::string::npos) {
			filteredOffers.push_back(offer);
		}
	});*/
}

std::vector<Offer> Service::filterByDestination(std::string destination) const {
	std::vector<Offer> filteredOffers;
	const std::vector<Offer>& offers = this->repository.getAll();

	std::copy_if(offers.begin(), offers.end(), std::back_inserter(filteredOffers), [&destination](const auto& offer) {
		return offer.getDestination() == destination;
	});

	return filteredOffers;

	/*std::for_each(offers.begin(), offers.end(), [&filteredOffers, &destination](const auto& offer) {
		if (offer.getDestination() == destination)
			filteredOffers.push_back(offer);
	});*/
}

std::vector<Offer> Service::filterByPrice(double price) const {
	std::vector<Offer> filteredOffers;
	const std::vector<Offer>& offers = this->repository.getAll();

	std::copy_if(offers.begin(), offers.end(), std::back_inserter(filteredOffers), [&price](const auto& offer) {
		return offer.getPrice() <= price;
	});

	return filteredOffers;

	/*std::for_each(offers.begin(), offers.end(), [&filteredOffers, &price](const auto& offer) {
		if (offer.getPrice() <= price)
			filteredOffers.push_back(offer);
	});*/
}

std::vector<Offer> Service::sortByName() const {
	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		return offer1.getName() <= offer2.getName();
	});

	return copyOffers;

	/*copyOffers.sort([](const auto& offer1, const auto& offer2) {
		return offer1.getName() <= offer2.getName();
	});*/
}

std::vector<Offer> Service::sortByDestination() const {

	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		return offer1.getDestination() < offer2.getDestination();
	});

	return copyOffers;

	/*copyOffers.sort([](const auto& offer1, const auto& offer2) {
		return offer1.getDestination() <= offer2.getDestination();
	});*/
}

std::vector<Offer> Service::sortByTypeAndPrice() const {
	const std::vector<Offer>& offers = this->repository.getAll();
	std::vector<Offer> copyOffers = offers;

	std::sort(copyOffers.begin(), copyOffers.end(), [](const auto& offer1, const auto& offer2) {
		if (offer1.getType() != offer2.getType()) {
			return offer1.getType() <= offer2.getType();
		}
		return offer1.getPrice() >= offer2.getPrice();
	});

	return copyOffers;

	/*copyOffers.sort([](const auto& offer1, const auto& offer2) {
		if (offer1.getType() != offer2.getType()) {
			return offer1.getType() <= offer2.getType();
		}
		return offer1.getPrice() >= offer2.getPrice();
	});*/
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
}

void Service::redo() {
	if (undoIndex == undoList.size() - 1) {
		throw ValidException("Nu se mai poate face redo!!!");
	}
	undoList.at(undoIndex + 1)->doRedo();
	undoIndex++;
}

void Service::exportWishlistCSV(std::string saveName) const {
	wishlist.exportCSV(saveName);
}