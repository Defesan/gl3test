#include "stRect.h"

STRect::STRect(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height)
{	
	this->origin = new STVec3f(originX, originY, originZ);
	this->velocity = new STVec3f(0.0f, 0.0f, 0.0f);
	this->acceleration = new STVec3f(0.0f, 0.0f, 0.0f);
	
	this->width = width;
	this->height = height;
	
	this->batch = new STPrimitiveBatch(0);
	
	this->batch->begin();
	
	this->genVerts();
	this->genNormals();
	this->genColors();
	this->genIndices();
	
	this->batch->finalize();
	
}

STRect::~STRect()
{

}

void STRect::genVerts()
{
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2;

	this->verts.clear();
	this->verts.push_back(this->origin->getX() - offsetX);
	this->verts.push_back(this->origin->getY() + offsetY);
	this->verts.push_back(this->origin->getZ());
	
	this->verts.push_back(this->origin->getX() + offsetX);
	this->verts.push_back(this->origin->getY() + offsetY);
	this->verts.push_back(this->origin->getZ());
	
	this->verts.push_back(this->origin->getX() - offsetX);
	this->verts.push_back(this->origin->getY() - offsetY);
	this->verts.push_back(this->origin->getZ());

	this->verts.push_back(this->origin->getX() + offsetX);
	this->verts.push_back(this->origin->getY() - offsetY);
	this->verts.push_back(this->origin->getZ());
	
	this->batch->copyVertexData(this->verts);
	
}

void STRect::genColors()
{
	for(int i = 0; i < 4; i++)
	{
		this->colors.push_back(0.05f * i);
		this->colors.push_back(0.07f * i);
		this->colors.push_back(0.1f * i);
		this->colors.push_back(1.0f);
	}
	this->batch->copyColorData(this->colors);
}

void STRect::genNormals()
{
	//Actually, this one seems reasonable. Just use 0,0,1. It's a flat rectangle on the xy plane.
	this->norms.push_back(0.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(1.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(1.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(1.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(0.0f);
	this->norms.push_back(1.0f);

	this->batch->copyNormalData(this->norms);
}

void STRect::genIndices()
{
	this->indices.push_back(0);
	this->indices.push_back(1);
	this->indices.push_back(2);
	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(3);

	this->batch->copyIndexData(this->indices);
}

bool STRect::setColors(std::vector<GLfloat> colorArray)
{
	if(!colorArray.empty())
	{
		this->colors.clear();
		std::vector<GLfloat>::iterator iter = colorArray.begin();
		for(; iter != colorArray.end(); iter++)
		{
			this->colors.push_back(*iter);			
		}
		return true;
	}
	return false;
}

void STRect::setColorToGLColor()
{
	GLfloat colors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glGetFloatv(GL_CURRENT_COLOR, colors);
	
	for(int i = 0; i < 16; i++)
	{
		this->colors.push_back(colors[i % 4]);
	}
}

void STRect::render()
{
	this->batch->draw();
}


void STRect::update()
{
	this->velocity->addVec3f(this->acceleration);
	this->translate(this->velocity);
	this->render();
}


void STRect::translate(GLfloat x, GLfloat y, GLfloat z)
{
	//Update the origin
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	//...and the verts
	this->genVerts();
}

void STRect::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->acceleration->setX(accX);
	this->acceleration->setY(accY);
	this->acceleration->setZ(accZ);
}
