#include "Domain.h"

Offer::Offer(std::string name, std::string destination, std::string type, double price) : id{++nextId}, name{ name }, destination{ destination }, type{ type }, price{ price } {
}

int Offer::nextId{ 0 };

int Offer::getId() const {
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

double Offer::getPrice() const {
	return price;
}

void Offer::setName(std::string name) {
	this->name = name;
}

void Offer::setDestination(std::string destination) {
	this->destination = destination;
}

void Offer::setType(std::string type) {
	this->type = type;
}

void Offer::setPrice(double price) {
	this->price = price;
}