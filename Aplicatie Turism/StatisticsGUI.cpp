#include "StatisticsGUI.h"
#include <QtWidgets/qboxlayout.h>
#include <sstream>
#include <QtWidgets/qheaderview.h>

StatisticsGUI::StatisticsGUI(std::vector<TypeCountDTO> items) : items { items } {
	buildGUI();
	loadTable(items);
	connectSignalsAndSlots();
}

void StatisticsGUI::buildGUI() {
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	layout->addWidget(table);
	layout->addWidget(okButton);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	setWindowModality(Qt::ApplicationModal);
}

void StatisticsGUI::loadTable(std::vector<TypeCountDTO> items) {
	StatTableModel* model = new StatTableModel{ items };
	table->setModel(model);
}

void StatisticsGUI::connectSignalsAndSlots() {
	QObject::connect(okButton, &QPushButton::clicked, [&]() {
		this->close();
	});
}
