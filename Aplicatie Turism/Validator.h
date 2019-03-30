#pragma once
#include "Domain.h"

//Module for entity validators

class OfferValidator {
public:
	/*
	Description: validates an offer

	In:
		- offer - the offer to be validated

	Exceptions:
		- throws ValidException if the offer is not valid
	*/
	void validate(const Offer&) const;
};