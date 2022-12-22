#pragma once

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <fmt/format.h>

class Image {
  std::string title;
  std::string link;
  std::string url;
  friend class ImageQuery;

public:
  void print() {
    std::cout << "\nTitle: " << title << "\nLink: " << link << "\nUrl: " << url
              << std::endl;
  }

  Image parse(tinyxml2::XMLElement *element) {

    for (auto *child = element->FirstChildElement();
         child != element->LastChildElement();
         child = child->NextSiblingElement()) {
      if (strcmp(child->Value(), "title") == 0) {
        this->title = child->GetText();
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
  void print() {
    std::cout << "Title: " << title << "\nLink: " << link
              << "\nDescription: " << description << "\nGuid: " << guid
              << "\nPubDate: " << pubDate << std::endl;
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
      } else if (strcmp(child->Value(), "link") == 0) {
        this->link = child->GetText();
      } else if (strcmp(child->Value(), "description") == 0) {
        this->description = child->GetText();
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
  void print() {
    std::cout << "Title: " << title << "\nLink: " << link
              << "\nDescription: " << description
              << "Last Build Date: " << last_build_date << "\nImage: ";
    image.print();
    std::cout << "\nItems: ";
    for (size_t i = 0; i < items.size(); i++) {
      items.at(i).print();
    }
  }

  Channel parse(tinyxml2::XMLElement *element) {

    for (auto *child = element->FirstChildElement();
         child != element->LastChildElement();
         child = child->NextSiblingElement()) {
      if (strcmp(child->Value(), "title") == 0) {
        this->title = child->GetText();
      } else if (strcmp(child->Value(), "description") == 0) {
        this->description = child->GetText();
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
