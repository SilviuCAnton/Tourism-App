#pragma once
#include "Repository.h"
#include "Domain.h"
#include "Validator.h"
#include "Wishlist.h"

//Module for the main functionalities of the app (GRASP Controller)

class Service {
private:
	Repository repository;
	OfferValidator validator;
	Wishlist wishlist;
public:
	/*
	Description: service constructor
	*/
	Service(const Repository&, const OfferValidator&, const Wishlist&);

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
	const std::vector<Offer>& getAllOffers() const noexcept;

	/*
	Description: finds all the offers with names mactching a sequence of characters 

	In: 
		- sequence - sequence of characters
	*/
	std::vector<Offer> findByName(std::string) const;

	/*
	Description: filters the offers by destination

	In:
		- destination - the destination to filter by
	*/
	std::vector<Offer> filterByDestination(std::string) const;

	/*
	Description: filters the offers by price

	In:
		- price - the price to filter by
	*/
	std::vector<Offer> filterByPrice(double) const;

	/*
	Description: sorts the offers by name
	*/
	std::vector<Offer> sortByName() const;

	/*
	Description: sorts the offers by destination
	*/
	std::vector<Offer> sortByDestination() const;

	/*
	Description: sorts the offers by type and price
	*/
	std::vector<Offer> sortByTypeAndPrice() const;

	/*
	Description: adds an offer to wishlist, given an offer id
	*/
	void addToWishlist(int);

	/*
	Description: empties the wishlist
	*/
	void emptyWishlist() noexcept;

	/*
	Description: populates the wishlist with a number of random offers
	*/
	void populateWishlist(int);

	/*
	Description: returns a list of all the offers in the wishlist

	Out:
		- wishlist - offer list
	*/
	const std::vector<Offer>& getWishlist() const noexcept;

	//Description: returns the size of the wishlist
	const int getWishlistSize() const;
};