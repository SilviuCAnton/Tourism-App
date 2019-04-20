#pragma once
#include <vector>
#include "Domain.h"
#include "MyList.h"

//Module for data storage

class Repository {
private:
	std::vector<Offer> items;
public:
	/*
	Description: repository constructor

	Out:
		- Repository - the generated repository
	*/
	Repository() = default;

	//Description: repository destructor
	virtual ~Repository() = default;

	/*
	Description: stores an offer into the repository

	In:
		- offer - the offer to store
	*/
	virtual void store(const Offer&);

	/*
	Description: deletes an offer from the repository

	In:
		- name - name of the offer
		- type - type of the offer

	Exceptions:
		- throws InexistentItemException if the offer does not exist
	*/
	virtual void deleteElement(int);

	/*
	Description: returns a copy of the list of all the offers inside the repository

	Out:
		- offers - the offer list
	*/
	const std::vector<Offer>& getAll() const noexcept;

	/*
	Description: updates an offer in the repository

	In:
		- offer - an offer with the id of the offer we want to update
	*/
	virtual void update(const Offer&);

	/*
	Description: returns the maximum id used already for an offer in the repository

	Out:
		- maxID - the max id used
	*/
	int getMaxId() const noexcept;
};

class FileRepository : public Repository {
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