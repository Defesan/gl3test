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

}

void STTorus::genIndices()
{
	//Now on to the hard part. No trigm I just have to figure out how to connect all the vertices I just generated in such a way that GL_TRIANGLES likes it.
	//Easy peasy, right?

}

void STTorus::genColors()
{
	//TODO

}

void STTorus::genNormals()
{
	//TODO

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
