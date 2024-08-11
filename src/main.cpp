#include "ChannelQuery.hpp"

#include "DBConnection.hpp"
#include "Download.hpp"
#include "ImageQuery.hpp"
#include "ItemQuery.hpp"
#include "RssParser.hpp"
#include "models.hpp"
#include "ui/MainWindow.hpp"
#include <QApplication>
#include <QPushButton>
#include <cstddef>
#include <curl/curl.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sqlite3.h>
#include <tinyxml2.h>

#define DBLOCATION "/home/chetan/Code/rssClient/rss.db"

#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow *mainWindow = new MainWindow();
  mainWindow->resize(1024,768);
  return app.exec();
}
