#include "stSphere.h"

Sphere::Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLuint numLayers, GLuint numSlices)
{
	this->batch = new STPrimitiveBatch(0);
	this->origin = new STVec3f(originX, originY, originZ);
	
	this->radius = radius;
	this->numLayers = numLayers;
	this->numSlices = numSlices;
	
	this->velocity = new STVec3f();
	this->acceleration = new STVec3f();
	
	this->batch->begin();
	
	this->genVerts();
	this->genIndices();
	this->genColors();
	this->genNormals();
	
	this->batch->finalize();
}

Sphere::~Sphere()
{
	//Using vectors, so no current references to delete.

}

void Sphere::genVerts()
{
	this->verts.clear();

	GLfloat originX = this->origin->getX();
	GLfloat originY = this->origin->getY();
	GLfloat originZ = this->origin->getZ();

	//Sphere construction begins at the top.
	GLfloat vertexYPos = this->radius + originY;
	GLfloat vertexXPos = originX;
	GLfloat vertexZPos = originZ;
	
	GLfloat layerAngle = PI/(this->numLayers + 1);  //The angle, in radians, between each layer of the sphere
	GLfloat sliceAngle = (2 * PI)/this->numSlices;  //The angle, in radians, between each meridian of the sphere.
	
	GLfloat currentSliceAngle = 0.0f;	//This is just the slice angle multiplied by the index of the slice currently being placed.
	GLfloat currentLayerAngle = 0.0f;	//Same as above, but for layers
	GLfloat layerRadius = 0.0f;			//The radius of the circle that defines the current layer

	//Top vertex coordinates
	this->verts.push_back(vertexXPos);
	this->verts.push_back(vertexYPos);
	this->verts.push_back(vertexZPos);
	
	//Generate layer i
	for(GLuint i = 0; i < this->numLayers; i++)
	{
		//Calculate the angle of the current layer
		currentLayerAngle = layerAngle * (i + 1);	
		
		//Define the dimensions and position of the current layer
		layerRadius = sin(currentLayerAngle) * this->radius;
		vertexYPos = cos(currentLayerAngle) * this->radius;
		
		//Generate vertex j of layer i
		for(GLuint j = 0; j < this->numSlices; j++)
		{
			//Calculate the angle of the current slice
			currentSliceAngle = j * sliceAngle;
			
			//Determine the coordinates of the current vertex
			vertexXPos = sin(currentSliceAngle) * layerRadius;
			vertexZPos = cos(currentSliceAngle) * layerRadius;

			//Place vertex j of layer i
			this->verts.push_back(vertexXPos);
			this->verts.push_back(vertexYPos);
			this->verts.push_back(vertexZPos);
		}
	}
	
	//Bottom vertex coordinates
	vertexYPos = -1 * this->radius + originY;
	vertexXPos = originX;
	vertexZPos = originZ;
	
	this->verts.push_back(vertexXPos);
	this->verts.push_back(vertexYPos);
	this->verts.push_back(vertexZPos);
	
	this->batch->copyVertexData(this->verts);
}

