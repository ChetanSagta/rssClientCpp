#pragma once
#include "DBConnection.hpp"
#include "models.hpp"

class ChannelQuery {

public:
  void insertChannel();
  int get_channel_id();
  ChannelQuery(Channel);
  ~ChannelQuery();
  bool isPresent();

private:
  Channel m_channel;
  const std::string filename = "/home/chetan/Code/rssClient/rss.db";
  DBConnection m_connection;
};
