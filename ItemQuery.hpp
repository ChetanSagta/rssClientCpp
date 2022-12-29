#pragma once
#include "DBConnection.hpp"
#include "models.hpp"

class ItemQuery {

public:
  void insertItem(int);
  ItemQuery(Item);
  bool isPresent();
  ~ItemQuery();

private:
  Item m_item;
  const std::string filename = "/home/chetan/Code/rssClient/rss.db";
  DBConnection m_connection;
};
