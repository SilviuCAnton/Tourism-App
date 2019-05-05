#pragma once
#include <qstring.h>
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

class WishlistGUI : public QWidget {
public:
	WishlistGUI(Service& service);
	void loadList(std::vector<Offer>);

private:
	Service& service;
	void buildGUI();
	void reloadList(std::vector<Offer>);
	void connectSignalsAndSlots();

	//List
	QListWidget* offerList = new QListWidget;
	QListWidget* wishList = new QListWidget;

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

