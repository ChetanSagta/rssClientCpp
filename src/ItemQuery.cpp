#include "ItemQuery.hpp"
#include <spdlog/spdlog.h>

ItemQuery::ItemQuery(Item item) : m_item(item) { m_connection.open(filename); }
ItemQuery::~ItemQuery() { m_connection.close(); }

void ItemQuery::insertItem(int channel_id) {

  std::string temp_query = fmt::format(
      "insert into item('title', 'description','link','guid','pub_date','cid') "
      "values ('{}', '{}', '{}', '{}','{}','{}');",
      m_item.title, m_item.description, m_item.link, m_item.guid,
      m_item.pubDate, channel_id);

  int result_code = m_connection.prepare_statement(temp_query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR(
        "Error while prepared statements. ErrorCode : {} , Message: {} \n",
        result_code, m_connection.get_error_message());
    SPDLOG_ERROR("ITEM : {}\n", m_item.print());
    return;
  }
  while (m_connection.next() == SQLITE_ROW) {
    // SPDLOG_INFO("Value: {} \n", m_connection.get_column_string_value(2));
  }
  m_connection.finalise();
}

bool ItemQuery::isPresent() {
  bool present = false;

  std::string query =
      fmt::format("select count(1) from item where link in ('{}');", m_item.link);

  int result_code = m_connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR(
        "Error while prepared statements. ErrorCode : {} , Message: {} \n",
        result_code, m_connection.get_error_message());
    SPDLOG_ERROR("ITEM : {}\n", m_item.print());
    //Returning True so that if the Query fails....the data doesn't enter that is dependent on is_present
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
