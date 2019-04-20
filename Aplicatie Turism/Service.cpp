#include "Service.h"
#include "Exceptions.h"
#include <algorithm>

Service::Service(Repository& repository, const OfferValidator& validator, const Wishlist&) : repository{ repository }, validator{ validator }, wishlist{ wishlist } {
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
}

void Service::modifyOffer(int id, std::string name, std::string destination, std::string type, double price) {
	Offer newOffer{ id, name, destination, type, price };

	this->validator.validate(newOffer);

	const std::vector<Offer>& offers = this->repository.getAll();
	for (const auto& offer : offers) {
		if (offer == newOffer) {
			throw DuplicateItemException("Oferta exista deja!!!");
		}
	}
	
	this->repository.update(newOffer);
}

void Service::removeOffer(int id) {
	this->repository.deleteElement(id);
}

const std::vector<Offer>& Service::getAllOffers() const noexcept {
	return this->repository.getAll();
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

	std::for_each(getAllOffers().begin(), getAllOffers().end(), [&statistic](const auto& offer) {
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
