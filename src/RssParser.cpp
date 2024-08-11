#include "RssParser.hpp"
#include "ChannelQuery.hpp"
#include "ImageQuery.hpp"
#include "ItemQuery.hpp"
#include "models.hpp"
#include <spdlog/spdlog.h>
#include <tinyxml2.h>
#include "Download.hpp"
#include <fstream>

void RssParser::initialise() {

  MemoryStruct output;
  output.memory = (char *)malloc(0);
  output.size = 1;
  memset(output.memory, ' ', 1);
  // std::string url = "https://www.reddit.com/r/Holup/.rss;
  std::string url = "https://www.thehindu.com/news/national/feeder/default.rss";
  Download download;
  download.downloadUrl(url, &output);
  fmt::print("Output: {}\n", output.memory);
  RssParser rssParser;
  rssParser.parseRssFeed(output.memory, output.size);
  // atomFeeds
  free(output.memory);
}

std::vector<std::string> readFile() {

  std::string url_file = "../url.txt";
  std::ifstream url_stream(url_file, std::ifstream::binary);
  if (!url_stream) {
    SPDLOG_ERROR("Error While Opening {} file", url_file);
    return {};
  }
  std::vector<std::string> urls;
  for (std::string line; getline(url_stream, line);) {
    urls.push_back(line);
  }
  return urls;
}

void RssParser::parseRssFeed(std::string content, size_t size) {

  spdlog::set_pattern("[%s : %! : %#] %v");
  tinyxml2::XMLDocument document;
  // tinyxml2::XMLError errorCode = document.LoadFile(filename.c_str());
  tinyxml2::XMLError errorCode = document.Parse(content.c_str(), size);
  if (errorCode != tinyxml2::XML_SUCCESS) {
    SPDLOG_ERROR("Error While Reading XMl: What? {}\n", errorCode);
  }
  tinyxml2::XMLElement *elem = document.RootElement()->FirstChildElement();
  Channel channel;
  channel = channel.parse(elem);

  ChannelQuery channel_query{channel};
  if (!channel_query.isPresent())
    channel_query.insertChannel();
  int channel_id = channel_query.get_channel_id();
  tinyxml2::XMLElement *first_item = elem->FirstChildElement("item");
  tinyxml2::XMLElement *last_item = elem->LastChildElement("item");

  for (auto *temp_elem = first_item; temp_elem <= last_item;
       temp_elem = temp_elem->NextSiblingElement("item")) {
    if (temp_elem == nullptr)
      break;
    Item item;
    item = item.parse(temp_elem);
    ItemQuery item_query{item};
    if (!item_query.isPresent()) {
      item_query.insertItem(channel_id);
    }
  }

  tinyxml2::XMLElement *image_elem = elem->FirstChildElement("image");
  if (image_elem == nullptr)
    return;
  Image image;
  image = image.parse(image_elem);
  ImageQuery image_query(image);
  image_query.insert(channel_id);
}
