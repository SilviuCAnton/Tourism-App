#include "Wishlist.h"
#include <random>
#include <gsl_util.h>
#include <chrono>
#include "Exceptions.h"

Wishlist::Wishlist(const Wishlist& other) : items{ other.items } {
}

Wishlist& Wishlist::operator=(const Wishlist& other) {
	if(*this == other) {
		return *this;
	}
	items.clear();
	std::copy(other.items.begin(), other.items.end(), std::back_inserter(items));
	return *this;
}

bool Wishlist::operator==(const Wishlist& other) {
	for (unsigned int i = 0; i < items.size(); i++) {
		if (!(items.at(i) == other.items.at(i))) {
			return false;
		}
	}
	return true;
}

void Wishlist::addToWishlist(const Offer& offer) {
	for (const auto& of : items) {
		if (offer == of) {
			throw DuplicateItemException("Oferta exista deja in wishlist!!!");
		}
	}
	items.push_back(offer);
}

void Wishlist::emptyWishlist() noexcept {
	items.clear();
}

void Wishlist::populateWishlist(int number, std::vector<Offer> offers) {
	items.clear();
	const unsigned int seed{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::shuffle(offers.begin(), offers.end(), std::default_random_engine(seed));
	std::copy(offers.begin(), offers.begin() + number, std::back_inserter(items));
}

const std::vector<Offer>& Wishlist::getAll() const noexcept {
	return items;
}
