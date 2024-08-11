#pragma once

#include "widgets/ArticlesModel.hpp"
#include <QDebug>
#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QWindow>
#include <QList>
#include<QStandardItem>

class MainWindow : public QWindow {

  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

private:
  QWidget *centralWidget;
  QHBoxLayout *layout;
  QLabel *label;
  QPushButton *button;
  QTableView *urlListView, *articlesListView, *previewViewList;
  ArticlesModel *m_articlesModel;
  QStringList *urls, *articles;
  QStandardItemModel *standardItem;

  
};
