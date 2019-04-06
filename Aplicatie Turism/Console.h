#pragma once
#include "Service.h"

class Console {
private:
	Service service;
	void printList(const List<Offer>&) const;
	void printResultList(const List<Offer>& offers) const;
	void displayMenu() const;
	void addOfferUI();
	void modifyOfferUI();
	void removeOfferUI();
	void findByNameUI() const;
	void filterByDestinationUI() const;
	void filterByPriceUI() const;
	void sortByNameUI() const;
	void sortByDestinationUI() const;
	void sortByTypeAndPriceUI() const;
public:
	Console(const Service&);
	void run();
};