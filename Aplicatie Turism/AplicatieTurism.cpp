#include "AplicatieTurism.h"

AplicatieTurism::AplicatieTurism(Service& service, QWidget *parent)
	: QMainWindow(parent), service{service}
{
	ui.setupUi(this);
}
