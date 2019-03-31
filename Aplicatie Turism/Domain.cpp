#include "Domain.h"

Offer::Offer(int id, std::string name, std::string destination, std::string type, double price) : id{id}, name{ name }, destination{ destination }, type{ type }, price{ price } {
}

int Offer::getId() const noexcept {
	return id;
}

std::string Offer::getName() const{
	return name;
}

std::string Offer::getDestination() const {
	return destination;
}

std::string Offer::getType() const {
	return type;
}

double Offer::getPrice() const noexcept {
	return price;
}

void Offer::setName(std::string newName) {
	this->name = newName;
}

void Offer::setDestination(std::string newDestination) {
	this->destination = newDestination;
}

void Offer::setType(std::string newType) {
	this->type = newType;
}

void Offer::setPrice(double newPrice) noexcept{
	this->price = newPrice;
}

bool Offer::operator==(const Offer& otherOffer) const {
	return name == otherOffer.name && type == otherOffer.type && destination == otherOffer.destination;
}

std::ostream& operator<<(std::ostream& out, const Offer& offer) {
	out << offer.getId() << ' ' << offer.getName() << ' ' << offer.getDestination() << ' ' << offer.getType() << ' ' << offer.getPrice();
	return out;
}