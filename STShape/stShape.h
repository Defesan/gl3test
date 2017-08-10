#ifndef __ST_SHAPE_H__
#define __ST_SHAPE_H__

#include <cmath>
#include <iostream>
#include <vector>

#include "../STLinear/stVector.h"
#include "../STTools/stPrimitiveBatch.h"
#include "../STTools/stTriangleBatch.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef PI
#define PI 3.1415926
#endif

//Ah, the prototypical abstract class. But... I am making shapes here, so I need one.
class STShape
{
protected:
	//Duh... We use batches now.
	STPrimitiveBatch* batch;
	
	//Seems I need these after all...
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
	virtual void setVelocity(STVec3f* velocity) = 0;
	virtual void setAcceleration(STVec3f* accel) = 0;
	
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
	
	//With batches, these actually become quite easy...
	virtual void render() = 0;
	virtual void update() = 0;
	
	//...but these might be a bit harder. Or maybe not, I dunno.
	virtual void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) = 0;
	virtual void translate(GLfloat x, GLfloat y, GLfloat z) = 0;
	

	virtual ~STShape() {};
};


#endif
