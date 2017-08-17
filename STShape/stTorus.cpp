#include "stTorus.h"

STTorus::STTorus(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat r1, GLfloat r2, GLint numSlices, GLint numSections)
{
	//this->batch = new STPrimitiveBatch(0);
	this->tBatch = new STTriangleBatch();
	this->origin = new STVec3f(originX, originY, originZ);
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->r1 = r1;
	this->r2 = r2;
	this->numSlices = numSlices;
	this->numSections = numSections;
	
	//this->tBatch->begin();   //Might need to add this later.
	
	this->genTriangles();
	
	this->tBatch->finalize();
	
	//this->batch->begin();
	
	//this->genVerts();
	//this->genIndices();
	//this->genColors();
	//this->genNormals();
	
	//this->batch->finalize();

}

STTorus::~STTorus()
{

}

//Aaand...all at once.
void STTorus::genTriangles()
{
	GLfloat invSections = 1.0f / (GLfloat)this->numSections;
	GLfloat invSlices = 1.0f / (GLfloat)this->numSlices;
	GLfloat invMinor = 1.0f / this->r2;

	//Gonna need these
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) * invSections;	//the number of radians between sections
	GLfloat thetaPrime = dTheta;	//The next ring
	
	GLfloat phi = 0.0f;
	GLfloat dPhi = (2 * PI) * invSlices;
	GLfloat phiPrime = dPhi;	//The next vert
	
	//Not gonna need indices, but I will need texture coords... How to do that?
	//Also, generate three verts at a time, so the index generator will be useful.
	for(int i = 0; i < this->numSections; i++)
	{
		STVec3f* verts[3];
		STVec3f* norms[3];
		STVec4f* colors[3];
		STVec2f* texCoords[3];	//Not my USUAL way of doing things, but I set up STTriangle for this purpose. That said, I could probably cut out the middleman, here...
		
		GLfloat x0 = cos(theta);	//Did the added precision of a double actually help? Guess I'll find out!
		GLfloat y0 = sin(theta);
		GLfloat x1 = cos(thetaPrime);
		GLfloat y1 = sin(thetaPrime);
		
		for(int j = 0; j < this->numSlices; j++)
		{
			GLfloat cosPhi = cos(phi);
			GLfloat cosPhiPrime = cos(phiPrime);
			GLfloat r = this->r2 * cosPhi + this->r1;
			GLfloat rPrime = this->r2 * cosPhiPrime + this->r1;
			GLfloat z = this->r2 * sin(phi);
			GLfloat zPrime = this->r2 * sin(phiPrime);
			
			//Vertex 1
			texCoords[0] = new STVec2f((GLfloat)i * invSections, (GLfloat)j * invSlices);
			norms[0] = new STVec3f(x0 * cosPhi, y0 * cosPhi, z * invMinor);
			colors[0] = new STVec4f(1.0f, 0.0f, 0.0f, 1.0f);
			verts[0] = new STVec3f(this->origin->getX() + x0 * r, this->origin->getY() + y0 * r, this->origin->getZ() + z);
			
			//Vertex 2
			texCoords[1] = new STVec2f((GLfloat)(i + 1) * invSections, (GLfloat)j * invSlices);
			norms[1] = new STVec3f(x1 * cosPhi, y1 * cosPhi, z * invMinor);
			colors[1] = new STVec4f(1.0f, 0.0f, 0.0f, 1.0f);
			verts[1] = new STVec3f(this->origin->getX() + x1 * r, this->origin->getY() + y1 * r, this->origin->getZ() + z);
			
			//Vertex 3
			texCoords[2] = new STVec2f((GLfloat)i * invSections, (GLfloat)(j + 1) * invSlices);
			norms[2] = new STVec3f(x0 * cosPhiPrime, y0 * cosPhiPrime, zPrime * invMinor);
			colors[2] = new STVec4f(1.0f, 0.0f, 0.0f, 1.0f);
			verts[2] = new STVec3f(this->origin->getX() + x0 * rPrime, this->origin->getY() + y0 * rPrime, this->origin->getZ() + zPrime);
			
			STTriangle* t1 = new STTriangle(verts, norms, colors, texCoords);
			
			this->tBatch->addTriangle(t1);
			
			//now we switch around some things...
			
			verts[0] = verts[1];
			norms[0] = norms[1];
			colors[0] = colors[1];
			texCoords[0] = texCoords[1];
			
			//Vertex 4
			texCoords[1] = new STVec2f((GLfloat)(i + 1) * invSections, (GLfloat)(j + 1) * invSlices);
			norms[1] = new STVec3f(x1 * cosPhiPrime, y1 * cosPhiPrime, zPrime * invMinor);
			colors[1] = new STVec4f(1.0f, 0.0f, 0.0f, 1.0f);
			verts[1] = new STVec3f(this->origin->getX() + x1 * rPrime, this->origin->getY() + y1 * rPrime, this->origin->getZ() + zPrime);
			
			
			STTriangle* t2 = new STTriangle(verts, norms, colors, texCoords);
			
			this->tBatch->addTriangle(t2);
			
			phi += dPhi;
			phiPrime += dPhi;
		}
		
		theta += dTheta;
		thetaPrime += dTheta;
	}

}


