#ifndef __ST_TRIANGLE_BATCH_H__
#define __ST_TRIANGLE_BATCH_H__

#include "stBatch.h"
#include "stTriangle.h"

//So... What does GLTriangleBatch do?
//According to the description, it's basically a container form of the batch principle,
//based entirely on triangles.
//Adding a triangle, it checks to see if the vertices are 'close enough' to anything already in the vertex list.
//How? I mean, that sounds like it would be expensive.
//...and it is. I mean, damn. *Damn*! For each of the three vertices in the triangle, *for each of the vertices in the vertex list(!)*, it checks:
//each of the three elements of the vertex being tested against the vertex being tested against,
//each of the three elements of the normal,
//and both elements of the texture coordinate. That's eight tests,
//done three times per triangle
//done n times for each of those three times. To be sure, it's still O(n), which isn't *terrible*, but this is an insanely common task,
//done many times(once for each triangle added),
//and the number of vertices goes up by, presumably, at least one with every triangle! 
//This is going to take planning.

class STTriangleBatch : public STBatch
{
public:
	STTriangleBatch();
	~STTriangleBatch();
	
	void addTriangle(STTriangle* tri);
	void finalize();	//Bind the buffers and finalize the mesh. Maybe I should also have an 'update' function...
	
	//None of these are used.
	//void bindVertexData();
	//void bindNormalData();
	//void bindIndexData();
	//void bindTexCoordData();
	
	void draw() override;
};


#endif //__ST_TRIANGLE_BATCH_H__
