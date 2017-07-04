#include "stUtil.h"

std::string fileToString(const std::string filePath)
{
	std::ifstream fileStream(filePath);
	
	fileStream.seekg(0, fileStream.end);
	int length = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);
	
	std::string result(length, ' ');
	fileStream.read(&result[0], length);
	
	return result;
}

float degreesToRadians(float degrees)
{
	//This might happen a lot, so...
	//PI / 180 = 0.017453292
	//Floating point multiplication is far easier than floating point division, 
	//and this will only ever be done to ONE value, namely PI/180. Don't even have to do the multiplication twice.
	//...It probably would have been optimized out by the compiler, anyway, but you never know for sure.
	return degrees * 0.017453292;
}
