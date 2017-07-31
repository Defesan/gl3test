#ifndef __ST_CYLINDER_H__
#define __ST_CYLINDER_H__

#include "stShape.h"

//Time to work on the four GLTools shapes I don't have: cylinder, cube, cone, and disc

class STCylinder : public STShape
{
private:
	GLfloat height;
	GLfloat topRadius;
	GLfloat bottomRadius;	//This allows for some more interesting shapes, and a more general implementation. In fact... I think I can use this to make a cone!
	GLint numSlices;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	void genNormals() override;

public:
	STCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat topRadius, GLfloat bottomRadius, GLint numSlices);
	STCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numSlices) : STCylinder(x, y, z, height, radius, radius, numSlices) {};
	~STCylinder() override;
	
	GLfloat getHeight() {return this->height;};
	GLfloat getTopRadius() {return this->topRadius;};
	GLfloat getBottomRadius() {return this->bottomRadius;};
	GLint getNumSlices() {return this->numSlices;};
	
	STVec3f* getOrigin() override {return this->origin;};
	
	GLfloat getOriginX() override {return this->origin->getX();};
	GLfloat getOriginY() override {return this->origin->getY();};
	GLfloat getOriginZ() override {return this->origin->getZ();};
	
	STVec3f* getVelocity() override {return this->velocity;};
	
	GLfloat getVelX() override {return this->velocity->getX();};
	GLfloat getVelY() override {return this->velocity->getY();};
	GLfloat getVelZ() override {return this->velocity->getZ();};
	
	STVec3f* getAcceleration() override {return this->acceleration;};
	
	GLfloat getAccX() override {return this->acceleration->getX();};
	GLfloat getAccY() override {return this->acceleration->getY();};
	GLfloat getAccZ() override {return this->acceleration->getZ();};
	
	bool setColors(std::vector<GLfloat> colorArray) override;
	void setColorToGLColor() override;
	
	void setOrigin(STVec3f* origin) override {this->origin = origin;};
	void setVelocity(STVec3f* velocity) override {this->velocity = velocity;};
	void setAcceleration(STVec3f* accel) override {this->acceleration = accel;};
	
	void render() override;
	void update() override;
	
	void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) override;
	void translate(GLfloat x, GLfloat y, GLfloat z) override;
	void translate(STVec3f* direction) { this->translate(direction->getX(), direction->getY(), direction->getZ()); };
	
	void printVerts();
	void printIndices();
};


#endif //__ST_CYLINDER_H__
