#pragma once

#include <sqlite3.h>
#include <string>

class DBConnection {

public:
  DBConnection();
  ~DBConnection();
  int prepare_statement(std::string);
  int next();
  std::string get_error_message();
  std::string get_column_name(int no);
  void close();
  void open(std::string);
  void finalise();
  std::string get_column_string_value(int);
  int get_column_int_value(int);
  void bind_values(int,const std::string);

private:
  sqlite3 *connection;
  sqlite3_stmt *pstmt;
  int error_code;
  const char* pzTail;
};
