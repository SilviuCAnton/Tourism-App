#pragma once
#include <string>

class ValidException {
private:
	std::string message;
public:
	ValidException(std::string m) : message{ m } {
	}
	friend std::ostream& operator<<(std::ostream& out, ValidException& err);
};