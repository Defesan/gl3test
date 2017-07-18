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
	//Planning time!
	//Generating a torus...
	//A torus is described by what I'll call an inner radius(r), the radius of the cross-section of the donut and an outer radius(R), the distance from the center of the
	//donut to the middle of the ring. Not terribly great at describing it.
	//So we're generating a bunch of circles in a circle around the origin, but the circles are vertically aligned and perpendicular to the line from the origin to their centers.
	//It's almost a matter of switching coordinate systems, but I don't think we have that luxury. Not generating the vertices every frame, at least!

	//So. Trig!
	//Let's first find out where the center of our first circle is. I'm constructing the torus vertically, so we'll be on the x-y plane, creating a circle that won't be represented by any points.
	//Let's say the angle to the point on thic circle that serves as the origin for our smaller circle is theta. Assuming an origin at x, y, z(we'll ignore the z for now), the
	//minor origin lies at x + sin(theta) * R, y + cos(theta) * R, z.
	GLfloat theta = 0.0f;
	GLfloat dTheta = (2 * PI) / (GLfloat)this->numSections;	//the number of radians between sections
	
	GLfloat phi = 0.0f;
	GLfloat dPhi = (2 * PI) / (GLfloat)this->numSlices;
	
	for(GLuint i = 0; i < this->numSections; i++)
	{
		GLfloat mOriginX = this->origin->getX() + sin(theta) * this->r1;
		GLfloat mOriginY = this->origin->getY() + cos(theta) * this->r1;
		GLfloat mOriginZ = this->origin->getZ();
		
		for(GLuint j = 0; j < this->numSlices; j++)
		{
			//Pretty sure this should work. And it did come out to three lines of code.
			//Basically, we're going down the components of the outer radius to find an x-y point along it and the line it generates.
			//To calculate this, we find the offset from the local origin -- defined by the cosine of phi times the inner radius -- and add that to the outer radius.
			//Because the offset will vary between -1 * r2 and 1 * r2, it's basically the projection of the xy-z plane's function onto x-y.
			//So yeah. Pretty sure that works.
			
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
	for(GLuint i = 0; i < this->numSections; i++)
	{
		for(GLuint j = 0; j < this->numSlices; j++)
		{
			//The vertex number SHOULD be i * numSlices + j
			//In short, there are numSections * numSlices verts, so the whole thing could be viewed...as a two-dimensional array or matrix A(i,j)
			int k = i * this->numSlices + j; 
			int l = this->numSlices + j;
			
			int v1 = k;
			int v2 = 0;
			int v3 = 0;
			int v4 = 0;
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
			
			this->indexData.push_back(v1);
			this->indexData.push_back(v3);
			this->indexData.push_back(v2);
			this->indexData.push_back(v4);
			this->indexData.push_back(v2);
			this->indexData.push_back(v3);
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
	//TODO
	this->batch->copyNormalData(this->norms);
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
