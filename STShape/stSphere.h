#ifndef __ST_SPHERE_H__
#define __ST_SPHERE_H__

#include "stShape.h"


class STSphere : public STShape
{
private:
	GLfloat radius;	
	GLuint numLayers;
	GLuint numSlices;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	void genNormals() override;
	
public:
	STSphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLuint numLayers, GLuint numSlices);
	STSphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius) : STSphere(originX, originY, originZ, radius, 6, 12) {};
	~STSphere() override;
	
	GLuint getNumLayers() {return this->numLayers;};
	GLuint getNumSlices() {return this->numSlices;};
	GLfloat getRadius() {return this->radius;};
	
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
};



#endif
