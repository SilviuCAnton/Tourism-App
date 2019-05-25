#include "ReadOnlyWishlistGUI.h"

ReadOnlyWishlistGUI::ReadOnlyWishlistGUI(Service & serv) : serv{ serv } {
	serv.subscribeToWishlist(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

ReadOnlyWishlistGUI::~ReadOnlyWishlistGUI() {
	serv.unsubscribeFromWishlist(this);
}

void ReadOnlyWishlistGUI::update() {
	repaint();
}

void ReadOnlyWishlistGUI::paintEvent(QPaintEvent * ev) {
	for (const auto& off : serv.getWishlist()) {
		QPainter p{ this };
		p.setRenderHint(QPainter::Antialiasing);
		int x = rand() % (width()-100);
		int y = rand() % (height()-100);

		QImage img("vac.jpg");
		Q_ASSERT(!img.isNull());
		p.drawImage( QRect(x,y,100,100), img);
	}
	
}
