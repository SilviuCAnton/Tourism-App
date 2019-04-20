#include "Repository.h"
#include <iterator>
#include <fstream>
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

void FileRepository::storeToFile() {
	std::ofstream f(fileName);
	f.clear();
	const std::vector<Offer>& offers = Repository::getAll();
	for (const auto& offer : offers) {
		f << offer << std::endl;
	}
	f.close();
}

void FileRepository::readFromFile() {
	std::ifstream f(fileName);
	Offer off{ 0,"","","",0 };
	while (f >> off) {
		Repository::store(off);
	}
	f.close();
}

FileRepository::FileRepository(std::string fileName) : fileName{ fileName } {
	readFromFile();
}

void FileRepository::store(const Offer& offer) {
	Repository::store(offer);
	storeToFile();
}

void FileRepository::deleteElement(int id) {
	Repository::deleteElement(id);
	storeToFile();
}

void FileRepository::update(const Offer& offer) {
	Repository::update(offer);
	storeToFile();
}

void FileRepository::emptyRepo() {
	std::ofstream f(fileName);
	f.clear();
	f.close();
}
