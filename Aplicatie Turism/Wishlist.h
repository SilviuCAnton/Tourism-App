#pragma once
#include "Domain.h"
#include <vector>

class Wishlist : public Observable {
private:
	std::vector<Offer> items;
public:
	//Default constructor
	Wishlist() = default;

	//Copy = destructor (rule of three)
	~Wishlist() = default;

	//Copy constructor (rule of three)
	Wishlist(const Wishlist&);

	//Copy = operator overload (rule of three)
	Wishlist& operator=(const Wishlist&);

	//Operator == overload
	bool operator==(const Wishlist&);

	//Adds an offer to the wishlist
	void addToWishlist(const Offer&);

	//Empties the wishlist
	void emptyWishlist() noexcept;

	void removeFromWishlist(Offer of);

	//Populates the wishlist with a number of random offers from a given list of offers
	void populateWishlist(int, std::vector<Offer>);

	//Returns a list of all the offers in the wishlist
	const std::vector<Offer>& getAll() const noexcept;

	//Returns size of wishlist
	const int getSize() const noexcept;

	//Exports wishlist as CSV file
	void exportCSV(std::string saveName) const;
};

