#ifndef __ST_SHADER_H__
#define __ST_SHADER_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <string>
#include <fstream>
#include <cstdarg>

#include "stUtil.h"
#include "stUniform.h"

#define SHADER_ERROR 0

enum ST_SHADER_ATTRIBUTE {ST_ATTRIBUTE_VERTEX = 0, ST_ATTRIBUTE_COLOR, ST_ATTRIBUTE_NORMAL, ST_ATTRIBUTE_TEXTURE0, 
                          ST_ATTRIBUTE_TEXTURE1, ST_ATTRIBUTE_TEXTURE2, ST_ATTRIBUTE_TEXTURE3, ST_ATTRIBUTE_LAST};

enum ST_STOCK_SHADER {ST_SHADER_IDENTITY = 0, ST_SHADER_FLAT, ST_SHADER_SHADED, ST_SHADER_LIGHT};

class STShaderManager
{
private:
	//What do I need in here? a vector of the 'names' of the shaders...
	std::vector<GLuint> activeShaderPointers;

public:
	STShaderManager();		//I think we can safely initialize the full shader library(which will be fairly small to start, but I'll keep adding to it) in the constructor.
	~STShaderManager();
	
	GLuint getShader(GLuint index) {return this->activeShaderPointers[index];};
	GLuint getStockShader(ST_STOCK_SHADER shader) {return this->getShader((GLuint)shader);};	//All of the custom shaders will be added AFTER the stock shaders, so the stock shader indices are valid.
	
	void runShader(GLuint shaderHandle, std::vector<STUniform*> uniforms);
	
	bool loadShaderSrc(std::string shaderSoource, GLuint shaderHandle);
	
	//Continuing my STL translation of the old code, we'll be using strings, not c-strings. Pretty much standard(and often best) practice in C++ now.
	//Successfully reduced loadShaderPair to a single in-header return.
	GLuint loadShaderPair(std::string vertexShaderFile, std::string fragShaderFile) {return this->loadShaderPairSrc(fileToString(vertexShaderFile), fileToString(fragShaderFile));};
	GLuint loadShaderPairSrc(std::string vertexShaderSrc, std::string fragShaderSrc);
	
	GLuint loadShaderPairWithAttributes(std::string vertexShaderFile, std::string fragShaderFile, ...);
	GLuint loadShaderPairSrcWithAttributes(std::string vertexShaderSrc, std::string fragShaderSrc, ...);
};


#endif //__ST_SHADER_H__
