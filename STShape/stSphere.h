#ifndef __ST_SPHERE_H__
#define __ST_SPHERE_H__

#include "stShape.h"


class Sphere : public Shape
{
private:
	GLfloat radius;	
	GLushort numLayers;
	GLushort numSlices;
	
	int frame;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
public:
	Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLushort numLayers, GLushort numSlices);
	Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius) : Sphere(originX, originY, originZ, radius, 6, 12) {};
	~Sphere() override;
	
	GLfloat* getVerts() override {return this->verts.data();};
	GLubyte* getColors() override {return this->colors.data();};
	GLushort* getIndices() override {return this->indices.data();};
	
	GLushort getNumLayers() {return this->numLayers;};
	GLushort getNumSlices() {return this->numSlices;};
	
	GLfloat getOriginX() override {return this->origin->getX();};
	GLfloat getOriginY() override {return this->origin->getY();};
	GLfloat getOriginZ() override {return this->origin->getZ();};
	
	GLfloat getVelX() override {return this->velocity->getX();};
	GLfloat getVelY() override {return this->velocity->getY();};
	GLfloat getVelZ() override {return this->velocity->getZ();};
	
	bool setColors(GLubyte** colors) override;
	void setColorToGLColor() override;
	
	void setBounds(GLfloat xPos, GLfloat xNeg, GLfloat yPos, GLfloat yNeg, GLfloat zPos, GLfloat zNeg) override;
	
	void render() override;
	void update() override;
	
	void setVelocity(GLfloat velX, GLfloat velY, GLfloat velZ) override;
	void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) override;
	void translate(GLfloat x, GLfloat y, GLfloat z) override;


};



#endif
