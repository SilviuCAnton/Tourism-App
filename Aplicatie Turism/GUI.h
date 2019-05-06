#pragma once
#include <qwidget.h>
#include <Service.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <WishlistGUI.h>

class GUI : public QWidget {
public:
	GUI(Service& serv);

private:
	Service& service;
	void buildGUI();
	void reloadList(std::vector<Offer>);
	void connectSignalsAndSlots();

	//aux
	int offerId;

	//Buttons
	QPushButton* removeButton = new QPushButton("Remove");
	QPushButton* sortByNameButton = new QPushButton("SortByName");
	QPushButton* sortByDestinationButton = new QPushButton("SortByDestination");
	QPushButton* sortByTypeAndPriceButton = new QPushButton("SortByTypeAndPrice");
	QPushButton* addButton = new QPushButton("Add");
	QPushButton* modifyButton = new QPushButton("Modify");
	QPushButton* filterByNameButton = new QPushButton("FilterByName");
	QPushButton* filterByDestinationButton = new QPushButton("FilterByDestination");
	QPushButton* filterByPriceButton = new QPushButton("FilterByPrice");
	QPushButton* undoButton = new QPushButton("Undo");
	QPushButton* redoButton = new QPushButton("Redo");
	QPushButton* wishlistButton = new QPushButton("MyWishlist");

	//List
	QListWidget* offerList = new QListWidget;

	//Text fields
	QLineEdit* nameTextEdit = new QLineEdit;
	QLineEdit* destinationTextEdit = new QLineEdit;
	QLineEdit* typeTextEdit = new QLineEdit;
	QLineEdit* priceTextEdit = new QLineEdit;

	//WishlistGUI
	WishlistGUI* wishGUI = new WishlistGUI{ service };
};

