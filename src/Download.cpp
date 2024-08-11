/* curl write callback, to fill tidy's input buffer...  */
#include <sys/types.h>
#include <curl/curl.h>
#include "Download.hpp"

uint Download::write_cb(char *in, uint size, uint nmemb, MemoryStruct *mem) {
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

void Download::downloadUrl(std::string url, MemoryStruct *output) {

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
