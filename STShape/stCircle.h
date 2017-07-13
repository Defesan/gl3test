#ifndef __ST_CIRCLE_H__
#define __ST_CIRCLE_H__

#include "stShape.h"



class STCircle : public STShape
{
private:
	GLfloat radius;
	GLuint numSlices;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	void genNormals() override;
	
public:
	
	STCircle(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLuint numVerts);
	STCircle(GLfloat originX, GLfloat originY, GLfloat radius) : STCircle(originX, originY, 0.0f, radius, 12) {};
	~STCircle() override;
	
	bool setColors(std::vector<GLfloat> colorArray) override;
	
	void setColorToGLColor() override;
	
	void setOrigin(STVec3f* origin) override {this->origin = origin;};
	void setAcceleration(STVec3f* accel) override {this->acceleration = accel;};
	void setVelocity(STVec3f* velocity) override {this->velocity = velocity;};
	
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
	
	
	GLfloat getRadius() {return this->radius;};
	GLuint getNumSlices() {return this->numSlices;};	

	void render() override;
	void update() override;
	
	void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) override;
	void translate(GLfloat x, GLfloat y, GLfloat z) override;
	void translate(STVec3f* direction) { this->translate(direction->getX(), direction->getY(), direction->getZ()); }; 
};


#endif
