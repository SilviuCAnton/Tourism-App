#include "Service.h"
#include "Exceptions.h"
#include <algorithm>

Service::Service(const Repository& repository, const OfferValidator& validator) : repository{ repository }, validator{ validator } {
}

void Service::addOffer(std::string name, std::string destination, std::string type, double price) {
	int newOfferId = this->repository.getMaxId() + 1;
	Offer newOffer{ newOfferId, name, destination, type, price };

	this->validator.validate(newOffer);

	std::vector<Offer> offers = this->repository.getAll();
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

	std::vector<Offer> offers = this->repository.getAll();
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

std::vector<Offer> Service::getAllOffers() const {
	return this->repository.getAll();
}

std::vector<Offer> Service::findByName(std::string sequence) const {
	std::vector<Offer> filteredOffers;
	std::vector<Offer> offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &sequence](const auto& offer) {
		if (offer.getName().find(sequence) != std::string::npos) {
			filteredOffers.push_back(offer);
		}
	});
	return filteredOffers;
}

std::vector<Offer> Service::filterByDestination(std::string destination) const {
	std::vector<Offer> filteredOffers;
	std::vector<Offer> offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &destination](const auto& offer) {
		if (offer.getDestination() == destination)
			filteredOffers.push_back(offer);
	});
	return filteredOffers;
}

std::vector<Offer> Service::filterByPrice(double price) const {
	std::vector<Offer> filteredOffers;
	std::vector<Offer> offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &price](const auto& offer) {
		if (offer.getPrice() <= price)
			filteredOffers.push_back(offer);
	});
	return filteredOffers;
}

std::vector<Offer> Service::sortByName() const {
	std::vector<Offer> offers = this->repository.getAll();

	std::sort(offers.begin(), offers.end(), [](const auto& offer1, const auto& offer2) {
		return offer1.getName() < offer2.getName();
	});
	return offers;
}

std::vector<Offer> Service::sortByDestination() const {
	std::vector<Offer> offers = this->repository.getAll();

	std::sort(offers.begin(), offers.end(), [](const auto& offer1, const auto& offer2) {
		return offer1.getDestination() < offer2.getDestination();
	});
	return offers;
}

std::vector<Offer> Service::sortByTypeAndPrice() const {
	std::vector<Offer> offers = this->repository.getAll();

	std::sort(offers.begin(), offers.end(), [](const auto& offer1, const auto& offer2) {
		if (offer1.getType() != offer2.getType()) {
			return offer1.getType() < offer2.getType();
		}
		return offer1.getPrice() > offer2.getPrice();
	});
	return offers;
}