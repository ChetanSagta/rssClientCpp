#include "ChannelQuery.hpp"

#include "DBConnection.hpp"
#include "ImageQuery.hpp"
#include "ItemQuery.hpp"
#include "models.hpp"
#include <cstddef>
#include <curl/curl.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sqlite3.h>
#include <tinyxml2.h>

#define DBLOCATION "/home/chetan/Code/rssClient/rss.db"

#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

struct MemoryStruct {
  char *memory;
  size_t size;
};

void parseRssFeed(std::string content, size_t size) {

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

/* curl write callback, to fill tidy's input buffer...  */
uint write_cb(char *in, uint size, uint nmemb, MemoryStruct *mem) {
  uint realsize = size * nmemb;

  char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if (ptr == NULL)
    return 0; /* out of memory! */

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), in, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void downloadUrl(std::string url, MemoryStruct *output) {

  char *curl_errbuf = new char;
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
  int err = curl_easy_perform(curl);
  if (err) {
    SPDLOG_INFO("Error Code: {} \n ", err);
  }
}

void initialize() {

  MemoryStruct output;
  output.memory = (char *)malloc(0);
  output.size = 1;
  memset(output.memory, ' ', 1);
  // std::string url = "https://www.reddit.com/r/Holup/.rss;
  std::string url = "https://www.thehindu.com/news/national/feeder/default.rss";
  downloadUrl(url, &output);
  fmt::print("Output: {}\n", output.memory);
  parseRssFeed(output.memory, output.size);
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

int main() { return 0; }