void Sphere::genIndices()
{
	/*
		Index generation is done in three parts:
		1) 'Upper cap' -- the triangles that are centered on the top vertex
		2) 'Strips' -- the areas between the layers, created with pairs of triangles forming quads
		3) 'Bottom cap' -- the triangles centered on the bottom vertex
	
	*/
	
	//1 -- Upper cap generation
	for(GLuint i = 0; i < this->numSlices; i++)
	{
		this->indices.push_back(0);			//Each triangle starts with the top vertex...
		this->indices.push_back(i + 1);		//and extends to the i + 1th slice vertex
		
		//Then, it has to check to make sure the next vertex is actually in the current layer
		if(i != (this->numSlices - 1))
		{
			this->indices.push_back(i + 2);	//If it is, the third index is just the next vertex.
		}
		else
		{
			this->indices.push_back(1);		//Otherwise, it has to loop back to the start.
		}
	}

	
	//2 -- Strip generation
	//For N layers, this is done N - 1 times. This is because the strips are defined in terms of both the ith layer and the (i + 1)th layer.
	for(GLuint i = 0; i < (this->numLayers - 1); i++)
	{
		GLuint firstVert = (this->numSlices * i) + 1;			//The index of the first vertex in the current layer
		GLuint belowFirst = (this->numSlices * (i + 1)) + 1; 	//The index of the first vertex on the layer below the current layer.
		
		//For each j, there are two triangles to generate.
		//Given vertex v(j) and v(j + M), with slice count M, the triangles are defined as follows:
		//Tri 1: {v(j), v(j + M), v(j + M + 1)}
		//Tri 2: {v(j), v(j + 1), v(j + M + 1)}
		for(GLuint j = 0; j < this->numSlices; j++)
		{
			//The first two indices in each group of six are always the jth vertex after firstVert and belowFirst, respectively.
			this->indices.push_back(firstVert + j);
			
			//Again, the circular nature of the strips requires a branch.
			if(j != (this->numSlices - 1))		//For all but the last vertex in the strip,
			{
				this->indices.push_back(belowFirst + j);
				this->indices.push_back(belowFirst + (j + 1));	//v(j + M + 1)
				this->indices.push_back(firstVert + j);			//v(j)
				this->indices.push_back(belowFirst + (j + 1));  //v(j + M + 1)
				this->indices.push_back(firstVert + (j + 1));	//v(j + 1)
			}
			else	//Otherwise, we have to substitute the starting vertices of both layers for the 'next' vertices.
			{
				this->indices.push_back(belowFirst + j);
				this->indices.push_back(belowFirst);
				this->indices.push_back(firstVert + j);
				this->indices.push_back(belowFirst);
				this->indices.push_back(firstVert);
				
			}
		}
	}
		
		
	//3 -- Bottom cap generation
	//Here, the index of the central vertex, as well as the first vertex of the last layer, need to be calculated.
	GLuint numVerts = this->numSlices * this->numLayers + 2;
	GLuint lastVert = numVerts - 1;
	GLuint startOfLastRing = lastVert - this->numSlices;

	//However, substituting lastVert for 0 and startOfLastRing for 1, the rest proceeds just like the upper cap.
	for(GLuint i = 0; i < this->numSlices; i++)
	{
		this->indices.push_back(lastVert);
		
		if(i != (this->numSlices - 1))
		{
			this->indices.push_back(i + (startOfLastRing + 1));
		}
		else
		{
			this->indices.push_back(startOfLastRing);
		}
		
		this->indices.push_back(i + startOfLastRing);
	}
	this->batch->copyIndexData(this->indices);
}

void Sphere::genColors()
{
	int numVerts = (this->numLayers * this->numSlices) + 2;

	GLfloat red = 0.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;
	GLfloat alpha = 0.0f;
	
	//Color generation, for the moment, is somewhat arbitrary.
	for(int i = 0; i < numVerts; i++)
	{
		this->colors.push_back(red);
		this->colors.push_back(green);
		this->colors.push_back(blue);
		this->colors.push_back(alpha);
		
		red += 0.01f;
		green += 0.02f;
		blue += 0.03f;
		
	}
	this->batch->copyColorData(this->colors);
}

void Sphere::genNormals()
{
	//So here this gets a BIT trickier. Before, we've simply dealt with 2D objects, but this thing has volume.
	//But it's still simple enough. If I'm thinking about this correctly, the normal for a given point should just be the point subtracted from the origin.
	//This *should*(right?) provide a vector pointing through the origin AND the vertex, which is thus normal to the surface of the sphere. I think.
	
	//Man, the TORUS is going to be fun!
	
	int vertCount = this->verts.size() / 3;
	for(int i = 0; i < vertCount; i++)
	{
		this->norms.push_back(this->origin->getX() - this->verts[i]);
		this->norms.push_back(this->origin->getY() - this->verts[i + 1]);
		this->norms.push_back(this->origin->getZ() - this->verts[i + 2]);
	}
	this->batch->copyNormalData(this->norms);
	
}

void Sphere::setColorToGLColor()
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

bool Sphere::setColors(std::vector<GLfloat> colorArray)
{
	//TODO
	return false;
}

void Sphere::render()
{
	this->batch->draw();
}

void Sphere::update()
{
	this->velocity->addVec3f(this->acceleration);	
	this->translate(this->velocity);
	this->render();
}

void Sphere::accelerate(GLfloat accX, GLfloat accY, GLfloat accZ)
{
	this->acceleration->setX(accX);
	this->acceleration->setY(accY);
	this->acceleration->setZ(accZ);
}


void Sphere::translate(GLfloat x, GLfloat y, GLfloat z)
{
	//Update the origin
	this->origin->addX(x);
	this->origin->addY(y);
	this->origin->addZ(z);
	
	//...and the verts
	this->genVerts();
	
}

