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
	//Now on to the hard part. No trigm I just have to figure out how to connect all the vertices I just generated in such a way that GL_TRIANGLES likes it.
	//Easy peasy, right?
	//It's probably easiest to go through the verts list from start to finish. Unlike a sphere, there aren't any 'caps' where the algorithm has to change. In fact, it's just a cylinder,
	//wrapped around itself.
	//Like a sphere, for each vertex, there are six indices -- we make two faces per vertex.
	//Except one problem. There are three elements(x, y and z) for each vertex. So we have to divide it by three, and add three each time. So really, there's only twice as many elements
	//in the index array than there are in the vertex array.
	
	//As with the sphere, there are four vertices that are important in every index calculation stage:(k = i * numSlices + j, l = numSlices + j)
	//1)v(k) -- the vertex we're at
	//2)v(k + 1) -- the next vertex up
	//3)v(k + l) -- the vertex across from v(k)
	//4)v(k + l + 1) -- the vertex across from v(k + 1)
	//The first triangle, wound counter-clockwise, goes as follows:
	//1, 3, 2
	//And the second one goes:
	//4, 2, 3
	
	//So the problem's in here. The wrong indices are getting pushed all over the place!
	for(int i = 0; i < this->numSections; i++)
	{
		for(int j = 0; j < this->numSlices; j++)
		{
			//The vertex number SHOULD be i * numSlices + j
			//In short, there are numSections * numSlices verts, so the whole thing could be viewed...as a two-dimensional array or matrix A(i,j)
			int k = i * this->numSlices + j; //k is the vertex index we're 'at'
			int l = this->numSlices;	//NO idea why I thought I had to add j here!!!
			
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
			this->indices.push_back(v3);
			this->indices.push_back(v2);
			this->indices.push_back(v4);
			this->indices.push_back(v2);
			this->indices.push_back(v3);
		}		
	}
	this->batch->copyIndexData(this->indices);
}
//...Color theory?
void STTorus::genColors()
{
	//Paint it black
	for(GLuint i = 0; i < this->verts.size() / 3; i++)
	{
		this->colors.push_back(0.0f);
		this->colors.push_back(0.0f);
		this->colors.push_back(0.0f);
		this->colors.push_back(1.0f);
	
	}
	this->batch->copyColorData(this->colors);
}
//Linear algebra
void STTorus::genNormals()
{
	//Now, in theory, we just need to subtract the vector that points from the origin of the torus to the local origin of the circle that a vertex is in
	//from the vector that points from the origin of the torus to the vertex itself.
	//This should generate a vector that points from the origin of the local circle to the vertex, which would thus be normal to that point on the torus.
	//To construct the first vector, we need two things:
	//1)the origin of the torus
	//2)the origin of the local circle.
	//we then subtract the origin of the torus from the origin of the local circle, and we have vector A.
	//For the second, we need:
	//1)The origin of the torus, again(thankfully, we have that)
	//2)The coordinates of the vertex.
	//Again, we subtract the origin from the vertex coords.
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) / (GLfloat)this->numSections;	//the number of radians between sections
	
	for(int i = 0; i < this->numSections; i++)
	{
		GLfloat mOriginX = this->origin->getX() + sin(theta) * this->r1;
		GLfloat mOriginY = this->origin->getY() + cos(theta) * this->r1;
		GLfloat mOriginZ = this->origin->getZ();
		
		STVec3f* v1 = new STVec3f(mOriginX - this->origin->getX(), mOriginY - this->origin->getY(), mOriginZ - this->origin->getZ());	//This one's constant for the inner loop.
		
		for(int j = 0; j < this->numSlices; j++)
		{
			int loc = (i * this->numSlices + j) * 3;
			STVec3f* v2 = new STVec3f(this->verts[loc] - this->origin->getX(), this->verts[loc + 1] - this->origin->getY(), this->verts[loc + 2] - this->origin->getZ());
			v2->subVec3f(v1);
			//Hate to say it, but I'm really hoping I can get away without normalizing, because floating point division is *the worst*.
			//Unfortunately, these are *normal* vectors, so I'm gonna play it safe for now.
			//Once I get the torus displaying properly, and a shader that actually utilizes normal vectors, I'll see what happens when I comment out the next line.
			v2->normalize();
			
			//Now that we've generated the normals, they need to be added to the normal array.
			this->norms.push_back(v2->getX());
			this->norms.push_back(v2->getY());
			this->norms.push_back(v2->getZ());
		}
		theta += dTheta;
	}
	this->batch->copyNormalData(this->norms);
}

bool STTorus::setColors(std::vector<GLfloat> colorArray)
{
	//Let's just tile the color array over the vertices.
	//It's fairly user-friendly.
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
