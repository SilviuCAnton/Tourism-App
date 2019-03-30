#pragma once
#include <string>

//Module for custom exceptions

class ValidException {
private:
	std::string message;
public:
	ValidException(std::string m) : message{ m } {
	}
	friend std::ostream& operator<<(std::ostream& out, ValidException& err);
};

class DuplicateItemException {
private:
	std::string message;
public:
	DuplicateItemException(std::string m) : message{ m } {
	}
	friend std::ostream& operator<<(std::ostream& out, DuplicateItemException& err);
};

class InexistentItemException {
private:
	std::string message;
public:
	InexistentItemException(std::string m) : message{ m } {
	}
	friend std::ostream& operator<<(std::ostream& out, InexistentItemException& err);
};