#pragma once
#include "Repository.h"
#include "Domain.h"

//Module for the main functionalities of the app (GRASP Controller)

class Service {
private:
	Repository repository;
public:
	void addOffer(std::string, std::string, std::string, double);
	void modifyOffer(int, std::string, std::string, std::string, double);
	void removeOffer(int);
	std::vector<Offer> getAllOffers();
	std::vector<Offer> findByName(std::string);
	std::vector<Offer> filterByDestination(std::string);
	std::vector<Offer> filterByPrice(double);
	std::vector<Offer> sortByName();
	std::vector<Offer> sortByDestination();
	std::vector<Offer> sortByTypeAndPrice();
};