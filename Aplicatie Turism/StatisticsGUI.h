#pragma once
#include <QtCore/qstring.h>
#include <QtWidgets/qwidget.h>
#include <Service.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

class StatisticsGUI : public QWidget {
public:
	StatisticsGUI(std::vector<TypeCountDTO> items);

private:
	std::vector<TypeCountDTO> items;
	void buildGUI(std::vector<TypeCountDTO> items);
	void loadTable(std::vector<TypeCountDTO> items);
	void connectSignalsAndSlots();

	//Table
	QTableWidget* table = new QTableWidget;

	//Buttons
	QPushButton* okButton = new QPushButton("Ok");

};

