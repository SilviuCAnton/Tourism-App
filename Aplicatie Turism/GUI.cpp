#include "GUI.h"
#include "Exceptions.h"
#include <QtWidgets//qerrormessage.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qinputdialog.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <sstream>
#include <QtGui/qcolor.h>
#include <StatisticsGUI.h>
#include <QtWidgets/qmessagebox.h>
#include <QtCore/qstringlist.h>

GUI::GUI(Service& serv) : service{ serv } {
	buildGUI();
	connectSignalsAndSlots();
	reloadTable(service.getAllOffers());
}

void GUI::buildGUI() {
	QHBoxLayout* horziontalLayout = new QHBoxLayout;
	QVBoxLayout* leftVerticalLayout = new QVBoxLayout;
	QHBoxLayout* leftHorziontalLayout = new QHBoxLayout;
	QVBoxLayout* rightVerticalLayout = new QVBoxLayout;
	QVBoxLayout* labelVerticalLayout = new QVBoxLayout;
	QVBoxLayout* textBoxVerticalLayout = new QVBoxLayout;
	QHBoxLayout* detailsHorizontalLayout = new QHBoxLayout;
	QHBoxLayout* topActionsLayout = new QHBoxLayout;
	QHBoxLayout* bottomActionsLayout = new QHBoxLayout;
	QVBoxLayout* actionsLayout = new QVBoxLayout;
	QHBoxLayout* topRightLayout = new QHBoxLayout;
	setLayout(horziontalLayout);

	//Left side - button list
	QWidget* leftButtonList = new QWidget;
	leftButtonList->setLayout(leftHorziontalLayout);
	leftHorziontalLayout->addWidget(removeButton);
	removeButton->setDisabled(true);
	leftHorziontalLayout->addWidget(sortByNameButton);
	leftHorziontalLayout->addWidget(sortByDestinationButton);
	leftHorziontalLayout->addWidget(sortByTypeAndPriceButton);

	//Left side
	QWidget* left = new QWidget;
	left->setLayout(leftVerticalLayout);
	leftVerticalLayout->addWidget(offerTable);
	leftVerticalLayout->addWidget(leftButtonList);

	//Details - labels
	QWidget* labels = new QWidget;
	labels->setLayout(labelVerticalLayout);
	QLabel* nameLabel = new QLabel("Name:");
	QLabel* destinationLabel = new QLabel("Destination:");
	QLabel* typeLabel = new QLabel("Type:");
	QLabel* priceLabel = new QLabel("Price:");
	labelVerticalLayout->addWidget(nameLabel);
	labelVerticalLayout->addWidget(destinationLabel);
	labelVerticalLayout->addWidget(typeLabel);
	labelVerticalLayout->addWidget(priceLabel);

	//Details - textFields
	QWidget* textFields = new QWidget;
	textFields->setLayout(textBoxVerticalLayout);
	textBoxVerticalLayout->addWidget(nameTextEdit);
	textBoxVerticalLayout->addWidget(destinationTextEdit);
	textBoxVerticalLayout->addWidget(typeTextEdit);
	textBoxVerticalLayout->addWidget(priceTextEdit);
	nameTextEdit->setDisabled(true);
	destinationTextEdit->setDisabled(true);
	typeTextEdit->setDisabled(true);
	priceTextEdit->setDisabled(true);
	nameTextEdit->setAlignment(Qt::AlignCenter);
	destinationTextEdit->setAlignment(Qt::AlignCenter);
	typeTextEdit->setAlignment(Qt::AlignCenter);
	priceTextEdit->setAlignment(Qt::AlignCenter);

	//Details
	QWidget* details = new QWidget;
	details->setLayout(detailsHorizontalLayout);
	detailsHorizontalLayout->addWidget(labels);
	detailsHorizontalLayout->addWidget(textFields);

	//Actions - top
	QWidget* topActions = new QWidget;
	topActions->setLayout(topActionsLayout);
	topActionsLayout->addWidget(addButton);
	topActionsLayout->addWidget(modifyButton);
	modifyButton->setDisabled(true);

	//Actions - bottom
	QWidget* bottomActions = new QWidget;
	bottomActions->setLayout(bottomActionsLayout);
	bottomActionsLayout->addWidget(filterByNameButton);
	bottomActionsLayout->addWidget(filterByDestinationButton);
	bottomActionsLayout->addWidget(filterByPriceButton);

	//Actions
	QWidget* actions = new QWidget;
	actions->setLayout(actionsLayout);
	actionsLayout->addWidget(topActions);
	actionsLayout->addWidget(bottomActions);

	//Top Right Options
	QWidget* topRight = new QWidget;
	topRight->setLayout(topRightLayout);
	topRightLayout->addWidget(undoButton);
	topRightLayout->addWidget(redoButton);
	topRightLayout->addWidget(statisticsButton);
	topRightLayout->addStretch();
	topRightLayout->addWidget(wishlistButton);

	//Right side
	QWidget* right = new QWidget;
	right->setLayout(rightVerticalLayout);
	rightVerticalLayout->addWidget(topRight);
	rightVerticalLayout->addWidget(details);
	rightVerticalLayout->addWidget(actions);

	//List setup
	//offerList->setSelectionMode(QAbstractItemView::SingleSelection);

	//Table setup
	offerTable->setSelectionMode(QAbstractItemView::SingleSelection);
	offerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	offerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//Main panel
	horziontalLayout->addWidget(left);
	horziontalLayout->addWidget(right);
	
}

