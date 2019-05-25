#pragma once
#include <QtCore/qstring.h>
#include <QtWidgets/qwidget.h>
#include <Service.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>

class WishlistGUI : public QWidget, public Observer {
public:
	WishlistGUI(Service& service);
	~WishlistGUI();
	void loadList(std::vector<Offer>);
	void update() override;

private:
	Service& service;
	void buildGUI();
	void reloadList(std::vector<Offer>);
	void connectSignalsAndSlots();

	//List
	QListView* offerList = new QListView;
	QListView* wishList = new QListView;

	//Buttons
	QPushButton* addButton = new QPushButton("Add");
	QPushButton* clearButton = new QPushButton("Clear");
	QPushButton* populateButton = new QPushButton("Populate");
	QPushButton* exportButton = new QPushButton("ExportCSV");

	//Text fields
	QLineEdit* nameTextEdit = new QLineEdit;
	QLineEdit* destinationTextEdit = new QLineEdit;
	QLineEdit* typeTextEdit = new QLineEdit;
	QLineEdit* priceTextEdit = new QLineEdit;
};

