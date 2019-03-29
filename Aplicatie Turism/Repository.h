#pragma once
#include <vector>
#include "Domain.h"

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

	/*
	Description: stores an offer into the repository

	In:
		- offer - the offer to store
	*/
	void store(const Offer&);

	/*
	Description: deletes an offer from the repository

	In:
		- name - name of the offer
		- type - type of the offer
	*/
	void deleteElement(int);

	/*
	Description: returns the size of the repository

	Out:
		- size - the size of the repo
	*/
	int size() const;

	/*
	Description: returns a list of all the offers inside the repository

	Out:
		- offers - the offer list
	*/
	std::vector<Offer> getAll() const;

	/*
	Description: returns an offer from the repo, given an id

	In:
		- id - id of the offer we want

	Out:
		- offer - the returned offer
	*/
	Offer getElement(int) const;

	/*
	Description: updates an offer in the repository

	In:
		- offer - an offer with the id of the offer we want to update
	*/
	void update(const Offer&);
};