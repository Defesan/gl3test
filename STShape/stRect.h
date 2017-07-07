#ifndef __ST_RECT_H__
#define __ST_RECT_H__

#include "stShape.h"

class Rect : public Shape
{
private:
	GLfloat width;
	GLfloat height;
	
	//Seems I need these after all...
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> colors;
	std::vector<GLuint> indices;
	
	bool batchStarted;
	
	/*
		I have two options:
		1) Figure out how to use indices with the Primitive batch function(actually shouldn't be that hard...)
		2) Change Rect so that it generates the full lists of vertices, normals, and colors, as they're supposed to be displayed...
		Going for 2, first.
	*/
	
	void genVerts() override;
	void genNormals() override;
	void genColors() override;
	void genIndices() override;
	
public:
	Rect(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height);
	Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height) : Rect(originX, originY, 0.0f, width, height) {};
	Rect(GLfloat originX, GLfloat originY, GLfloat edge) : Rect(originX, originY, 0.0f, edge, edge) {};
	~Rect() override;
	
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
	
	//Shoulda remembered that if you have an attribute, it's best to have at least a getter for it.
	GLfloat getWidth() {return this->width;};
	GLfloat getHeight() {return this->height;};
	
	void setWidth(GLfloat newWidth) {this->width = newWidth;};
	void setHeight(GLfloat newHeight) {this->height = newHeight;};
	
	void render() override;
	void update() override;
	
	void translate(GLfloat x, GLfloat y, GLfloat z) override;
	void translate(STVec3f* direction) { this->translate(direction->getX(), direction->getY(), direction->getZ()); }; 
	void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) override;
};



#endif
