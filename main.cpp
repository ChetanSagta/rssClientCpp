#include "DBConnection.hpp"
#include "models.cpp"
#include <sqlite3.h>
#include "ChannelQuery.hpp"

#define DBLOCATION "/home/chetan/Code/rssClient/rss.db"

int main() {
  tinyxml2::XMLDocument document;
  tinyxml2::XMLError errorCode = document.LoadFile("../rssfeedstopstories.cms");
  if (errorCode != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error While Reading XMl: What? " << errorCode << std::endl;
  }
  tinyxml2::XMLElement *elem = document.RootElement()->FirstChildElement();
  Channel channel;
  channel = channel.parse(elem);
  
  ChannelQuery channel_query{channel};
  channel_query.insertChannel();
  std::cout<<channel_query.get_channel_id()<<std::endl;
  return 0;
}
