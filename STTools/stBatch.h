#ifndef __ST_BATCH_H__
#define __ST_BATCH_H__

/*
	I can certainly understand the virtue of having a base class for these batches...but calling it BatchBase is a bit much.
	Also, a trick I recall from my compilers class, sometimes you want to know the type of subclass you're working with.
 */
 
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include "../STLinear/stVector.h"
#include "stShader.h"

enum BATCH_TYPE {TRIANGLE, PRIMITIVE};

class STBatch
{
protected:
	BATCH_TYPE type;

	std::vector<GLfloat> vertData;
	std::vector<GLfloat> normData;
	std::vector<std::vector<GLfloat>> texCoordData;
	std::vector<GLfloat> colorData;	
	std::vector<GLuint> indexData;
	
	GLuint vertID;
	GLuint normID;
	GLuint colorID;
	std::vector<GLuint> texIDs;
	GLuint indexID;
	
	GLuint vertexBufferArrayID;
	
	 
public:
	virtual void draw() = 0;
}; 


#endif //__ST_BATCH_H__