//void GUI::reloadList(std::vector<Offer> offers) {
//	offerList->clear();
//	std::vector<Offer> sorted = service.sortByTypeAndPrice();
//
//	for (const auto& offer : offers) {
//		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName()), offerList);
//		item->setData(Qt::UserRole, offer.getId());
//		int len = sorted.size();
//		for (int i = 0; i < sorted.size(); i++) {
//			if (sorted.at(i) == offer) {
//				if ((double)i / len < 0.33) {
//					item->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
//				}
//				else if ((double)i / len < 0.66) {
//					item->setBackground(QBrush(Qt::green, Qt::SolidPattern));
//				}
//				else {
//					item->setBackground(QBrush(Qt::red, Qt::SolidPattern));
//				}
//				break;
//			}
//		}
//	}
//}

void GUI::reloadTable(std::vector<Offer> offers) {
	offerTable->clear();
	std::vector<Offer> sorted = service.sortByTypeAndPrice();
	offerTable->setRowCount(offers.size());
	offerTable->setColumnCount(5);
	QStringList myStringList;
	myStringList.append("Name");
	myStringList.append("Destination");
	myStringList.append("Type");
	myStringList.append("Price");
	myStringList.append("TypeCount");
	offerTable->setHorizontalHeaderLabels(myStringList);
	std::vector<TypeCountDTO> vct = service.typeStatistic();
	int row{ 0 };

	for (const auto& offer : offers) {
		int count{ 0 };
		for (const auto& dto : vct) {
			if (dto.getType() == offer.getType()) {
				count = dto.getCount();
			}
		}

		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(offer.getName()));
		name->setData(Qt::UserRole, offer.getId());
		QTableWidgetItem* destination = new QTableWidgetItem(QString::fromStdString(offer.getDestination()));
		QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(offer.getType()));
		QTableWidgetItem* price = new QTableWidgetItem(QString::number(offer.getPrice()));
		QTableWidgetItem* typeCount = new QTableWidgetItem(QString::number(count));

		int len = sorted.size();
		for (int i = 0; i < sorted.size(); i++) {
			if (sorted.at(i) == offer) {
				if ((double)i / len < 0.33) {
					name->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
					destination->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
					type->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
					price->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
					typeCount->setBackground(QBrush(Qt::blue, Qt::SolidPattern));
				}
				else if ((double)i / len < 0.66) {
					name->setBackground(QBrush(Qt::green, Qt::SolidPattern));
					destination->setBackground(QBrush(Qt::green, Qt::SolidPattern));
					type->setBackground(QBrush(Qt::green, Qt::SolidPattern));
					price->setBackground(QBrush(Qt::green, Qt::SolidPattern));
					typeCount->setBackground(QBrush(Qt::green, Qt::SolidPattern));
				}
				else {
					name->setBackground(QBrush(Qt::red, Qt::SolidPattern));
					destination->setBackground(QBrush(Qt::red, Qt::SolidPattern));
					type->setBackground(QBrush(Qt::red, Qt::SolidPattern));
					price->setBackground(QBrush(Qt::red, Qt::SolidPattern));
					typeCount->setBackground(QBrush(Qt::red, Qt::SolidPattern));
				}
				break;
			}
		}

		offerTable->setItem(row, 0, name);
		offerTable->setItem(row, 1, destination);
		offerTable->setItem(row, 2, type);
		offerTable->setItem(row, 3, price);
		offerTable->setItem(row, 4, typeCount);
		row++;
	}
}

