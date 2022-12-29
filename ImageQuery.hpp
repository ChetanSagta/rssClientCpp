#pragma once
#include "DBConnection.hpp"
#include "models.hpp"
class ImageQuery {

public:
  ImageQuery(Image);
  ~ImageQuery();
  void insert(int);
  bool isPresent();

private:
  Image m_image;
  const std::string filename = "/home/chetan/Code/rssClient/rss.db";
  DBConnection m_connection;
};
