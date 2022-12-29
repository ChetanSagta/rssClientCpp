#pragma once

#include <algorithm>
#include <ctime>
#include <fmt/format.h>
#include <iomanip>
#include <iostream>
#include <regex>
#include <spdlog/spdlog.h>
#include <string>
#include <tinyxml2.h>
#include <vector>

class Image {
  std::string title;
  std::string link;
  std::string url;
  friend class ImageQuery;

public:
  std::string print() {
    return fmt::format( "\nTitle: {}\nLink: {}, \nUrl: {}\n ", title, link,url);
  }

  std::string replace(std::string str, std::string from, std::string to) {
    std::regex from_re(from);
    std::string temp_str = std::regex_replace(str, from_re, to);
    return temp_str;
  }

  Image parse(tinyxml2::XMLElement *element) {

    for (auto *child = element->FirstChildElement();
         child != element->LastChildElement();
         child = child->NextSiblingElement()) {
      if (strcmp(child->Value(), "title") == 0) {
        this->title = child->GetText();
        if (!this->title.empty()) {
          this->title = replace(this->title, "'", "''");
        }
      } else if (strcmp(child->Value(), "link") == 0) {
        this->link = child->GetText();
      } else if (strcmp(child->Value(), "url") == 0) {
        this->url = child->GetText();
      }
    }
    return *this;
  }
};

class Item {
  std::string title;
  std::string description;
  std::string link;
  std::string guid;
  std::string pubDate;
  bool read;
  friend class ItemQuery;

public:
  std::string print() {
    return fmt::format(
        "Title: {} \nLink: {} \nDescription: {}\nGuid: {}\n Description: {}",
        title, link, description, guid, pubDate);
  }

  std::string replace(std::string str, std::string from, std::string to) {
    std::regex from_re(from);
    std::string temp_str = std::regex_replace(str, from_re, to);
    return temp_str;
  }

  Item parse(tinyxml2::XMLElement *element) {

    for (auto *child = element->FirstChildElement();
         child != element->LastChildElement();
         child = child->NextSiblingElement()) {
      if (child == nullptr)
        return *this;
      if (child->GetText() == nullptr)
        continue;
      if (strcmp(child->Value(), "title") == 0) {
        this->title = child->GetText();
        if (!this->title.empty()) {
          this->title = replace(this->title, "'", "''");
        }
      } else if (strcmp(child->Value(), "link") == 0) {
        this->link = child->GetText();
      } else if (strcmp(child->Value(), "description") == 0) {
        this->description = child->GetText();
        if (!this->description.empty()) {
          this->description = replace(this->description, "'", "''");
        }
      } else if (strcmp(child->Value(), "guid") == 0) {
        this->guid = child->GetText();
      } else if (strcmp(child->Value(), "pubDate") == 0) {
        this->guid = child->GetText();
      }
    }
    this->read = false;
    return *this;
  }
};

class Channel {
  std::string title;
  std::string link;
  std::string description;
  Image image;
  std::vector<Item> items;
  std::string last_build_date;
  friend class ChannelQuery;

public:

  std::string replace(std::string str, std::string from, std::string to) {
    std::regex from_re(from);
    std::string temp_str = std::regex_replace(str, from_re, to);
    return temp_str;
  }

  std::string print() {
    return fmt::format( "Title: {},\nLink: {},\nDescription: {},\nLast Build Date: {}\n", title,link,description, last_build_date);
  }

  Channel parse(tinyxml2::XMLElement *element) {

    for (auto *child = element->FirstChildElement();
         child != element->LastChildElement();
         child = child->NextSiblingElement()) {
      if (strcmp(child->Value(), "title") == 0) {
        this->title = child->GetText();
        if (!this->title.empty()) {
          this->title = replace(this->title, "'", "''");
        }
      } else if (strcmp(child->Value(), "description") == 0) {
        this->description = child->GetText();
        if (!this->description.empty()) {
          this->description = replace(this->description, "'", "''");
        }
      } else if (strcmp(child->Value(), "link") == 0) {
        this->link = child->GetText();
      } else if (strcmp(child->Value(), "image") == 0) {
        this->image = image.parse(child);
      } else if (strcmp(child->Value(), "item") == 0) {
        Item item;
        this->items.push_back(item.parse(child));
      } else if (strcmp(child->Value(), "lastBuildDate") == 0) {
        this->last_build_date = child->GetText();
      }
    }
    return *this;
  }
};
