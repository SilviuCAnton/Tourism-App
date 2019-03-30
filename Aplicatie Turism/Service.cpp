#include "Service.h"
#include "Exceptions.h"

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
	for (auto offer : offers) {
		if (offer.getName().find(sequence) != std::string::npos) {
			filteredOffers.push_back(offer);
		}
	}
	return filteredOffers;
}

std::vector<Offer> Service::filterByDestination(std::string destination) const {
	std::vector<Offer> filteredOffers;

	std::vector<Offer> offers = this->repository.getAll();
	for (auto offer : offers) {
		if (offer.getDestination() == destination) {
			filteredOffers.push_back(offer);
		}
	}
	return filteredOffers;
}

std::vector<Offer> Service::filterByPrice(double price) const {
	std::vector<Offer> filteredOffers;

	std::vector<Offer> offers = this->repository.getAll();
	for (auto offer : offers) {
		if (offer.getPrice() <= price) {
			filteredOffers.push_back(offer);
		}
	}
	return filteredOffers;
}