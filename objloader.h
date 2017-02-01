#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "rawmodel.h"
#include "loader.h"

using namespace std;


class ObjLoader
{
public:
    static RawModel* loadObjModel(string fileContent, Loader *loader);
};

#endif // OBJLOADER_H
