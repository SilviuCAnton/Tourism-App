#include "Exceptions.h"

std::ostream& operator<<(std::ostream& out, ValidException& err) {
	out << err.message;
	return out;
}

std::ostream& operator<<(std::ostream& out, DuplicateItemException& err) {
	out << err.message;
	return out;
}

std::ostream& operator<<(std::ostream& out, InexistentItemException& err) {
	out << err.message;
	return out;
}