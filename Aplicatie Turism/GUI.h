#pragma once
#include <qwidget.h>
#include <Service.h>
#include <qthread.h>
#include <QtWidgets/qstatusbar.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
#include <QtWidgets\qspinbox.h>
#include <qtextedit.h>
#include <QLabel>
#include <qdebug.h>
#include <QTableWidget>
#include <qcolor.h>

class GUI : public QWidget {
public:
	GUI(Service& serv);

private:
	Service& service;
	void buildGUI();

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
	QTextEdit* nameTextEdit = new QTextEdit;
	QTextEdit* destinationTextEdit = new QTextEdit;
	QTextEdit* typeTextEdit = new QTextEdit;
	QTextEdit* priceTextEdit = new QTextEdit;
};

