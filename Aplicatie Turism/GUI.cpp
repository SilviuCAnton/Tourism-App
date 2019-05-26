#include "GUI.h"
#include "ReadOnlyWishlistGUI.h"
#include "Exceptions.h"
#include <QtWidgets>
#include <sstream>
#include <qdebug.h>

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
	QHBoxLayout* wishlistBtnsLayout = new QHBoxLayout;
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
	QWidget* wishlistBtns = new QWidget;
	wishlistBtns->setLayout(wishlistBtnsLayout);
	wishlistBtnsLayout->addWidget(addToWishlistButton);
	wishlistBtnsLayout->addWidget(clearWishlistButton);
	wishlistBtnsLayout->addWidget(populateWishlistButton);
	leftVerticalLayout->addWidget(wishlistBtns);
	addToWishlistButton->setDisabled(true);

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
	topRightLayout->addWidget(readOnlyWishlistButton);

	//Right side
	QWidget* right = new QWidget;
	right->setLayout(rightVerticalLayout);
	rightVerticalLayout->addWidget(topRight);
	rightVerticalLayout->addWidget(details);
	rightVerticalLayout->addWidget(actions);

	//Table setup
	offerTable->setSelectionMode(QAbstractItemView::SingleSelection);
	offerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	offerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//Main panel
	horziontalLayout->addWidget(left);
	horziontalLayout->addWidget(right);
	
}

void GUI::reloadTable(std::vector<Offer> offers) {
	model = new TableModel { offers, service.sortByTypeAndPrice() };
	offerTable->setModel(model);
	QObject::connect(offerTable->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (offerTable->selectionModel()->selectedIndexes().isEmpty()) {
			addToWishlistButton->setDisabled(true);
			removeButton->setDisabled(true);
			modifyButton->setDisabled(true);
			nameTextEdit->clear();
			destinationTextEdit->clear();
			typeTextEdit->clear();
			priceTextEdit->clear();
			return;
		}
		addToWishlistButton->setEnabled(true);
		removeButton->setEnabled(true);
		modifyButton->setEnabled(true);
		const Offer& myOffer{ service.findById(offerTable->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toInt()) };
		nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
		destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
		typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
		std::stringstream ss{};
		ss << myOffer.getPrice();
		priceTextEdit->setText(QString::fromStdString(ss.str()));
	});
}

void GUI::connectSignalsAndSlots() {

	QObject::connect(addToWishlistButton, &QPushButton::clicked, [&]() {
		try {
			int offerId = offerTable->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toInt();
			offerTable->clearSelection();
			service.addToWishlist(offerId);
		}
		catch (DuplicateItemException& die) {
			QErrorMessage err(this);
			err.setMinimumSize(200, 100);
			std::stringstream ss{};
			ss << die;
			err.showMessage(QString::fromStdString(ss.str()));
			err.exec();
		}
	});

	QObject::connect(clearWishlistButton, &QPushButton::clicked, [&]() {
		service.emptyWishlist();
	});

	QObject::connect(populateWishlistButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti numarul de oferte: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		int number = text.toInt();
		service.populateWishlist(number);
	});

	QObject::connect(sortByNameButton, &QPushButton::clicked, [&]() {
		offerTable->clearSelection();
		reloadTable(service.sortByName());

	});

	QObject::connect(sortByDestinationButton, &QPushButton::clicked, [&]() {
		offerTable->clearSelection();
		reloadTable(service.sortByDestination());
	});

	QObject::connect(sortByTypeAndPriceButton, &QPushButton::clicked, [&]() {
		offerTable->clearSelection();
		reloadTable(service.sortByTypeAndPrice());
	});

	QObject::connect(removeButton, &QPushButton::clicked, [&]() {
		offerId = offerTable->currentIndex().data(Qt::UserRole).toInt();
		offerTable->clearSelection();
		service.removeOffer(offerId);
		reloadTable(service.getAllOffers());

	});

	QObject::connect(readOnlyWishlistButton, &QPushButton::clicked, [&]() {
		ReadOnlyWishlistGUI* wishGUI = new ReadOnlyWishlistGUI{ service };
		wishGUI->show();
	});

	QObject::connect(wishlistButton, &QPushButton::clicked, [&]() {
		WishlistGUI* wishGUI = new WishlistGUI{ service };
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
			offerId = offerTable->currentIndex().data(Qt::UserRole).toInt();
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
		offerTable->clearSelection();
		reloadTable(service.filterByPrice(price));
	});

	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			service.undo();
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
			reloadTable(service.getAllOffers());
		}
		catch (ValidException& ve) {
			std::stringstream ss{};
			ss << ve;
			QMessageBox::critical(this, tr("Error"), tr(ss.str().c_str()));
		}
	});
}

QVariant TableModel::data(const QModelIndex & index, int role) const
{
	if (role == Qt::DisplayRole) {
		std::string str;
		if (index.column() == 0) {
			str = items.at(index.row()).getName();
		}
		else if (index.column() == 1) {
			str = items.at(index.row()).getDestination();
		}
		else if (index.column() == 2) {
			str = items.at(index.row()).getType();
		}
		else if (index.column() == 3) {
			str = std::to_string(items.at(index.row()).getPrice());
		}
		return QString::fromStdString(str);
	}
	if (role == Qt::UserRole) {
		return items.at(index.row()).getId();
	}
	if (role == Qt::BackgroundColorRole) {
		int id = items.at(index.row()).getId();
		int size = sorted.size();
		int pos{ 0 };
		while (id != sorted[pos].getId()) {
			pos++;
		}
		if (pos < size / 3) {
			return QColor(Qt::red);
		}
		else if (pos < size / 3 * 2) {
			return QColor(Qt::green);
		}
		else {
			return QColor(Qt::blue);
		}
	}
	return QVariant();
}

TableModel::TableModel(const std::vector<Offer>& offers, const std::vector<Offer>& sorted) : QAbstractTableModel(), items{ offers }, sorted{ sorted } {
}

int TableModel::columnCount(const QModelIndex &) const {
	return 4;
}

int TableModel::rowCount(const QModelIndex &) const {
	return items.size();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return QString("Nume");
			}
			else if(section == 1) {
				return QString("Destinatie");
			}
			else if (section == 2) {
				return QString("Tip");
			}
			else if (section == 3) {
				return QString("Pret");
			}
		}
		else {
			return QString("%1").arg(section);
		}
	}
	return QVariant();
}