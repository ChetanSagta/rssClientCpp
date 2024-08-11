#include "models.hpp"
#include <string>
class Download{
private:
  uint static write_cb(char*, uint, uint, MemoryStruct*);

public:
  void downloadUrl(std::string, MemoryStruct*);
};
