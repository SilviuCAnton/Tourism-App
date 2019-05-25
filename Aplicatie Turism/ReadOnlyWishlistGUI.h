#pragma once
#include "Domain.h"
#include <QtWidgets>
#include <Service.h>

class ReadOnlyWishlistGUI : public Observer, public QWidget {
private:
	Service& serv;
public:
	ReadOnlyWishlistGUI(Service& serv);
	~ReadOnlyWishlistGUI();
	void update() override;
protected:
	void paintEvent(QPaintEvent* ev) override;
};

