#include "WishlistGUI.h"
#include <sstream>
#include <qinputdialog.h>

WishlistGUI::WishlistGUI(Service& serv) : service{ serv } {
	buildGUI();
	connectSignalsAndSlots();
	reloadList(service.getWishlist());
}

void WishlistGUI::buildGUI() {
	QHBoxLayout* horziontalLayout = new QHBoxLayout;
	QVBoxLayout* leftVerticalLayout = new QVBoxLayout;
	QVBoxLayout* rightVerticalLayout = new QVBoxLayout;
	QVBoxLayout* labelVerticalLayout = new QVBoxLayout;
	QVBoxLayout* textBoxVerticalLayout = new QVBoxLayout;
	QHBoxLayout* detailsHorizontalLayout = new QHBoxLayout;
	QHBoxLayout* actionsLayout = new QHBoxLayout;
	setLayout(horziontalLayout);

	//Left side
	QWidget* left = new QWidget;
	QLabel* offerLabel = new QLabel("Offers:");
	QLabel* wishlistLabel = new QLabel("Wishlist:");
	left->setLayout(leftVerticalLayout);
	leftVerticalLayout->addWidget(offerLabel);
	leftVerticalLayout->addWidget(offerList);
	leftVerticalLayout->addWidget(wishlistLabel);
	leftVerticalLayout->addWidget(wishList);

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

	//Actions
	QWidget* actions = new QWidget;
	actions->setLayout(actionsLayout);
	actionsLayout->addWidget(addButton);
	actionsLayout->addWidget(clearButton);
	actionsLayout->addWidget(populateButton);
	actionsLayout->addWidget(exportButton);
	addButton->setDisabled(true);

	//Right side
	QWidget* right = new QWidget;
	right->setLayout(rightVerticalLayout);
	rightVerticalLayout->addWidget(details);
	rightVerticalLayout->addStretch();
	rightVerticalLayout->addWidget(actions);

	//List setup
	offerList->setSelectionMode(QAbstractItemView::SingleSelection);
	wishList->setSelectionMode(QAbstractItemView::SingleSelection);

	//Main panel
	horziontalLayout->addWidget(left);
	horziontalLayout->addWidget(right);
}

void WishlistGUI::loadList(std::vector<Offer> offers) {
	offerList->clear();
	for (const auto& offer : offers) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName()), offerList);
		item->setData(Qt::UserRole, offer.getId());
	}
}

void WishlistGUI::reloadList(std::vector<Offer> offers) {
	wishList->clear();
	for (const auto& offer : offers) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName()), wishList);
		item->setData(Qt::UserRole, offer.getId());
	}
}

void WishlistGUI::connectSignalsAndSlots() {
	QObject::connect(offerList, &QListWidget::itemSelectionChanged, [&]() {
		if (!offerList->selectedItems().isEmpty()) {
			addButton->setEnabled(true);
			wishList->clearSelection();
			const Offer& myOffer{ service.findById(offerList->selectedItems().first()->data(Qt::UserRole).toInt()) };
			nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
			destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
			typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
			std::stringstream ss{};
			ss << myOffer.getPrice();
			priceTextEdit->setText(QString::fromStdString(ss.str()));
		}
		else {
			addButton->setDisabled(true);
		}
	});

	QObject::connect(wishList, &QListWidget::itemSelectionChanged, [&]() {
		if (!wishList->selectedItems().isEmpty()) {
			offerList->clearSelection();
			const Offer& myOffer{ service.findById(wishList->selectedItems().first()->data(Qt::UserRole).toInt()) };
			nameTextEdit->setText(QString::fromStdString(myOffer.getName()));
			destinationTextEdit->setText(QString::fromStdString(myOffer.getDestination()));
			typeTextEdit->setText(QString::fromStdString(myOffer.getType()));
			std::stringstream ss{};
			ss << myOffer.getPrice();
			priceTextEdit->setText(QString::fromStdString(ss.str()));
		}
	});

	QObject::connect(populateButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti numarul de oferte: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		int number = text.toInt();
		wishList->clearSelection();
		service.populateWishlist(number);
		reloadList(service.getWishlist());
	});

	QObject::connect(clearButton, &QPushButton::clicked, [&]() {
		service.emptyWishlist();
		reloadList(service.getWishlist());
	});

	QObject::connect(addButton, &QPushButton::clicked, [&]() {
		int offerId = offerList->selectedItems().first()->data(Qt::UserRole).toInt();
		offerList->clearSelection();
		service.addToWishlist(offerId);
		reloadList(service.getWishlist());
	});

	QObject::connect(exportButton, &QPushButton::clicked, [&]() {
		QInputDialog inputDialog;
		inputDialog.setMinimumSize(200, 100);
		inputDialog.setLabelText("Introduceti numele cu care doriti sa fie salvat fisierul: ");
		inputDialog.exec();
		auto text = inputDialog.textValue();
		std::string fileName = text.toStdString();
		service.exportWishlistCSV(fileName);
	});
}
