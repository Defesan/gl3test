#include "stCircle.h"

Circle::Circle(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLuint numVerts)
{
	this->batch = new STPrimitiveBatch(0);
	this->origin = new STVec3f(originX, originY, originZ);
	
	this->radius = radius;
	this->numSlices = numVerts;
	
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->batch->begin();

	this->genVerts();
	this->genIndices();
	this->genColors();
	this->genNormals();
	
	this->batch->finalize();
}

Circle::~Circle()
{

}

void Circle::genVerts()
{
	GLfloat sliceAngle = (2 * PI) / (GLfloat)this->numSlices; 
	this->verts.clear();
	this->verts.push_back(this->origin->getX());
	this->verts.push_back(this->origin->getY());
	this->verts.push_back(this->origin->getZ());
	
	for(GLuint i = 1; i < (this->numSlices + 1); i++)
	{
		GLfloat currentAngle = sliceAngle * (i - 1);
		
		this->verts.push_back(this->verts[0] + sin(currentAngle) * this->radius);
		this->verts.push_back(this->verts[1] + cos(currentAngle) * this->radius);
		this->verts.push_back(this->verts[2]);
	}
	
	this->batch->copyVertexData(this->verts);
}

void Circle::genIndices()
{
	
	for(GLuint i = 0; i < (this->numSlices - 1); i++)
	{
		this->indices.push_back(0);
		this->indices.push_back(i + 1);
		this->indices.push_back(i + 2);
	}
	
	this->indices.push_back(0);
	this->indices.push_back(this->numSlices);
	this->indices.push_back(1);
	
	this->batch->copyIndexData(this->indices);
}

void Circle::genColors()
{
	GLfloat red = 0.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;
	GLfloat alpha = 1.0f;
	
	GLfloat delta = 3.0f / (float)(this->numSlices + 1);	//Floating point division is costly, but here we're only doing it once.
	
	for(GLuint i = 0; i < (this->numSlices + 1); i++)
	{
		this->colors.push_back(red);
		this->colors.push_back(green);
		this->colors.push_back(blue);
		this->colors.push_back(alpha);
		
		//Generate the colors for the next vertex.
		//If red hasn't been maxed out...
		if(red < 1.0f)
		{
			//and there's room for a full delta...
			if((1.0f - red) > delta)
			{
				//Add the full delta.
				red += delta;
			}
			else	//There's still room, but not ENOUGH room
			{
				GLfloat overflow = delta - (1.0f - red);
				red = 1.0f;
				green += overflow;
			}
		
		}
		else if(green < 1.0f)
		{
			if((1.0f - green) > delta)
			{
				green += delta;
			}
			else	
			{
				GLfloat overflow = delta - (1.0f - green);
				green = 1.0f;
				blue += overflow;
			}
		}
		else if(blue < 1.0f)
		{
			if((1.0f - blue) > delta)
			{
				blue += delta;
			}
			else	
			{
				blue = 1.0f;
			}
		}
		else
		{
			std::cout << "Edge case... But this shouldn't happen. All the colors got filled up." << std::endl;
		}
	}
	this->batch->copyColorData(this->colors);
}

void Circle::genNormals()
{
	int vertCount = this->verts.size() / 3;
	for(int i = 0; i < vertCount; i++)
	{
		this->norms.push_back(0.0f);
		this->norms.push_back(0.0f);
		this->norms.push_back(1.0f);
	}
	this->batch->copyNormalData(this->norms);
}

bool Circle::setColors(std::vector<GLfloat> colorArray)
{
	return false;
}

void Circle::setColorToGLColor()
{
	GLfloat colors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GLubyte ubColors[4] = {0, 0, 0, 0};
	glGetFloatv(GL_CURRENT_COLOR, colors);
	int colorSize = this->colors.size();
	
	//Convert from float to ubyte
	for(int i = 0; i < 4; i++)
	{
		ubColors[i] = (GLubyte)(colors[i] * 255);		
	}
	this->colors.clear();
	for(int i = 0; i < colorSize; i++)
	{
		this->colors.push_back(ubColors[i % 4]);
	}
}

void Circle::render()
{
	this->batch->draw();

}

void Circle::update()
{
	this->velocity->addVec3f(this->acceleration);	
	this->translate(this->velocity);
	this->render();
}


void Circle::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->acceleration->setX(accX);
	this->acceleration->setY(accY);
	this->acceleration->setZ(accZ);
}


void Circle::translate(GLfloat x, GLfloat y, GLfloat z)
{
	//Update the origin
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	//...and the verts
	this->genVerts();
}


