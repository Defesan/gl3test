#ifndef __ST_RECT_H__
#define __ST_RECT_H__

#include "stShape.h"

class Rect : public Shape
{
private:
	GLfloat width;
	GLfloat height;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	
public:
	Rect(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height);
	Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height) : Rect(originX, originY, 0.0f, width, height) {};
	Rect(GLfloat originX, GLfloat originY, GLfloat edge) : Rect(originX, originY, 0.0f, edge, edge) {};
	~Rect() override;
	
	GLfloat* getVerts() override {return this->verts.data();};
	GLubyte* getColors() override {return this->colors.data();};
	GLushort* getIndices() override {return this->indices.data();};
	
	GLfloat getOriginX() override {return this->origin->getX();};
	GLfloat getOriginY() override {return this->origin->getY();};
	GLfloat getOriginZ() override {return this->origin->getZ();};
	
	GLfloat getVelX() override {return this->velocity->getX();};
	GLfloat getVelY() override {return this->velocity->getY();};
	GLfloat getVelZ() override {return this->velocity->getZ();};
	
	GLfloat getWidth() {return this->width;};
	GLfloat getHeight() {return this->height;};
	
	
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
