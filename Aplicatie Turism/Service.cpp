#include "Service.h"
#include "Exceptions.h"
#include <algorithm>

Service::Service(const Repository& repository, const OfferValidator& validator) : repository{ repository }, validator{ validator } {
}

void Service::addOffer(std::string name, std::string destination, std::string type, double price) {
	int newOfferId = this->repository.getMaxId() + 1;
	Offer newOffer{ newOfferId, name, destination, type, price };

	this->validator.validate(newOffer);

	const List<Offer>& offers = this->repository.getAll();
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

	const List<Offer>& offers = this->repository.getAll();
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

const List<Offer>& Service::getAllOffers() const {
	return this->repository.getAll();
}

List<Offer> Service::findByName(std::string sequence) const {
	List<Offer> filteredOffers;
	const List<Offer>& offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &sequence](const auto& offer) {
		if (offer.getName().find(sequence) != std::string::npos) {
			filteredOffers.push_back(offer);
		}
	});
	return filteredOffers;
}

List<Offer> Service::filterByDestination(std::string destination) const {
	List<Offer> filteredOffers;
	const List<Offer>& offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &destination](const auto& offer) {
		if (offer.getDestination() == destination)
			filteredOffers.push_back(offer);
	});
	return filteredOffers;
}

List<Offer> Service::filterByPrice(double price) const {
	List<Offer> filteredOffers;
	const List<Offer>& offers = this->repository.getAll();

	std::for_each(offers.begin(), offers.end(), [&filteredOffers, &price](const auto& offer) {
		if (offer.getPrice() <= price)
			filteredOffers.push_back(offer);
	});
	return filteredOffers;
}

List<Offer> Service::sortByName() const {
	const List<Offer>& offers = this->repository.getAll();
	List<Offer> copyOffers = offers;

	copyOffers.sort([](const auto& offer1, const auto& offer2) {
		return offer1.getName() <= offer2.getName();
	});

	return copyOffers;
}

List<Offer> Service::sortByDestination() const {
	const List<Offer>& offers = this->repository.getAll();
	List<Offer> copyOffers = offers;

	copyOffers.sort([](const auto& offer1, const auto& offer2) {
		return offer1.getDestination() <= offer2.getDestination();
	});

	return copyOffers;
}

List<Offer> Service::sortByTypeAndPrice() const {
	const List<Offer>& offers = this->repository.getAll();
	List<Offer> copyOffers = offers;

	copyOffers.sort([](const auto& offer1, const auto& offer2) {
		if (offer1.getType() != offer2.getType()) {
			return offer1.getType() <= offer2.getType();
		}
		return offer1.getPrice() >= offer2.getPrice();
	});

	return copyOffers;
}