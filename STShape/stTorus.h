#ifndef __ST_TORUS_H__
#define __ST_TORUS_H__

#include "stShape.h"

class STTorus : public STShape
{
private:
	GLfloat r1;		//Radius of the central circle
	GLfloat r2;		//Radius of the torus cross-section
	GLint numSlices;	//The number of vertices in each cross-section
	GLint numSections;	//The number of cross-sections
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	void genNormals() override;
	
	STTriangleBatch* tBatch;
	
	void genTriangles();

public:
	STTorus(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat r1, GLfloat r2, GLint numSlices, GLint numSections);	//A torus is surprisingly rigidly, yet easily defined.
	~STTorus() override;

	GLint getNumSections() {return this->numSections;};
	GLint getNumSlices() {return this->numSlices;};
	GLfloat getOuterRadius() {return this->r1;};
	GLfloat getInnerRadius() {return this->r2;};
	
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


#endif //__ST_TORUS_H__
