#include "GUI.h"
#include "Exceptions.h"
#include <qerrormessage.h>
#include <qobject.h>
#include <qinputdialog.h>
#include <sstream>

GUI::GUI(Service& serv) : service{ serv } {
	buildGUI();
	connectSignalsAndSlots();
	reloadList(service.getAllOffers());
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
	leftHorziontalLayout->addWidget(sortByNameButton);
	leftHorziontalLayout->addWidget(sortByDestinationButton);
	leftHorziontalLayout->addWidget(sortByTypeAndPriceButton);

	//Left side
	QWidget* left = new QWidget;
	left->setLayout(leftVerticalLayout);
	leftVerticalLayout->addWidget(offerList);
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
	topRightLayout->addStretch();
	topRightLayout->addWidget(wishlistButton);

	//Right side
	QWidget* right = new QWidget;
	right->setLayout(rightVerticalLayout);
	rightVerticalLayout->addWidget(topRight);
	rightVerticalLayout->addWidget(details);
	rightVerticalLayout->addWidget(actions);

	//List setup
	offerList->setSelectionMode(QAbstractItemView::SingleSelection);

	//Main panel
	horziontalLayout->addWidget(left);
	horziontalLayout->addWidget(right);
}

void GUI::reloadList(std::vector<Offer> offers) {
	offerList->clear();
	for (const auto& offer : offers) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName()), offerList);
		item->setData(Qt::UserRole, offer.getId());
	}
}

void GUI::connectSignalsAndSlots() {
	QObject::connect(offerList, &QListWidget::itemSelectionChanged, [&]() {
		if (!offerList->selectedItems().isEmpty()) {
			const Offer& myOffer{ service.findById(offerList->selectedItems().first()->data(Qt::UserRole).toInt()) };
			nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
			destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
			typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
			std::stringstream ss{};
			ss << myOffer.getPrice();
			priceTextEdit->setText(QString::fromStdString(ss.str()));
		}
 	});

	QObject::connect(sortByNameButton, &QPushButton::clicked, [&]() {
		offerList->clearSelection();
		reloadList(service.sortByName());
	});

	QObject::connect(sortByDestinationButton, &QPushButton::clicked, [&]() {
		offerList->clearSelection();
		reloadList(service.sortByDestination());
	});

	QObject::connect(sortByTypeAndPriceButton, &QPushButton::clicked, [&]() {
		offerList->clearSelection();
		reloadList(service.sortByTypeAndPrice());
	});

	QObject::connect(removeButton, &QPushButton::clicked, [&]() {
		int offerId{ offerList->selectedItems().first()->data(Qt::UserRole).toInt() };
		offerList->clearSelection();
		service.removeOffer(offerId);
		reloadList(service.getAllOffers());
	});

	QObject::connect(filterByNameButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti secventa dorita: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		std::string sequence = text.toStdString();
		offerList->clearSelection();
		reloadList(service.findByName(sequence));
	});

	QObject::connect(filterByDestinationButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti destinatia dorita: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		std::string destination = text.toStdString();
		offerList->clearSelection();
		reloadList(service.filterByDestination(destination));
	});

	QObject::connect(filterByPriceButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti pretul: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		double price = text.toDouble();
		offerList->clearSelection();
		reloadList(service.filterByPrice(price));
	});

	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			service.undo();
			reloadList(service.getAllOffers());
		}
		catch (ValidException& ve) {
			QErrorMessage err(this);
			err.setMinimumSize(200, 100);
			std::stringstream ss{};
			ss << ve;
			err.showMessage(QString::fromStdString(ss.str()));
			err.exec();
		}
	});

	QObject::connect(redoButton, &QPushButton::clicked, [&]() {
		try {
			service.redo();
			reloadList(service.getAllOffers());
		}
		catch (ValidException& ve) {
			QErrorMessage err(this);
			err.setMinimumSize(200, 100);
			std::stringstream ss{};
			ss << ve;
			err.showMessage(QString::fromStdString(ss.str()));
			err.exec();
		}
	});
}
