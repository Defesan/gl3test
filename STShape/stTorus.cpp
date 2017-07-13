#include "stTorus.h"

STTorus::STTorus(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat r1, GLfloat r2, GLint numSlices, GLint numSections)
{
	this->batch = new STPrimitiveBatch(0);
	this->origin = new STVec3f(originX, originY, originZ);
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->r1 = r1;
	this->r2 = r2;
	this->numSlices = numSlices;
	this->numSections = numSections;
	
	this->batch->begin();
	
	this->genVerts();
	this->genIndices();
	this->genColors();
	this->genNormals();
	
	this->batch->finalize();

}

STTorus::~STTorus()
{

}

void STTorus::genVerts()
{
	//TODO

}

void STTorus::genIndices()
{
	//TODO

}

void STTorus::genColors()
{
	//TODO

}

void STTorus::genNormals()
{
	//TODO

}

bool STTorus::setColors(std::vector<GLfloat> colorArray)
{
	//TODO
	return false;
}

void STTorus::setColorToGLColor()
{
	int colorSize = this->colors.size();
	this->colors.clear();
	
	GLfloat colors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glGetFloatv(GL_CURRENT_COLOR, colors);
		
	for(int i = 0; i < colorSize; i++)
	{
		this->colors.push_back(colors[i % 4]);
	}
}

void STTorus::render()
{
	this->batch->draw();
}

void STTorus::update()
{
	this->velocity->addVec3f(this->acceleration);
	this->translate(this->velocity);
	this->render();
}

void STTorus::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->acceleration->setX(accX);
	this->acceleration->setY(accY);
	this->acceleration->setZ(accZ);
}

void STTorus::translate(GLfloat x, GLfloat y, GLfloat z)
{
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	this->genVerts();
}
