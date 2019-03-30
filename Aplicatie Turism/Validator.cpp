#include "Validator.h"
#include "Exceptions.h"

void OfferValidator::validate(const Offer& offer) const {
	if (offer.getName().size() == 0) {
		throw ValidException("Nume nu poate fi vid!!!");
	}
	if (offer.getPrice() <= 0) {
		throw ValidException("Pretul nu poate fi mai mic sau egal decat 0!!!");
	}
	if (offer.getDestination().size() == 0) {
		throw ValidException("Destinatie nu poate fi vida!!!");
	}
	if (offer.getType().size() == 0) {
		throw ValidException("Tip nu poate fi vid!!!");
	}
}