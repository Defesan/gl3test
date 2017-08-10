#include "stTriangle.h"

STTriangle::STTriangle(std::vector<STVec3f*> verts, std::vector<STVec3f*> norms, std::vector<STVec4f*> colors, std::vector<STVec2f*> texCoords)
{
	this->verts = verts;
	this->norms = norms;
	this->colors = colors;
	this->texCoords = texCoords;
}

STTriangle::STTriangle(STVec3f* vert1, STVec3f* vert2, STVec3f* vert3, STVec3f* norm1, STVec3f* norm2, STVec3f* norm3, STVec4f* color1, STVec4f* color2, STVec4f* color3, STVec2f* tex1, STVec2f* tex2, STVec2f* tex3)
{
	this->verts.push_back(vert1);
	this->verts.push_back(vert2);
	this->verts.push_back(vert3);
	
	this->norms.push_back(norm1);
	this->norms.push_back(norm2);
	this->norms.push_back(norm3);
	
	this->colors.push_back(color1);
	this->colors.push_back(color2);
	this->colors.push_back(color3);
		
	this->texCoords.push_back(tex1);
	this->texCoords.push_back(tex2);
	this->texCoords.push_back(tex3);
	
	//Note: the parameters passed to this function should be organized such that vert1 is the point for norm1 and tex1, and so on.
}

STTriangle::STTriangle(STVec3f* verts[3], STVec3f* norms[3], STVec4f* colors[3], STVec2f* texCoords[3])
{
	this->verts.push_back(verts[0]);
	this->verts.push_back(verts[1]);
	this->verts.push_back(verts[2]);
	
	this->norms.push_back(norms[0]);
	this->norms.push_back(norms[1]);
	this->norms.push_back(norms[2]);
	
	this->colors.push_back(colors[0]);
	this->colors.push_back(colors[1]);
	this->colors.push_back(colors[2]);
	
	this->texCoords.push_back(texCoords[0]);
	this->texCoords.push_back(texCoords[1]);
	this->texCoords.push_back(texCoords[2]);
}

bool STTriangle::containsVertex(STVec3f* vertex, STVec3f* normal, STVec4f* color, STVec2f* texCoord)
{
	float delta = 0.00001f;
	for(int i = 0; i < 3; i++)
	{
		if(vertex->closeEnough(this->verts[i], delta) && normal->closeEnough(this->norms[i], delta) && color->closeEnough(this->colors[i], delta) && texCoord->closeEnough(this->texCoords[i], delta))
		{
			return true;
		}
	}
	return false;
}

STVec3f* STTriangle::getVertex(int index)
{
	if(index > 2 || index < 0)
	{
		//WTF are you trying to pull?
		std::cerr << "STTriangle: Requested vertex index out of bounds." << std::endl;
		return nullptr;
	}
	return this->verts[index];
}

STVec3f* STTriangle::getNormal(int index)
{
	if(index > 2 || index < 0)
	{
		std::cerr << "STTriangle: Requested normal vector index out of bounds." << std::endl;
		return nullptr;
	}
	return this->norms[index];
}

STVec4f* STTriangle::getColor(int index)
{
	if(index > 2 || index < 0)
	{
		std::cerr << "STTriangle: Requested color point index out of bounds." << std::endl;
		return nullptr;
	}
	return this->colors[index];
}

STVec2f* STTriangle::getTexCoord(int index)
{
	if(index > 2 || index < 0)
	{
		std::cerr << "STTriangle: Requested texture coordinate index out of bounds." << std::endl;
		return nullptr;
	}
	return this->texCoords[index];

}
