#pragma once
#include "Repository.h"
#include "Domain.h"
#include "Validator.h"

//Module for the main functionalities of the app (GRASP Controller)

class Service {
private:
	Repository repository;
	OfferValidator validator;
public:
	/*
	Description: service constructor
	*/
	Service(const Repository&, const OfferValidator&);

	/*
	Description: adds an offer given a name, a destination, a type and a price

	In:
		- name - name of the offer
		- destination - the destination of the trip
		- type - the type of the offer
		- price - the money cost

	Exceptions:
		- throws DuplicateItemException if the offer already exists
		- throws ValidException if the offer is not valid
	*/
	void addOffer(std::string, std::string, std::string, double);

	/*
	Description: modifies an offer given the id of the offer, the new name, the new destination, the new type and the new price

	In:
		- id - the id of the offer
		- name - name of the offer
		- destination - the destination of the trip
		- type - the type of the offer
		- price - the money cost

	Exceptions:
		- throws DuplicateItemException if the offer already exists
		- throws ValidException if the offer is not valid
	*/
	void modifyOffer(int, std::string, std::string, std::string, double);

	/*
	Description: removes an offer given the id of the offer

	In:
		- id - the id of the of the offer
	*/
	void removeOffer(int);

	/*
	Description: returns a list of all the offers

	Out: 
		- offers - offer list
	*/
	const List<Offer>& getAllOffers() const;

	/*
	Description: finds all the offers with names mactching a sequence of characters 

	In: 
		- sequence - sequence of characters
	*/
	List<Offer> findByName(std::string) const;

	/*
	Description: filters the offers by destination

	In:
		- destination - the destination to filter by
	*/
	List<Offer> filterByDestination(std::string) const;

	/*
	Description: filters the offers by price

	In:
		- price - the price to filter by
	*/
	List<Offer> filterByPrice(double) const;

	/*
	Description: sorts the offers by name
	*/
	List<Offer> sortByName() const;

	/*
	Description: sorts the offers by destination
	*/
	List<Offer> sortByDestination() const;

	/*
	Description: sorts the offers by type and price
	*/
	List<Offer> sortByTypeAndPrice() const;
};