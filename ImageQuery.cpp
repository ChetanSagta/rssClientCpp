#include "ImageQuery.hpp"
#include <fmt/format.h>

void ImageQuery::insertQuery(int cid, int iid){
  std::string query = fmt::format("insert into image(title, link , url , cid, iid) values ('{}','{}','{}','{}');",m_image.title, m_image.link, m_image.url, cid, iid);
}
