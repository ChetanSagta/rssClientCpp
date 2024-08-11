#include "MainWindow.hpp"
#include "models/Article.hpp"
#include "widgets/ArticlesModel.hpp"
#include <QHeaderView>
#include <QStringListModel>
#include <QTableView>
#include <qabstractitemmodel.h>
#include <qnamespace.h>

MainWindow::MainWindow() : QWindow() {
  // Create a central widget and set its layout

  m_articlesModel = new ArticlesModel();
  Article *article = new Article();
  article->setNumber(1);
  article->setLink("Link");
  article->setTitle("Title");
  m_articlesModel->addArticle(article);

  urlListView = new QTableView();
  urlListView->setModel(m_articlesModel);

  urlListView->resizeRowsToContents();
  urlListView->resizeColumnsToContents();

  urlListView->show();

  /*connect(button, &QPushButton::clicked, this,
   * &MainWindow::handleButtonClick);*/
}

MainWindow::~MainWindow() {}