void GUI::connectSignalsAndSlots() {
	/*QObject::connect(offerList, &QListWidget::itemSelectionChanged, [&]() {
		if (!offerList->selectedItems().isEmpty()) {
			removeButton->setEnabled(true);
			modifyButton->setEnabled(true);
			const Offer& myOffer{ service.findById(offerList->selectedItems().first()->data(Qt::UserRole).toInt()) };
			nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
			destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
			typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
			std::stringstream ss{};
			ss << myOffer.getPrice();
			priceTextEdit->setText(QString::fromStdString(ss.str()));
		}
		else {
			removeButton->setDisabled(true);
			modifyButton->setDisabled(true);
			nameTextEdit->clear();
			destinationTextEdit->clear();
			typeTextEdit->clear();
			priceTextEdit->clear();
		}
	});*/

	QObject::connect(offerTable, &QTableWidget::itemSelectionChanged, [&]() {
		if (!offerTable->selectedItems().isEmpty()) {
			removeButton->setEnabled(true);
			modifyButton->setEnabled(true);
			const Offer& myOffer{ service.findById(offerTable->selectedItems().first()->data(Qt::UserRole).toInt()) };
			nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
			destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
			typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
			std::stringstream ss{};
			ss << myOffer.getPrice();
			priceTextEdit->setText(QString::fromStdString(ss.str()));
		}
		else {
			removeButton->setDisabled(true);
			modifyButton->setDisabled(true);
			nameTextEdit->clear();
			destinationTextEdit->clear();
			typeTextEdit->clear();
			priceTextEdit->clear();
		}
	});

	QObject::connect(sortByNameButton, &QPushButton::clicked, [&]() {
		offerTable->clearSelection();
		//offerList->clearSelection();
		//reloadList(service.sortByName());
		reloadTable(service.sortByName());

	});

	QObject::connect(sortByDestinationButton, &QPushButton::clicked, [&]() {
		offerTable->clearSelection();
		reloadTable(service.sortByDestination());
		//offerList->clearSelection();
		//reloadList(service.sortByDestination());
	});

	QObject::connect(sortByTypeAndPriceButton, &QPushButton::clicked, [&]() {
		/*offerList->clearSelection();
		reloadList(service.sortByTypeAndPrice());*/
		offerTable->clearSelection();
		reloadTable(service.sortByTypeAndPrice());
	});

	QObject::connect(removeButton, &QPushButton::clicked, [&]() {
		offerId = offerTable->selectedItems().first()->data(Qt::UserRole).toInt();
		//offerList->clearSelection();
		offerTable->clearSelection();
		service.removeOffer(offerId);
		//reloadList(service.getAllOffers());
		reloadTable(service.getAllOffers());

	});

	QObject::connect(wishlistButton, &QPushButton::clicked, [&]() {
		wishGUI->loadList(service.getAllOffers());
		wishGUI->show();
	});

	QObject::connect(statisticsButton, &QPushButton::clicked, [&]() {
		StatisticsGUI* statGUI = new StatisticsGUI(service.typeStatistic());
		statGUI->show();
	});

	QObject::connect(addButton, &QPushButton::clicked, [&]() {
		if (addButton->text() == "Add") {
			addButton->setText("Ok");
			nameTextEdit->clear();
			nameTextEdit->setEnabled(true);
			destinationTextEdit->clear();
			destinationTextEdit->setEnabled(true);
			typeTextEdit->clear();
			typeTextEdit->setEnabled(true);
			priceTextEdit->clear();
			priceTextEdit->setEnabled(true);

			modifyButton->setDisabled(true);
			filterByNameButton->setDisabled(true);
			filterByDestinationButton->setDisabled(true);
			filterByPriceButton->setDisabled(true);
			undoButton->setDisabled(true);
			redoButton->setDisabled(true);
			wishlistButton->setDisabled(true);
			removeButton->setDisabled(true);
			sortByNameButton->setDisabled(true);
			sortByDestinationButton->setDisabled(true);
			sortByTypeAndPriceButton->setDisabled(true);
		}
		else {
			modifyButton->setEnabled(true);
			filterByNameButton->setEnabled(true);
			filterByDestinationButton->setEnabled(true);
			filterByPriceButton->setEnabled(true);
			undoButton->setEnabled(true);
			redoButton->setEnabled(true);
			wishlistButton->setEnabled(true);
			removeButton->setEnabled(true);
			sortByNameButton->setEnabled(true);
			sortByDestinationButton->setEnabled(true);
			sortByTypeAndPriceButton->setEnabled(true);

			try {
				std::string name = nameTextEdit->text().toStdString();
				std::string destination = destinationTextEdit->text().toStdString();
				std::string type = typeTextEdit->text().toStdString();
				double price = priceTextEdit->text().toDouble();

				service.addOffer(name, destination, type, price);
				//offerList->clearSelection();
				//reloadList(service.getAllOffers());
				offerTable->clearSelection();
				reloadTable(service.getAllOffers());
			}
			catch (DuplicateItemException& die) {
				std::stringstream ss{};
				ss << die;
				QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
			}
			catch (ValidException& ve) {
				std::stringstream ss{};
				ss << ve;
				QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
			}

			addButton->setText("Add");
			nameTextEdit->clear();
			nameTextEdit->setDisabled(true);
			destinationTextEdit->clear();
			destinationTextEdit->setDisabled(true);
			typeTextEdit->clear();
			typeTextEdit->setDisabled(true);
			priceTextEdit->clear();
			priceTextEdit->setDisabled(true);
		}
	});

	QObject::connect(modifyButton, &QPushButton::clicked, [&]() {
		if (modifyButton->text() == "Modify") {
			offerId = offerTable->selectedItems().first()->data(Qt::UserRole).toInt();
			modifyButton->setText("Ok");
			nameTextEdit->setEnabled(true);
			destinationTextEdit->setEnabled(true);
			typeTextEdit->setEnabled(true);
			priceTextEdit->setEnabled(true);

			addButton->setDisabled(true);
			filterByNameButton->setDisabled(true);
			filterByDestinationButton->setDisabled(true);
			filterByPriceButton->setDisabled(true);
			undoButton->setDisabled(true);
			redoButton->setDisabled(true);
			wishlistButton->setDisabled(true);
			removeButton->setDisabled(true);
			sortByNameButton->setDisabled(true);
			sortByDestinationButton->setDisabled(true);
			sortByTypeAndPriceButton->setDisabled(true);
		}
		else {
			addButton->setEnabled(true);
			filterByNameButton->setEnabled(true);
			filterByDestinationButton->setEnabled(true);
			filterByPriceButton->setEnabled(true);
			undoButton->setEnabled(true);
			redoButton->setEnabled(true);
			wishlistButton->setEnabled(true);
			removeButton->setEnabled(true);
			sortByNameButton->setEnabled(true);
			sortByDestinationButton->setEnabled(true);
			sortByTypeAndPriceButton->setEnabled(true);

			try {
				std::string name = nameTextEdit->text().toStdString();
				std::string destination = destinationTextEdit->text().toStdString();
				std::string type = typeTextEdit->text().toStdString();
				double price = priceTextEdit->text().toDouble();

				service.modifyOffer(offerId, name, destination, type, price);
				/*offerList->clearSelection();
				reloadList(service.getAllOffers());*/
				offerTable->clearSelection();
				reloadTable(service.getAllOffers());
			}
			catch (DuplicateItemException& die) {
				std::stringstream ss{};
				ss << die;
				QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
			}
			catch (ValidException& ve) {
				std::stringstream ss{};
				ss << ve;
				QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
			}

			modifyButton->setText("Modify");
			nameTextEdit->clear();
			nameTextEdit->setDisabled(true);
			destinationTextEdit->clear();
			destinationTextEdit->setDisabled(true);
			typeTextEdit->clear();
			typeTextEdit->setDisabled(true);
			priceTextEdit->clear();
			priceTextEdit->setDisabled(true);
		}
	});

	QObject::connect(filterByNameButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti secventa dorita: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		std::string sequence = text.toStdString();
		/*offerList->clearSelection();
		reloadList(service.findByName(sequence));*/
		offerTable->clearSelection();
		reloadTable(service.findByName(sequence));
	});

	QObject::connect(filterByDestinationButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti destinatia dorita: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		std::string destination = text.toStdString();
		/*offerList->clearSelection();
		reloadList(service.filterByDestination(destination));*/
		offerTable->clearSelection();
		reloadTable(service.filterByDestination(destination));
	});

	QObject::connect(filterByPriceButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti pretul: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		double price = text.toDouble();
		/*offerList->clearSelection();
		reloadList(service.filterByPrice(price));*/
		offerTable->clearSelection();
		reloadTable(service.filterByPrice(price));
	});

	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			service.undo();
			//reloadList(service.getAllOffers());
			reloadTable(service.getAllOffers());
		}
		catch (ValidException& ve) {
			std::stringstream ss{};
			ss << ve;
			QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
		}
	});

	QObject::connect(redoButton, &QPushButton::clicked, [&]() {
		try {
			service.redo();
			//reloadList(service.getAllOffers());
			reloadTable(service.getAllOffers());
		}
		catch (ValidException& ve) {
			std::stringstream ss{};
			ss << ve;
			QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
		}
	});
}