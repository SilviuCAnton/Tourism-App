#pragma once
#include <QtCore/qstring.h>
#include <QtWidgets/qwidget.h>
#include <Service.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

class StatisticsGUI : public QWidget {
public:
	StatisticsGUI(std::vector<TypeCountDTO> items);

private:
	std::vector<TypeCountDTO> items;
	void buildGUI();
	void loadTable(std::vector<TypeCountDTO> items);
	void connectSignalsAndSlots();

	//Table
	QTableView* table = new QTableView;

	//Buttons
	QPushButton* okButton = new QPushButton("Ok");

	class StatTableModel : public QAbstractTableModel {
	private:
		std::vector<TypeCountDTO> items;
	public:
		StatTableModel(const std::vector<TypeCountDTO>& items) : QAbstractTableModel(), items{ items } {};
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
			if (role == Qt::DisplayRole) {
				if (index.column() == 0) {
					return QString::fromStdString(items.at(index.row()).getType());
				}
				else if (index.column() == 1) {
					return QString::number(items.at(index.row()).getCount());
				}
			}
			return QVariant();
		};
		int columnCount(const QModelIndex& = QModelIndex()) const override { return 2; }
		int rowCount(const QModelIndex& = QModelIndex()) const override { return items.size(); }
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
			if (role == Qt::DisplayRole) {
				if (orientation == Qt::Horizontal) {
					if (section == 0) {
						return QString("Tip").arg(section);
					}
					else if (section == 1) {
						return QString("Cate").arg(section);
					}
				}
				else {
					return QString("%1").arg(section);
				}
			}
			return QVariant();
		}
	};
};

