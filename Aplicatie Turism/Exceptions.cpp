#include "Exceptions.h"

std::ostream& operator<<(std::ostream& out, const ValidException& err) {
	out << err.message;
	return out;
}

std::ostream& operator<<(std::ostream& out, const DuplicateItemException& err) {
	out << err.message;
	return out;
}

std::ostream& operator<<(std::ostream& out, const InexistentItemException& err) {
	out << err.message;
	return out;
}