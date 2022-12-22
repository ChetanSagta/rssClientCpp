#pragma once
#include "DBConnection.hpp"
#include "models.cpp"

class ChannelQuery {

public:
  void insertChannel();
  int get_channel_id();
  ChannelQuery(Channel);

private:
  Channel m_channel;
  const std::string filename = "/home/chetan/Code/rssClient/rss.db";
};
