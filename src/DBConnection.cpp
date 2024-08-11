#include "DBConnection.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string>

DBConnection::DBConnection() {
  SPDLOG_INFO("Initiliasing Sqlite");
  sqlite3_initialize();
}

DBConnection::~DBConnection() {
  SPDLOG_INFO("Shutting Down sqlite");
  sqlite3_shutdown();
}

int DBConnection::prepare_statement(std::string query) {
  return sqlite3_prepare_v2(connection, query.c_str(), query.length(), &pstmt,
                            NULL);
}

int DBConnection::next() { return sqlite3_step(pstmt); }

std::string DBConnection::get_error_message() {
  return sqlite3_errmsg(connection);
}

std::string DBConnection::get_column_name(int column_no) {
  return sqlite3_column_name(pstmt, column_no);
}

void DBConnection::open(const std::string file_name) {
  SPDLOG_INFO("Opening Sqlite DB");
  error_code = sqlite3_open_v2(file_name.c_str(), &connection,
                               SQLITE_OPEN_READWRITE, "unix-dotfile");
  if (error_code != SQLITE_OK) {
    SPDLOG_ERROR("Error While Opening SQLITE: {}", error_code);
    return;
  }
}

void DBConnection::finalise() { sqlite3_finalize(pstmt); }

void DBConnection::close() {
  SPDLOG_INFO("Closing SQLITE \n");
  sqlite3_close_v2(connection);
}

std::string DBConnection::get_column_string_value(int column_no) {
  return reinterpret_cast<const char *>(sqlite3_column_text(pstmt, column_no));
}

int DBConnection::get_column_int_value(int column_no) {
  return sqlite3_column_int(pstmt, column_no);
}

void DBConnection::bind_values(int index, const std::string value) {
  sqlite3_bind_text(pstmt, index, value.c_str(), value.length(), SQLITE_STATIC);
}
