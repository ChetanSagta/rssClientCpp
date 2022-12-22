#pragma once
#include "DBConnection.hpp"
#include "models.cpp"
class ImageQuery{

  void insertQuery(int,int);


private:
    Image m_image;
    DBConnection connection;
};
