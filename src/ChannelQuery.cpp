#include "ChannelQuery.hpp"

ChannelQuery::ChannelQuery(Channel channel) : m_channel(channel) {
  m_connection.open(filename);
}

ChannelQuery::~ChannelQuery() { m_connection.close(); }

void ChannelQuery::insertChannel() {

  std::string temp_query = fmt::format(
      "insert into channel ('title','link', 'description','last_build_date') "
      "values ('{}', '{}', '{}', '{}');",
      m_channel.title, m_channel.link, m_channel.description,
      m_channel.last_build_date);

  int result_code = m_connection.prepare_statement(temp_query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR( "Error while prepared statements. ErrorCode : {} Message: {} \n" ,result_code, m_connection.get_error_message());
    return;
  }
  while (m_connection.next() == SQLITE_ROW) {
    SPDLOG_INFO( "Value: {} \n " ,m_connection.get_column_string_value(2));
  }
  m_connection.finalise();
}

int ChannelQuery::get_channel_id() {
  int temp_value = -1;

  std::string query = "select id from channel where title = ?";
  int result_code = m_connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR( "Error while prepared statements. ErrorCode : {}, Message: {} \n" ,result_code ,m_connection.get_error_message());
    m_connection.finalise();
    return -1;
  }
  m_connection.bind_values(1, m_channel.title);
  if (m_connection.next() == SQLITE_ROW) {
    temp_value = m_connection.get_column_int_value(0);
  }
  m_connection.finalise();
  return temp_value;
}

bool ChannelQuery::isPresent() {
  bool present = false;

  std::string query = fmt::format(
      "select count(1) from channel where link in ('{}');", m_channel.link);

  int result_code = m_connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    SPDLOG_ERROR(
        "Error while prepared statements. ErrorCode : {} , Message: {} \n",
        result_code, m_connection.get_error_message());
    SPDLOG_ERROR("ITEM : {}\n", m_channel.print());
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
