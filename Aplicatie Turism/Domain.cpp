#include "Domain.h"
#include <iostream>

Offer::Offer(int id, std::string name, std::string destination, std::string type, double price) : id{ id }, name{ name }, destination{ destination }, type{ type }, price{ price } {
}

Offer::Offer(const Offer& ot) : id{ ot.id }, name{ ot.name }, destination{ ot.destination }, type{ ot.type }, price{ ot.price } {
	//std::cout << "copy" << std::endl;
}

Offer & Offer::operator=(const Offer & ot)
{
	if (*this == ot) {
		return *this;
	}
	id = ot.id;
	name = ot.name;
	destination = ot.destination;
	type = ot.type;
	price = ot.price;
	return *this;
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

bool Offer::operator==(const Offer& otherOffer) const noexcept {
	return name == otherOffer.name && type == otherOffer.type && destination == otherOffer.destination;
}

std::ostream& operator<<(std::ostream& out, const Offer& offer) {
	out << offer.getId() << ". " << offer.getName() << " - " << offer.getDestination() << " - " << offer.getType() << " - " << offer.getPrice();
	return out;
}