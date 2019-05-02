#pragma once
#include <vector>
#include <map>
#include "Domain.h"
#include "MyList.h"

//Module for data storage

class Repository {
public:
	virtual void store(const Offer&) = 0;
	virtual void deleteElement(int) = 0;
	virtual void update(const Offer&) = 0;
	virtual int getMaxId() const = 0;
	virtual const std::vector<Offer>& getAll() const = 0;
	virtual ~Repository() = default;
};

class MemoryRepository : public Repository {
private:
	std::vector<Offer> items;
public:
	/*
	Description: repository constructor

	Out:
		- Repository - the generated repository
	*/
	MemoryRepository() = default;

	/*
	Description: stores an offer into the repository

	In:
		- offer - the offer to store
	*/
	virtual void store(const Offer&) override;

	/*
	Description: deletes an offer from the repository

	In:
		- name - name of the offer
		- type - type of the offer

	Exceptions:
		- throws InexistentItemException if the offer does not exist
	*/
	virtual void deleteElement(int) override;

	/*
	Description: returns a copy of the list of all the offers inside the repository

	Out:
		- offers - the offer list
	*/
	const std::vector<Offer>& getAll() const noexcept override;

	/*
	Description: updates an offer in the repository

	In:
		- offer - an offer with the id of the offer we want to update
	*/
	virtual void update(const Offer&) override;

	/*
	Description: returns the maximum id used already for an offer in the repository

	Out:
		- maxID - the max id used
	*/
	int getMaxId() const noexcept override;
};

class FileRepository : public MemoryRepository {
private:
	std::string fileName;
	void storeToFile();
	void readFromFile();
public:
	FileRepository(std::string fileName);
	void store(const Offer&) override;
	void deleteElement(int) override;
	void update(const Offer&) override;
	void emptyRepo();
};

class ProbabilityRepo : public Repository {
private:
	std::map<int, Offer> items;
	std::vector<Offer> getAllVect;
	double probability;
public:

	ProbabilityRepo(double prob);

	void store(const Offer &) override;

	void deleteElement(int) override;

	const std::vector<Offer>& getAll() const noexcept override;

	void update(const Offer &) override;

	int getMaxId() const override;

};