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

	//Copy Constructor
	Offer(const Offer& ot);

	//Asignment operator overload
	Offer& operator=(const Offer& ot);

	//Destructor
	~Offer() = default;

	/*
	Description: getter for the id

	Out:
		- id - returns the id of the offer
	*/
	int getId() const noexcept;

	/*
	Description: setter for the id

	Out:
		- id - sets the id of the offer
	*/
	void setId(int) noexcept;

	/*
	Description: getter for the name

	Out:
		- name - returns the name of the offer
	*/
	std::string getName() const;

	/*
	Description: setter for the name

	Out:
		- name - sets the name of the offer
	*/
	void setName(std::string);

	/*
	Description: getter for the destination

	Out:
		- destination - returns the destination of the offer
	*/
	std::string getDestination() const;

	/*
	Description: setter for the destination

	Out:
		- destination - sets the destination of the offer
	*/
	void setDestination(std::string);

	/*
	Description: getter for the type

	Out:
		- type - returns the type of the offer
	*/
	std::string getType() const;

	/*
	Description: setter for the type

	Out:
		- type - sets the type of the offer
	*/
	void setType(std::string);

	/*
	Description: getter for the price

	Out:
		- price - returns the price of the offer
	*/
	double getPrice() const noexcept;

	/*
	Description: setter for the price

	Out:
		- price - sets the price of the offer
	*/
	void setPrice(double) noexcept;

	/*
	Description: == operator overload

	Out: returns true if 2 offers are considered equal(name, destination and type are the same);
	*/
	bool operator==(const Offer&) const noexcept;

	//Print representation
	friend std::ostream& operator<<(std::ostream& out, const Offer& offer);

	//Read representation
	friend std::istream& operator>>(std::istream& in, Offer& offer);
};

class TypeCountDTO {
private:
	std::string type;
	int count;
public:
	TypeCountDTO(std::string newtype, int newcount) {
		type = newtype;
		count = newcount;
	}

	std::string getType() const {
		return type;
	}

	int getCount() const noexcept{
		return count;
	}
};