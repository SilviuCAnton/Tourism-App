#include "Repository.h"
#include <iterator>
#include <fstream>
#include <random>
#include "Exceptions.h"
#include <algorithm>

void MemoryRepository::store(const Offer& offer) {
	items.push_back(offer);
}

void MemoryRepository::deleteElement(int id) {
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

const std::vector<Offer>& MemoryRepository::getAll() const noexcept {
	return items;
}

void MemoryRepository::update(const Offer& offer) {
	this->deleteElement(offer.getId());
	this->store(offer);
}

int MemoryRepository::getMaxId() const noexcept {
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
	const std::vector<Offer>& offers = MemoryRepository::getAll();
	for (auto offer : offers) {
		f << offer << std::endl;
	}
	f.close();
}

void FileRepository::readFromFile() {
	std::ifstream f(fileName);
	Offer off{ 0,"","","",0 };
	while (f >> off) {
		MemoryRepository::store(off);
	}
	f.close();
}

FileRepository::FileRepository(std::string fileName) : fileName{ fileName } {
	readFromFile();
}

void FileRepository::store(const Offer& offer) {
	MemoryRepository::store(offer);
	storeToFile();
}

void FileRepository::deleteElement(int id) {
	MemoryRepository::deleteElement(id);
	storeToFile();
}

void FileRepository::update(const Offer& offer) {
	MemoryRepository::update(offer);
	storeToFile();
}

void FileRepository::emptyRepo() {
	std::ofstream f(fileName);
	f.clear();
	f.close();
}

ProbabilityRepo::ProbabilityRepo(double prob) : probability { prob } {
}

void ProbabilityRepo::store(const Offer& offer) {
	const double result = static_cast<double>(std::rand()) / RAND_MAX;
	if (result < probability) {
		throw ValidException("Ghinion!!!");
	}
	items[offer.getId()] = offer;
	getAllVect.push_back(offer);
}

void ProbabilityRepo::deleteElement(int id) {
	const double result = static_cast<double>(std::rand()) / RAND_MAX;
	if (result < probability) {
		throw ValidException("Ghinion!!!");
	}
	items.erase(id);
	int index{ 0 };
	for (const auto& elem : getAllVect) {
		if (elem.getId() == id) {
			getAllVect.erase(getAllVect.begin() + index);
			index = -1;
			break;
		}
		index++;
	}
}

const std::vector<Offer>& ProbabilityRepo::getAll() const noexcept {
	return getAllVect;
}

void ProbabilityRepo::update(const Offer& offer) {
	const double result = static_cast<double>(std::rand()) / RAND_MAX;
	if (result < probability) {
		throw ValidException("Ghinion!!!");
	}
	deleteElement(offer.getId());
	store(offer);
}

int ProbabilityRepo::getMaxId() const
{
	int max{ 0 };
	std::for_each(items.begin(), items.end(), [&max](const auto& myMapPair) {
		if (max < myMapPair.first) {
			max = myMapPair.first;
		}
	});
	return max;
}
