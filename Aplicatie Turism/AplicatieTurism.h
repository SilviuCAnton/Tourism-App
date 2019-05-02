#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AplicatieTurism.h"
#include "Service.h"

class AplicatieTurism : public QMainWindow
{
	Q_OBJECT

public:
	AplicatieTurism(Service& service, QWidget *parent = Q_NULLPTR);

private:
	Ui::AplicatieTurismClass ui;
	Service& service;
};
