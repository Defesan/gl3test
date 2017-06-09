#include "stCircle.h"

Circle::Circle(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLushort numVerts)
{

	this->origin = new STVec3f();
	
	this->radius = radius;
	this->numSlices = numVerts;
	
	this->velocity = new STVec3f();
	
	this->boundPos = new STVec3f(100.0f, 100.0f, 100.0f);
	this->boundNeg = new STVec3f(-100.0f, -100.0f, -100.0f);

	this->genVerts();
	this->genIndices();
	this->genColors();
	
	this->translate(originX, originY, originZ);	
}

Circle::~Circle()
{

}

void Circle::genVerts()
{
	GLfloat sliceAngle = (2 * PI) / (GLfloat)this->numSlices; 

	this->verts.push_back(0.0f);
	this->verts.push_back(0.0f);
	this->verts.push_back(0.0f);
	
	for(int i = 1; i < (this->numSlices + 1); i++)
	{
		GLfloat currentAngle = sliceAngle * (i - 1);
		
		this->verts.push_back(sin(currentAngle) * this->radius);
		this->verts.push_back(cos(currentAngle) * this->radius);
		this->verts.push_back(0.0f);
	}
}

void Circle::genIndices()
{
	
	for(int i = 0; i < (this->numSlices - 1); i++)
	{
		this->indices.push_back(0);
		this->indices.push_back(i + 1);
		this->indices.push_back(i + 2);
	}
	
	this->indices.push_back(0);
	this->indices.push_back(this->numSlices);
	this->indices.push_back(1);
}

void Circle::genColors()
{
	GLubyte red = 0;
	GLubyte green = 0;
	GLubyte blue = 0;
	GLubyte alpha = 255;
	
	int delta = 765 / (this->numSlices + 1);
	
	if(!delta)
	{
		delta = 1;
	
	}
	
	for(int i = 0; i < (this->numSlices + 1); i++)
	{
		this->colors.push_back(red);
		this->colors.push_back(green);
		this->colors.push_back(blue);
		this->colors.push_back(alpha);
		
		//Generate the colors for the next vertex.
		//If red hasn't been maxed out...
		if(red < 255)
		{
			//and there's room for a full delta...
			if((255 - red) > delta)
			{
				//Add the full delta.
				red += delta;
			}
			else	//There's still room, but not ENOUGH room
			{
				int overflow = delta - (255 - red);
				red = 255;
				green += overflow;
			}
		
		}
		else if(green < 255)
		{
			if((255 - green) > delta)
			{
				green += delta;
			}
			else	
			{
				int overflow = delta - (255 - green);
				green = 255;
				blue += overflow;
			}
		}
		else if(blue < 255)
		{
			if((255 - blue) > delta)
			{
				blue += delta;
			}
			else	
			{
				blue = 255;
			}
		}
		else
		{
			std::cout << "Edge case... But this shouldn't happen. All the colors got filled up." << std::endl;
		}
	}
}

bool Circle::setColors(GLubyte** colors)
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
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, this->colors.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, this->verts.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, this->indices.data());

}

void Circle::update()
{
	//This acts as a sort of default behavior, really, but external calls can modify it considerably. Still only 'bout as smart as a Roomba...
	
	if(((this->origin->getX() + this->radius + this->velocity->getX()) > this->boundPos->getX()) || ((this->origin->getX() - this->radius + this->velocity->getX()) < this->boundNeg->getX()))
	{
		this->velocity->mulX(-1);
	}
	if(((this->origin->getY() + this->radius + this->velocity->getY()) > this->boundPos->getY()) || ((this->origin->getY() - this->radius + this->velocity->getY()) < this->boundNeg->getY()))
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

void Circle::setVelocity(GLfloat velX, GLfloat velY, GLfloat velZ)
{
	this->velocity->setX(velX);
	this->velocity->setY(velY);
	this->velocity->setZ(velZ);
}

void Circle::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->velocity->addX(accX);
	this->velocity->addY(accY);
	this->velocity->addZ(accZ);
}


void Circle::translate(GLfloat x, GLfloat y, GLfloat z)
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

void Circle::setBounds(GLfloat xPos, GLfloat xNeg, GLfloat yPos, GLfloat yNeg, GLfloat zPos, GLfloat zNeg)
{
	this->boundPos->setX(xPos);
	this->boundPos->setY(yPos);
	this->boundPos->setZ(zPos);
	
	this->boundNeg->setX(xNeg);
	this->boundNeg->setY(yNeg);
	this->boundNeg->setZ(zNeg);

}
