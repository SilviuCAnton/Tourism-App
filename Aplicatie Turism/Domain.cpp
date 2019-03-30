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

void Offer::setName(std::string name) {
	this->name = name;
}

void Offer::setDestination(std::string destination) {
	this->destination = destination;
}

void Offer::setType(std::string type) {
	this->type = type;
}

void Offer::setPrice(double price) noexcept{
	this->price = price;
}