#ifndef __ST_UTIL_H__
#define __ST_UTIL_H__

#include <string>
#include <fstream>

#ifndef PI	//I really need a constants header...
#define PI 3.1415926f
#endif

std::string fileToString(const std::string filePath);
float degreesToRadians(float degrees);


#endif //__ST_UTIL_H__
