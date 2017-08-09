#ifndef __ST_TRIANGLE_H__
#define __ST_TRIANGLE_H__

#include <vector>
#include <iostream>

#include "../STLinear/stVector.h"


class STTriangle
{
private:
	//There should be three of each. Still thinking an array would be simpler...
	std::vector<STVec3f*> verts;
	std::vector<STVec3f*> norms;
	std::vector<STVec3f*> colors;
	std::vector<STVec2f*> texCoords;
	
public:
	//I was spoiled for choice here. Each form had its own benefits and drawbacks... But C++ supports constructor overloading, so it didn't matter.
	STTriangle(std::vector<STVec3f*> verts, std::vector<STVec3f*> norms, std::vector<STVec3f*> colors, std::vector<STVec2f*> texCoords);
	STTriangle(STVec3f* vert1, STVec3f* vert2, STVec3f* vert3, STVec3f* norm1, STVec3f* norm2, STVec3f* norm3, STVec3f* color1, STVec3f* color2, STVec3f* color3, STVec2f* tex1, STVec2f* tex2, STVec2f* tex3);
	STTriangle(STVec3f* verts[3], STVec3f* norms[3], STVec3f* colors[3], STVec2f* texCoords[3]);

	bool containsVertex(STVec3f* vertex, STVec3f* normal, STVec3f* color, STVec2f* texCoord);
	
	STVec3f* getVertex(int index);
	STVec3f* getNormal(int index);
	STVec3f* getColor(int index);
	STVec2f* getTexCoord(int index);
};

#endif //__ST_TRIANGLE_H__
