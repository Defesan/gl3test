#include "stCylinder.h"

STCylinder::STCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat topRadius, GLfloat bottomRadius, GLint numSlices)
{
	this->batch = new STPrimitiveBatch(0);
	this->origin = new STVec3f(x, y, z);
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->height = height;
	this->topRadius = topRadius;
	this->bottomRadius = bottomRadius;
	this->numSlices = numSlices;
	
	this->batch->begin();
	
	this->genVerts();
	this->genIndices();
	this->genColors();
	this->genNormals();
	
	this->batch->finalize();

}

STCylinder::~STCylinder()
{

}

void STCylinder::genVerts()
{


	this->batch->copyVertexData(this->verts);
}

void STCylinder::genIndices()
{


	this->batch->copyIndexData(this->indices);
}

void STCylinder::genColors()
{
	int numVerts = (this->numSlices * 2) + 2;

	GLfloat red = 0.2f;
	GLfloat green = 0.2f;
	GLfloat blue = 0.2f;
	GLfloat alpha = 1.0f;
	
	for(int i = 0; i < numVerts; i++)
	{
		this->colors.push_back(red);
		this->colors.push_back(green);
		this->colors.push_back(blue);
		this->colors.push_back(alpha);
	}
	this->batch->copyColorData(this->colors);

}

void STCylinder::genNormals()
{

	this->batch->copyNormalData(this->norms);
}

void STCylinder::setColorToGLColor()
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

bool STCylinder::setColors(std::vector<GLfloat> colorArray)
{
	this->colors.clear();
	std::vector<GLfloat>::iterator iterSource = colorArray.begin();
	std::vector<GLfloat>::iterator iterDest = this->colors.begin();
	for(; iterDest != this->colors.end(); iterDest++, iterSource++)
	{
		if(iterSource == colorArray.end())
		{
			iterSource = colorArray.begin();
		}
		*iterDest = *iterSource;
	}
	return false;
}

void STCylinder::render()
{
	this->batch->draw();
}

void STCylinder::update()
{
	this->velocity->addVec3f(this->acceleration);	
	this->translate(this->velocity);
	this->render();
}

void STCylinder::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->acceleration->setX(accX);
	this->acceleration->setY(accY);
	this->acceleration->setZ(accZ);
}


void STCylinder::translate(GLfloat x, GLfloat y, GLfloat z)
{
	//Update the origin
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	//...and the verts
	this->genVerts();
	
}
