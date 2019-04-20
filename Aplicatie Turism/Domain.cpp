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

void Offer::setId(int id) noexcept{
	this->id = id;
}

std::string Offer::getName() const{
	return name;
}

void Offer::setName(std::string name) {
	this->name = name;
}

std::string Offer::getDestination() const {
	return destination;
}

void Offer::setDestination(std::string destination) {
	this->destination = destination;
}

std::string Offer::getType() const {
	return type;
}

void Offer::setType(std::string type) {
	this->type = type;
}

double Offer::getPrice() const noexcept {
	return price;
}

void Offer::setPrice(double price) noexcept{
	this->price = price;
}

bool Offer::operator==(const Offer& otherOffer) const noexcept {
	return name == otherOffer.name && type == otherOffer.type && destination == otherOffer.destination;
}

std::ostream& operator<<(std::ostream& out, const Offer& offer) {
	out << offer.getId() << " " << offer.getName() << " " << offer.getDestination() << " " << offer.getType() << " " << offer.getPrice();
	return out;
}

std::istream & operator>>(std::istream & in, Offer & offer) {
	int id{ 0 };
	std::string name;
	std::string destination;
	std::string type;
	double price{ 0 };
	in >> id >> name >> destination >> type >> price;
	offer.setId(id);
	offer.setName(name);
	offer.setDestination(destination);
	offer.setType(type);
	offer.setPrice(price);
	return in;
}
