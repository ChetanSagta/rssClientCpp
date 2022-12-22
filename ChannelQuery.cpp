#include "ChannelQuery.hpp"
#include "DBConnection.hpp"

ChannelQuery::ChannelQuery(Channel channel):m_channel(channel){}

void ChannelQuery::insertChannel(){

  std::string temp_query = fmt::format("insert into channel ('title','link', 'description','last_build_date') values ('{}', '{}', '{}', '{}');", m_channel.title, m_channel.link, m_channel.description, m_channel.last_build_date);

  DBConnection connection{};
  connection.open(filename);
  
  int result_code = connection.prepare_statement(temp_query);
  if (result_code != SQLITE_OK) {
    std::cerr << "Error while prepared statements. ErrorCode : " << result_code << " Message: "<< connection.get_error_message()
              << std::endl;
    connection.close();
    return;
  }
  while(connection.next() == SQLITE_ROW){
    std::cout<<"Value: "<<connection.get_column_string_value(2)<<std::endl;
 }
  connection.finalise();
  connection.close();
}

int ChannelQuery::get_channel_id(){
    int temp_value=-1;
  DBConnection connection;
  connection.open(filename);

  std::string query = "select id from channel where title = ?";
  int result_code = connection.prepare_statement(query);
  if (result_code != SQLITE_OK) {
    std::cerr << "Error while prepared statements. ErrorCode : " << result_code << " Message: "<< connection.get_error_message()
              << std::endl;

    connection.finalise();
    return -1;
  }
  connection.bind_values(1, m_channel.title);
  if(connection.next() == SQLITE_ROW){
      temp_value = connection.get_column_int_value(1);
  }
  connection.finalise();
  return temp_value;

}
