#include "Wishlist.h"
#include <random>
#include <chrono>
#include "Exceptions.h"
#include <fstream>

Wishlist::Wishlist(const Wishlist& other) : Observable(), items{ other.items } {
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
	if (items.size() != other.getSize()) {
		return false;
	}

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
	notifyObservers();
}

void Wishlist::emptyWishlist() noexcept {
	items.clear();
	notifyObservers();
}

void Wishlist::removeFromWishlist(Offer of) {
	auto it = std::find(items.begin(), items.end(), of);
	if (it != items.end()) {
		items.erase(it);
	}
}

void Wishlist::populateWishlist(int number, std::vector<Offer> offers) {
	if (number > offers.size()) {
		number = offers.size();
	}
	items.clear();
	const unsigned int seed{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::shuffle(offers.begin(), offers.end(), std::default_random_engine(seed));
	std::copy(offers.begin(), offers.begin() + number, std::back_inserter(items));
	notifyObservers();
}

const std::vector<Offer>& Wishlist::getAll() const noexcept {
	return items;
}

const int Wishlist::getSize() const noexcept {
	return items.size();
}

void Wishlist::exportCSV(std::string saveName) const {
	if (items.size() == 0) {
		throw InexistentItemException("Wishlistul este gol!!!");
	}
	saveName = saveName + ".csv";
	std::ofstream f(saveName);
	for (const auto& offer : items) {
		f << offer << std::endl;
	}
	f.close();
}