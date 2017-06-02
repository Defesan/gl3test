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
