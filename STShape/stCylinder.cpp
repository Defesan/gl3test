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
	GLfloat verticalOffset = this->height / 2;
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) / this->numSlices;
	
	//Generate the top vertex
	this->verts.push_back(this->origin->getX());
	this->verts.push_back(this->origin->getY());
	this->verts.push_back(this->origin->getZ() + verticalOffset);
	
	//Generate the top ring(if applicable)
	if(this->topRadius > 0.0f)
	{
		for(int i = 0; i < this->numSlices; i++)
		{
			this->verts.push_back(this->origin->getX() + (this->topRadius * sin(theta)));
			this->verts.push_back(this->origin->getY() + (this->topRadius * cos(theta)));
			this->verts.push_back(this->origin->getZ() + verticalOffset);
			theta += dTheta;
		}
		theta = 0.0f;	
	}
	
	//Generate the bottom ring(if applicable)
	if(this->bottomRadius > 0.0f)
	{
		for(int i = 0; i < this->numSlices; i++)
		{
			this->verts.push_back(this->origin->getX() + (this->bottomRadius * sin(theta)));
			this->verts.push_back(this->origin->getY() + (this->bottomRadius * cos(theta)));
			this->verts.push_back(this->origin->getZ() - verticalOffset);
			theta += dTheta;
		}
	}
	
	//Generate the bottom vertex
	this->verts.push_back(this->origin->getX());
	this->verts.push_back(this->origin->getY());
	this->verts.push_back(this->origin->getZ() - verticalOffset);
	

	this->batch->copyVertexData(this->verts);
}

void STCylinder::genIndices()
{
	//This bit's tricky because of how general I made it. Regretting that decision now, but this'll make it VERY versatile.
	//Though it looks like the GLTools version ALMOST went this far.
	//Turns out the algorithm's the same for both types of cones.
	if((this->topRadius == 0.0f && this->bottomRadius > 0.0f) || (this->topRadius > 0.0f && this->bottomRadius == 0.0f))
	{
		//Here we have a typical cone with a point on the top and a circle, closed, at the bottom.
		//First we generate the cone...
		for(int i = 0; i < this->numSlices; i++)
		{
			int k = 0;
			if(i < (this->numSlices - 1))
			{
				k = i + 2;
			}
			else
			{
				k = 1;
			}
		
			this->indices.push_back(0);
			this->indices.push_back(i + 1);
			this->indices.push_back(k);
		}
		
		//Next we create the bottom.
		//find the index of the last vertex:
		int last = this->numSlices + 1;	
		
		for(int i = 0; i < this->numSlices; i++)
		{
			int k = 0;
			if(i < (this->numSlices - 1))
			{
				k = i + 2;
			}
			else
			{
				k = 1;
			}
			
			//I think I have to invert the last two. We'll see.
			this->indices.push_back(last);
			this->indices.push_back(k);
			this->indices.push_back(i + 1);
		}
		
		
	
	}
	else if(this->topRadius > 0.0f && this->bottomRadius > 0.0f)
	{
		//Here we have some type of cylindrical solid with circles at the top and the bottom.
		
		//First, we create the top. Same as creating the cone in the first case.
		for(int i = 0; i < this->numSlices; i++)
		{
			int k = 0;
			if(i < (this->numSlices - 1))
			{
				k = i + 2;
			}
			else
			{
				k = 1;
			}
		
			this->indices.push_back(0);
			this->indices.push_back(i + 1);
			this->indices.push_back(k);
		}
		
		//Next, we connect the top ring to the bottom ring.
		//Now, here I think RSW made a mistake. See, his cylinder has multiple layers, like a sphere. But the difference between the radii of the circles that make up
		//the layers is linear. It will ALWAYS be a straight line. Adding more vertices simply adds geometrical complexity, and can't be seen. I think. Pretty sure
		//that even TEXTURES wouldn't be affected, though you could create more colorful cylinders without textures. Adding more slices, sure, that increases the roundness of the cylinder,
		//but more layers?
		for(int i = 0; i < this->numSlices; i++)
		{
			int k = 0;
			int j = 0;
			if(i < (this->numSlices - 1))
			{
				k = i + 2;
				j = i + 2 + this->numSlices;
			}
			else
			{
				k = 1;
				j = this->numSlices + 1;
			}
			//So here we have the same setup as STSphere.
			this->indices.push_back(i + 1);
			this->indices.push_back(i + 1 + this->numSlices);
			this->indices.push_back(j);
			this->indices.push_back(i + 1);
			this->indices.push_back(j);
			this->indices.push_back(k);
			
		}
		
		//Finally, we create the bottom.
		//Same as before.
		int last = 2 * this->numSlices + 1;	
		
		for(int i = this->numSlices; i < last; i++)
		{
			int k = 0;
			if(i < (last - 1))
			{
				k = i + 2;
			}
			else
			{
				k = this->numSlices;
			}
			
			//I think I have to invert the last two. We'll see.
			this->indices.push_back(last);
			this->indices.push_back(k);
			this->indices.push_back(i + 1);
		}
	}
	else if(this->topRadius == 0.0f && this->bottomRadius == 0.0f)
	{
		//Here we have...a line segment. This reminds me of the scene in Grim Fandango where Manny asks the balloon artist for a dead worm.
		//That said... GL_TRIANGLES wants at least three indices...
		this->indices.push_back(0);
		this->indices.push_back(1);
		this->indices.push_back(0);
		//It's a degenerate triangle, but hey. I'm curious to see if it'll work!
	}
	else
	{
		//Well, here, we have a problem. This basically means that one or both of the radii are *negative*. We shouldn't even GET here.
		std::cerr << "Warning! Negative distances, such as radii, may cause universal collapse!" << std::endl;
	}

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
	//This is why I made this. Where do the normals on a vertex point when they're all on 90 degree corners?
	//Hmmm... I wonder if I've been doing normals wrong. Here, the first two coordinates of any normal are the coordinates of its vertex.
	//The z coordinate is the bottom radius minus the top radius. 
	
	int numVerts = (this->numSlices * 2) + 2;
	int currPos = 0;
	GLfloat zNorm = this->bottomRadius - this->topRadius;
	
	if(abs(zNorm) < 0.00001f)
	{
		zNorm = 0.0f;	
	}
	
	for(int i = 0; i < numVerts; i++)
	{
		this->norms.push_back(this->verts[currPos]);
		currPos++;
		this->norms.push_back(this->verts[currPos]);
		currPos++;
		this->norms.push_back(zNorm);
		currPos++;
	}
	
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

void STCylinder::printVerts()
{
	std::vector<GLfloat>::iterator iter = this->verts.begin();
	
	int i = 0;
	
	for(; iter != this->verts.end(); iter += 3, i++)
	{
		std::cout << "Vert " << i << ") X = " << *iter << " Y = " << *(iter + 1) << " Z = " << *(iter + 2) << std::endl;
	}
}


void STCylinder::printIndices()
{
	std::vector<GLuint>::iterator iter = this->indices.begin();
	
	int i = 0;
	
	for(; iter != this->indices.end(); iter += 3, i++)
	{
		std::cout << "Tri " << i << ") " << *iter << " " << *(iter + 1) << " " << *(iter + 2) << std::endl;
	}
}
