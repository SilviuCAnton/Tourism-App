#include "Repository.h"
#include <iterator>
#include "Exceptions.h"

void Repository::store(const Offer& offer) {
	items.push_back(offer);
}

void Repository::deleteElement(int id) {
	int index{ 0 };
	for (const auto& elem : items) {
		if (elem.getId() == id) {
			items.erase(items.begin() + index);
			index = -1;
			break;
		}
		index++;
	}
	if (index == items.size()) {
		throw InexistentItemException("Elementul cu id-ul dat nu exista!!");
	}
}

const std::vector<Offer>& Repository::getAll() const noexcept {
	return items;
}

void Repository::update(const Offer& offer) {
	this->deleteElement(offer.getId());
	this->store(offer);
}

int Repository::getMaxId() const noexcept {
	int maxId = 0;
	for (const auto& item : items) {
		if (item.getId() > maxId){
			maxId = item.getId();
		}
	}
	return maxId;
}
