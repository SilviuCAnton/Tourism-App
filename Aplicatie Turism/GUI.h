#pragma once
#include <Service.h>
#include "WishlistGUI.h"
#include "StatisticsGUI.h"
#include <QtWidgets>

class TableModel : public QAbstractTableModel {
private:
	std::vector<Offer> items;
	std::vector<Offer> sorted;
public:
	TableModel(const std::vector<Offer>& offers, const std::vector<Offer>& sorted);
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	int columnCount(const QModelIndex& = QModelIndex()) const override;
	int rowCount(const QModelIndex& = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

class GUI : public QWidget {
public:
	GUI(Service& serv);

private:
	Service& service;
	void buildGUI();
	//void reloadList(std::vector<Offer>);
	void reloadTable(std::vector<Offer>);
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
	QPushButton* statisticsButton = new QPushButton("TypeStatistics");
	QPushButton* readOnlyWishlistButton = new QPushButton("DrawWishlist");
	QPushButton* addToWishlistButton = new QPushButton("AddToWishlist");
	QPushButton* clearWishlistButton = new QPushButton("ClearWishlist");
	QPushButton* populateWishlistButton = new QPushButton("PopulateWishlist");

	/*List
	QListWidget* offerList = new QListWidget;*/
	QTableView* offerTable = new QTableView;
	TableModel* model;

	//Text fields
	QLineEdit* nameTextEdit = new QLineEdit;
	QLineEdit* destinationTextEdit = new QLineEdit;
	QLineEdit* typeTextEdit = new QLineEdit;
	QLineEdit* priceTextEdit = new QLineEdit;

};