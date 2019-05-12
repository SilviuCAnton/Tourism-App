#include "StatisticsGUI.h"
#include <qboxlayout.h>
#include <sstream>
#include <qheaderview.h>

StatisticsGUI::StatisticsGUI(std::vector<TypeCountDTO> items) : items { items } {
	buildGUI(items);
	loadTable(items);
	connectSignalsAndSlots();
}

void StatisticsGUI::buildGUI(std::vector<TypeCountDTO> items) {
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
	QVBoxLayout* layout = new QVBoxLayout;
	QStringList myStringList;
	myStringList.append("Type");
	myStringList.append("Count");
	setLayout(layout);
	table->setRowCount(items.size());
	table->setColumnCount(2);
	table->setHorizontalHeaderLabels(myStringList);
	layout->addWidget(table);
	layout->addWidget(okButton);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
}

void StatisticsGUI::loadTable(std::vector<TypeCountDTO> items) {
	int i = 0;
	for (const auto& item : items) {
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(item.getType())));
		std::stringstream ss{};
		ss << item.getCount();
		item.getCount();
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
		i++;
	}
}

void StatisticsGUI::connectSignalsAndSlots() {
	QObject::connect(okButton, &QPushButton::clicked, [&]() {
		this->close();
	});
}
