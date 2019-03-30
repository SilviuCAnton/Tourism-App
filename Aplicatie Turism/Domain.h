#pragma once
#include <string>

//Module for defining the entities in the aplication

class Offer {
private:
	int id;
	std::string name;
	std::string destination;
	std::string type;
	double price;
public:
	/*
	Description: offer constructor

	In:
		- id - id of the offer
		- name - name of the offer
		- destination - trip destination
		- type - offer type
		- price - price of the offer

	Out:
		- offer - the generated offer
	*/
	Offer(int, std::string, std::string, std::string, double);

	/*
	Description: getter for the id

	Out:
		- id - returns the id of the offer
	*/
	int getId() const noexcept;

	/*
	Description: getter for the name

	Out:
		- name - returns the name of the offer
	*/
	std::string getName() const;

	/*
	Description: getter for the destination

	Out:
		- destination - returns the destination of the offer
	*/
	std::string getDestination() const;

	/*
	Description: getter for the type

	Out:
		- type - returns the type of the offer
	*/
	std::string getType() const;

	/*
	Description: getter for the price

	Out:
		- price - returns the price of the offer
	*/
	double getPrice() const noexcept;

	/*
	Description: setter for the name

	In:
		- name - sets the name of the offer
	*/
	void setName(std::string);

	/*
	Description: setter for the destination

	In:
		- destination - sets the destination of the offer
	*/
	void setDestination(std::string);

	/*
	Description: setter for the type

	In:
		- type - sets the type of the offer
	*/
	void setType(std::string);

	/*
	Description: setter for the price

	In:
		- price - sets the price of the offer
	*/
	void setPrice(double) noexcept;
};