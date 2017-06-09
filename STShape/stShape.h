#ifndef __ST_SHAPE_H__
#define __ST_SHAPE_H__

#include <cmath>
#include <iostream>
#include <vector>

#include "STLinear/stVec3f.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>


#define PI 3.1415926

//Ah, the prototypical abstract class. But... I am making shapes here, so I need one.
class Shape
{
protected:
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> colors;
	std::vector<GLuint> indices;
	
	//To be honest, EVERY shape will have these!
	STVec3f* origin;
	STVec3f* velocity;
	STVec3f* acceleration;
		
	virtual void genVerts() = 0;
	virtual void genIndices() = 0;
	virtual void genNormals() = 0;	//Now this should be fun: generative normal mapping?
	virtual void genColors() = 0;
	
public:
	
	virtual bool setColors(std::vector<GLfloat> colorArray) = 0;
	
	virtual void setColorToGLColor() = 0;
	
	virtual void setOrigin(STVec3f* origin) = 0;
	
	
	virtual std::vector<GLfloat> getColors() = 0;
	virtual std::vector<GLfloat> getVerts() = 0;
	virtual std::vector<GLfloat> getNorms() = 0;
	virtual std::vector<GLuint> getIndices() = 0;
	
	virtual STVec3f* getOrigin() = 0;
	
	virtual GLfloat getOriginX() = 0;
	virtual GLfloat getOriginY() = 0;
	virtual GLfloat getOriginZ() = 0;
	
	virtual STVec3f* getVelocity() = 0;
	
	virtual GLfloat getVelX() = 0;
	virtual GLfloat getVelY() = 0;
	virtual GLfloat getVelZ() = 0;
	
	virtual STVec3f* getAcceleration() = 0;
	
	virtual GLfloat getAccX() = 0;
	virtual GLfloat getAccY() = 0;
	virtual GLfloat getAccZ() = 0;
	
	virtual void render() = 0;
	virtual void update() = 0;
	
	//Normally, these objects won't have a velocity -- they just sit there.
	//When you want to set the velocity in one go, use setVelocity,
	//but if you want to ADD to the velocity, use accelerate.
	virtual void setVelocity(GLfloat velX, GLfloat velY, GLfloat velZ) = 0;
	virtual void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) = 0;
	virtual void translate(GLfloat x, GLfloat y, GLfloat z) = 0;
	

	virtual ~Shape() {};
};


#endif