//Trigonometry
void STTorus::genVerts()
{
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) / (GLfloat)this->numSections;	//the number of radians between sections
	
	GLfloat phi = 0.0f;
	GLfloat dPhi = (2 * PI) / (GLfloat)this->numSlices;
	
	for(int i = 0; i < this->numSections; i++)
	{
		//I may not actually need these first two!
		//GLfloat mOriginX = this->origin->getX() + sin(theta) * this->r1;
		//GLfloat mOriginY = this->origin->getY() + cos(theta) * this->r1;
		GLfloat mOriginZ = this->origin->getZ();
		
		for(int j = 0; j < this->numSlices; j++)
		{
			
			this->verts.push_back(this->origin->getX() + sin(theta) * (this->r1 + (cos(phi) * this->r2)));
			this->verts.push_back(this->origin->getY() + cos(theta) * (this->r1 + (cos(phi) * this->r2)));
			this->verts.push_back(mOriginZ + sin(phi) * this->r2);
			
			phi += dPhi;
		}
		phi = 0.0f;
		theta += dTheta;
	}
	this->batch->copyVertexData(this->verts);
}
//Graph theory
void STTorus::genIndices()
{
	for(int i = 0; i < this->numSections; i++)
	{
		for(int j = 0; j < this->numSlices; j++)
		{
			int k = i * this->numSlices + j; 
			int l = this->numSlices;	
			
			GLuint v1 = (GLuint)k;
			GLuint v2 = 0;
			GLuint v3 = 0;
			GLuint v4 = 0;
			if(j < (this->numSlices - 1) && i < (this->numSections - 1))
			{
				//We're in the clear. The algorithm has no bumps.
				v2 = k + 1;
				v3 = k + l;
				v4 = k + l + 1;
			}
			else if(j == (this->numSlices - 1) && i < (this->numSections - 1))
			{
				//We're not in the last section, but we are at the end of a section.
				//This means that v2 is actually the first vertex in the section, and v4 is the first vertex of the NEXT section.
				//However, v3 is unchanged.
				v2 = k - j;
				v3 = k + l;
				v4 = k + l - j;
			} 
			else if(j < (this->numSlices - 1) && i == (this->numSections - 1))
			{
				//We're in the last section, but not at the end.
				//This means that v2 is the next vertex in the section(k + 1),
				//but v3 is the current vertex in the FIRST section, and v4 is the NEXT vertex in the FIRST section.
				v2 = k + 1;
				v3 = j;
				v4 = j + 1;
			}
			else
			{
				//We're almost done, actually. This is the last triangle pair of the last section.
				//v2, in this case, is the FIRST vertex of the LAST section, v3 is the LAST vertex of the FIRST section, and v4 is the FIRST vertex of the FIRST section.
				//Okay, the caps got out of hand there...
				v2 = k - j;
				v3 = j;
				v4 = 0;
			}
			
			this->indices.push_back(v1);
			this->indices.push_back(v2);
			this->indices.push_back(v3);
			this->indices.push_back(v4);
			this->indices.push_back(v3);
			this->indices.push_back(v2);
		}		
	}
	this->batch->copyIndexData(this->indices);
}
//...Color theory?
void STTorus::genColors()
{
	int numVerts = this->verts.size() / 3;

	GLfloat red = 1.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;
	GLfloat alpha = 1.0f;
	
	//Color generation, for the moment, is somewhat arbitrary.
	for(int i = 0; i < numVerts; i++)
	{
		this->colors.push_back(red);
		this->colors.push_back(green);
		this->colors.push_back(blue);
		this->colors.push_back(alpha);
		/*
		red += 0.01f;
		green += 0.02f;
		blue += 0.03f;
		
		if(red >= 1.0f)
		{
			red = 0.0f;
		}
		if(green >= 1.0f)
		{
			green = 0.0f;
		}
		if(blue >= 1.0f)
		{
			blue = 0.0f;
		}*/
	}
	this->batch->copyColorData(this->colors);
}
//Linear algebra
void STTorus::genNormals()
{
	//I switched to the method RSW used...and got the same result. Which, actually, you know, I kind of take as a compliment!
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) / (GLfloat)this->numSections;	//the number of radians between sections
	
	GLfloat phi = 0.0f;
	GLfloat dPhi = (2 * PI) / (GLfloat)this->numSlices;
	
	for(int i = 0; i < this->numSections; i++)
	{
		//GLfloat mOriginX = this->origin->getX() + sin(theta) * this->r1;
		//GLfloat mOriginY = this->origin->getY() + cos(theta) * this->r1;
		//GLfloat mOriginZ = this->origin->getZ();
		
		//so in the other code, a0 is simply the angle from 0 to the current section.
		//That's theta.
		//x0 and y0 are the sin and cos of a0.
		GLfloat x0 = sin(theta);
		GLfloat y0 = cos(theta);
		
		for(int j = 0; j < this->numSlices; j++)
		{
			//Ok... So......
			//I need c, as well.
			//b is just phi.
			GLfloat c = cos(phi);
			
			//and 'z' is just r2 times the sin of phi.
			//'cept the normal construction DIVIDES z by r2, so... it's just sin of phi.
			GLfloat z = sin(phi);
			
			STVec3f* normal = new STVec3f(x0 * c, y0 * c, z);
			normal->normalize();
			
			//Now we have everything.
			this->norms.push_back(normal->getX());
			this->norms.push_back(normal->getY());
			this->norms.push_back(normal->getZ());
			
			phi += dPhi;
		}
		theta += dTheta;
		phi = 0.0f;
	}
	this->batch->copyNormalData(this->norms);
}

bool STTorus::setColors(std::vector<GLfloat> colorArray)
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
	this->tBatch->draw();
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
	
	this->genTriangles();
}
