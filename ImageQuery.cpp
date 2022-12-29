#include "ImageQuery.hpp"
#include <fmt/format.h>

ImageQuery::ImageQuery(Image image) : m_image{image} {
  m_connection.open(filename);
}

ImageQuery::~ImageQuery() { m_connection.close(); }

void ImageQuery::insert(int cid) {
  std::string query =
      fmt::format("insert into image(title, link , url , cid) values "
                  "('{}','{}','{}','{}');",
                  m_image.title, m_image.link, m_image.url, cid);

  int result_code = m_connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR(
        "Error while prepared statements. ErrorCode : {} , Message: {} \n",
        result_code, m_connection.get_error_message());
    SPDLOG_ERROR("ITEM : {}\n", m_image.print());
    return;
  }
  while (m_connection.next() == SQLITE_ROW) {
    // SPDLOG_INFO("Value: {} \n", m_connection.get_column_string_value(2));
  }
  m_connection.finalise();
}

bool ImageQuery::isPresent() {
  bool present = false;

  std::string query = fmt::format(
      "select count(1) from image where url in ('{}');", m_image.url);

  int result_code = m_connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR(
        "Error while prepared statements. ErrorCode : {} , Message: {} \n",
        result_code, m_connection.get_error_message());
    SPDLOG_ERROR("IMAGE : {}\n", m_image.print());
    // Returning True so that if the Query fails....the data doesn't enter that
    // is dependent on is_present
    return true;
  }
  while (m_connection.next() == SQLITE_ROW) {
    int value = m_connection.get_column_int_value(0);
    SPDLOG_INFO("No of Items Present: {}", value);
    if (value > 0)
      present = true;
  }
  m_connection.finalise();
  return present;
}
