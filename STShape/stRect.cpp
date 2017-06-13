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
	this->genNormals();
	this->genColors();
	this->genBatch();
	
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
	
	this->verts.push_back(-offsetX);
	this->verts.push_back(offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(offsetX);
	this->verts.push_back(offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(-offsetX);
	this->verts.push_back(-offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(offsetX);
	this->verts.push_back(-offsetY);
	this->verts.push_back(0.0f);
}

void Rect::genColors()
{
	for(int i = 0; i < 4; i++)
	{
		this->colors.push_back(0.05f * i);
		this->colors.push_back(0.07f * i);
		this->colors.push_back(0.1f * i);
		this->colors.push_back(1.0f);
	}
	
}

void Rect::genNormals()
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

}

void Rect::genBatch()
{
	std::vector<GLfloat> rawVerts;
	std::vector<GLfloat> rawNorms;
	std::vector<GLfloat> rawColors;
	
	//create the raw verts array
	rawVerts.push_back(this->verts[0]);
	rawVerts.push_back(this->verts[1]);
	rawVerts.push_back(this->verts[2]);
	rawVerts.push_back(this->verts[3]);
	rawVerts.push_back(this->verts[4]);
	rawVerts.push_back(this->verts[5]);
	rawVerts.push_back(this->verts[6]);
	rawVerts.push_back(this->verts[7]);
	rawVerts.push_back(this->verts[8]);
	rawVerts.push_back(this->verts[6]);
	rawVerts.push_back(this->verts[7]);
	rawVerts.push_back(this->verts[8]);
	rawVerts.push_back(this->verts[3]);
	rawVerts.push_back(this->verts[4]);
	rawVerts.push_back(this->verts[5]);
	rawVerts.push_back(this->verts[9]);
	rawVerts.push_back(this->verts[10]);
	rawVerts.push_back(this->verts[11]);
	
	//Ugh. There IS a better way of doing this. I think I'd rather create the verts, norms, and colors as vectors of Vec3fs and Vec4fs, then...
	//Write basically all the same lines, but in a more pleasing manner, like rawVerts.push_back(this->verts[0].getX();
	
	rawNorms.push_back(this->norms[0]);
	rawNorms.push_back(this->norms[1]);
	rawNorms.push_back(this->norms[2]);
	rawNorms.push_back(this->norms[3]);
	rawNorms.push_back(this->norms[4]);
	rawNorms.push_back(this->norms[5]);
	rawNorms.push_back(this->norms[6]);
	rawNorms.push_back(this->norms[7]);
	rawNorms.push_back(this->norms[8]);
	rawNorms.push_back(this->norms[6]);
	rawNorms.push_back(this->norms[7]);
	rawNorms.push_back(this->norms[8]);
	rawNorms.push_back(this->norms[3]);
	rawNorms.push_back(this->norms[4]);
	rawNorms.push_back(this->norms[5]);
	rawNorms.push_back(this->norms[9]);
	rawNorms.push_back(this->norms[10]);
	rawNorms.push_back(this->norms[11]);
	
	rawColors.push_back(this->colors[0]);
	rawColors.push_back(this->colors[1]);
	rawColors.push_back(this->colors[2]);
	rawColors.push_back(this->colors[3]);
	rawColors.push_back(this->colors[4]);
	rawColors.push_back(this->colors[5]);
	rawColors.push_back(this->colors[6]);
	rawColors.push_back(this->colors[7]);
	rawColors.push_back(this->colors[8]);
	rawColors.push_back(this->colors[9]);
	rawColors.push_back(this->colors[10]);
	rawColors.push_back(this->colors[11]);
	rawColors.push_back(this->colors[8]);
	rawColors.push_back(this->colors[9]);
	rawColors.push_back(this->colors[10]);
	rawColors.push_back(this->colors[11]);
	rawColors.push_back(this->colors[4]);
	rawColors.push_back(this->colors[5]);
	rawColors.push_back(this->colors[6]);
	rawColors.push_back(this->colors[7]);
	rawColors.push_back(this->colors[12]);
	rawColors.push_back(this->colors[13]);
	rawColors.push_back(this->colors[14]);
	rawColors.push_back(this->colors[15]);
	
	//Must find better way... That said, when I thought that about rects BEFORE(with the ugly sequential vertex positioning), I looked at the GLTools version...
	//And it did the same damn thing. AND for rectangular solids.

	this->batch->copyVertexData(rawVerts);
	this->batch->copyNormalData(rawNorms);
	this->batch->copyColorData(rawColors); 	//Completely coincidental that all three have the same length.
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
	this->batch->draw();
}


void Rect::update()
{
	//Have to figure out what to do here...
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
