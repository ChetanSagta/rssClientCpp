#pragma once

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <qabstractitemmodel.h>
#include <qstandarditemmodel.h>
#include "../models/Article.hpp"

class ArticlesModel : public QAbstractTableModel {

Q_OBJECT
private:
  QList<Article*> *m_list;

public:
  ArticlesModel();
  ~ArticlesModel();
  void addArticle(Article *article);
  ArticlesModel *getModel();

  // QAbstractItemModel interface
  public:
  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
};
