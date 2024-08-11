#include "ArticlesModel.hpp"
#include <qglobal.h>
#include <qstandarditemmodel.h>

ArticlesModel::ArticlesModel() { m_list = new QList<Article*>(); }

ArticlesModel::~ArticlesModel() {}

void ArticlesModel::addArticle(Article *article) { m_list->append(article); }

ArticlesModel *ArticlesModel::getModel() { return this; }

int ArticlesModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_list->size();
}
int ArticlesModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 3;
}
QVariant ArticlesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole)
    return QVariant();

  Article *article = (*m_list)[index.row()];
  switch (index.column()) {
  case 0:
    return article->getNumber();
  case 1:
    return article->getTitle();
  case 2:
    return article->getLink();
  default:
    return QVariant();
  }
}
