#include "DBConnection.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string>

DBConnection::DBConnection() {
  std::cout<<"Initiliasing Sqlite"<<std::endl;
  sqlite3_initialize();
}

DBConnection::~DBConnection() {
    std::cout<<"Shutting Down sqlite"<<std::endl;
    sqlite3_shutdown();
}

int DBConnection::prepare_statement(std::string query) {
  return sqlite3_prepare_v2(connection, query.c_str(), query.length(), &pstmt, NULL);
}

int DBConnection::next() { return sqlite3_step(pstmt); }

std::string DBConnection::get_error_message() {
  return sqlite3_errmsg(connection);
}

std::string DBConnection::get_column_name(int column_no){
    return sqlite3_column_name(pstmt, column_no);
}

void DBConnection::open(const std::string file_name){
    std::cout<<"Opening Sqlite DB"<<std::endl;
    error_code = sqlite3_open_v2(file_name.c_str(), &connection, SQLITE_OPEN_READWRITE, "unix-dotfile");
    if (error_code != SQLITE_OK) {
      std::cerr << "Error While Opening SQLITE: " << error_code << std::endl;
      return;
    }
}

void DBConnection::finalise(){
    sqlite3_finalize(pstmt);
}

void DBConnection::close(){
    std::cout<<"Closing SQLITE "<<std::endl;
    sqlite3_close_v2(connection);
}

std::string DBConnection::get_column_string_value(int column_no){
    return reinterpret_cast<const char*>(sqlite3_column_text(pstmt, column_no));
}

int DBConnection::get_column_int_value(int column_no){
    return sqlite3_column_int(pstmt, column_no);
}


void DBConnection::bind_values(int index, const std::string value){
  sqlite3_bind_text(pstmt,index,value.c_str(), value.length(),SQLITE_STATIC);
}
