#pragma once
#include <QAbstractTableModel>
#include <QObject>
#include <qstandarditemmodel.h>
#include <string>

class Article : public QStandardItem {

  int number;
  QString title;
  QString link;

public:
  void setNumber(int number) { this->number = number; }

  void setTitle(QString title) { this->title = title; }

  void setLink(QString link) { this->link = link; }

  int getNumber() { return this->number; }

  QString getLink() { return this->link; }

  QString getTitle() { return this->title; }
};
