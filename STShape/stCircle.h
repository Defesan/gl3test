#ifndef __ST_CIRCLE_H__
#define __ST_CIRCLE_H__

#include "stShape.h"



class Circle : public Shape
{
private:
	GLfloat radius;
	GLushort numSlices;
	
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> colors;
	std::vector<GLuint> indices;
	
	void genVerts() override;
	void genIndices() override;
	void genColors() override;
	void genNormals() override;
	
public:
	
	Circle(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLushort numVerts);
	Circle(GLfloat originX, GLfloat originY, GLfloat radius) : Circle(originX, originY, 0.0f, radius, 12) {};
	~Circle() override;
	
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

	void render() override;
	void update() override;
	
	void accelerate(GLfloat accX, GLfloat accY, GLfloat accZ) override;
	void translate(GLfloat x, GLfloat y, GLfloat z) override;
};


#endif
