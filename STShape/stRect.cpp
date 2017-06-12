#include "stRect.h"

Rect::Rect(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height)
{	
	this->origin = new STVec3f();
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->width = width;
	this->height = height;
	
	this->batch = new STPrimitiveBatch(0);
	
	//That should be all the members initialized. Now the really hard part.
	
	this->genVerts();
	this->genIndices();
	this->genNormals();
	this->genColors();
	
	//Okay, that wasn't hard *here*, but it'll be a bit more difficult later...
	
	this->translate(originX, originY, originZ);
}

Rect::~Rect()
{

}

void Rect::genVerts()
{
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2;
	
	std::vector<GLfloat> verts;
	
	verts.push_back(-offsetX);
	verts.push_back(offsetY);
	verts.push_back(0.0f);
	verts.push_back(offsetX);
	verts.push_back(offsetY);
	verts.push_back(0.0f);
	verts.push_back(-offsetX);
	verts.push_back(-offsetY);
	verts.push_back(0.0f);
	verts.push_back(offsetX);
	verts.push_back(-offsetY);
	verts.push_back(0.0f);

	this->batch.copyVertexData(verts);
}

void Rect::genIndices()
{
	this->indices.push_back(0);
	this->indices.push_back(1);
	this->indices.push_back(2);
	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(3);
	
}

void Rect::genColors()
{
	for(int i = 0; i < 4; i++)
	{
		this->colors.push_back(20 * i);
		this->colors.push_back(30 * i);
		this->colors.push_back(50 * i);
		this->colors.push_back(255);
	}
}

bool Rect::setColors(GLubyte** colors)
{
	if(colors)
	{
		this->colors.clear();
		//Yes, I know. Not good code. I need to pull in both the number of vertices and the size of the color array, but for now...
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				this->colors.push_back(colors[i][j]);
			}
		}
		return true;
	}
	return false;
}

void Rect::setColorToGLColor()
{
	//These colors are typically floats, which presents a problem....
	GLfloat colors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GLubyte ubColors[4] = {0, 0, 0, 0};
	glGetFloatv(GL_CURRENT_COLOR, colors);
	
	//Convert from float to ubyte
	for(int i = 0; i < 4; i++)
	{
		ubColors[i] = (GLubyte)(colors[i] * 255);		//should work?
	}
	this->colors.clear();
	for(int i = 0; i < 16; i++)
	{
		this->colors.push_back(ubColors[i % 4]);
	}
}

void Rect::render()
{
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, this->colors.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, this->verts.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, this->indices.data());
}


void Rect::update()
{
	//This acts as a sort of default behavior, really, but external calls can modify it considerably. Still only 'bout as smart as a Roomba...
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2;
	
	if(((this->origin->getX() + offsetX + this->velocity->getX()) > this->boundPos->getX()) || ((this->origin->getX() - offsetX + this->velocity->getX()) < this->boundNeg->getX()))
	{
		this->velocity->mulX(-1);
	}
	if(((this->origin->getY() + offsetY + this->velocity->getY()) > this->boundPos->getY()) || ((this->origin->getY() - offsetY + this->velocity->getY()) < this->boundNeg->getY()))
	{
		this->velocity->mulY(-1);
	}
	if(((this->origin->getZ() + this->velocity->getZ()) > this->boundPos->getZ()) || ((this->origin->getZ() + this->velocity->getZ()) < this->boundNeg->getZ()))
	{
		this->velocity->mulZ(-1);
	}
	
	this->translate(this->velocity->getX(), this->velocity->getY(), this->velocity->getZ());
	this->render();

}

void Rect::setVelocity(GLfloat velX, GLfloat velY, GLfloat velZ)
{
	this->velocity->setX(velX);
	this->velocity->setY(velY);
	this->velocity->setZ(velZ);
}

void Rect::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->velocity->addX(accX);
	this->velocity->addY(accY);
	this->velocity->addZ(accZ);
}


void Rect::translate(GLfloat x, GLfloat y, GLfloat z)
{
	std::vector<GLfloat>::iterator iter;

	//Update the origin
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	//...and the verts
	for(iter = this->verts.begin(); iter != this->verts.end(); iter++)
	{
		*iter += x;
		iter++;
		*iter += y;
		iter++;
		*iter += z;
	}
	
}

void Rect::setBounds(GLfloat xPos, GLfloat xNeg, GLfloat yPos, GLfloat yNeg, GLfloat zPos, GLfloat zNeg)
{
	this->boundPos->setX(xPos);
	this->boundPos->setY(yPos);
	this->boundPos->setZ(zPos);
	
	this->boundNeg->setX(xNeg);
	this->boundNeg->setY(yNeg);
	this->boundNeg->setZ(zNeg);

}
