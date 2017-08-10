#include "stTriangleBatch.h"

STTriangleBatch::STTriangleBatch()
{
	this->type = TRIANGLE;		//Should change this -- I really misunderstood what he was doing.
	this->vertID = 0;
	this->normID = 0;
	this->colorID = 0;
	this->indexID = 0;
	
	this->vertexBufferArrayID = 0;
	
	for(int i = 0; i < 4; i++)
	{
		this->texIDs[i] = 0;
	}
}

STTriangleBatch::~STTriangleBatch()
{
	glDeleteBuffers(1, &this->vertID);
	glDeleteBuffers(1, &this->normID);
	glDeleteBuffers(1, &this->colorID);
	glDeleteBuffers(1, &this->indexID);
	
	glDeleteBuffers(4, this->texIDs.data());
	
}

void STTriangleBatch::addTriangle(STTriangle* tri)
{
	for(int i = 0; i < 3; i++)
	{
		std::vector<GLfloat>::iterator iterV = this->vertData.begin();
		std::vector<GLfloat>::iterator iterN = this->normData.begin();
		std::vector<GLfloat>::iterator iterC = this->colorData.begin();
		std::vector<GLfloat>::iterator iterT = this->texCoordData[0].begin();
		
		bool match = false;
		int index = 0;
		int colorIndex = 0;
		int texIndex = 0;
		const int delta = 0.0001f;

		for(; iterV < this->vertData.end(); iterV += 3, iterN += 3, iterC += 4, iterT += 2, index += 3, colorIndex += 4, texIndex += 2) //Okay, now THIS for loop is getting ridiculous.
		{
			//Alright. This should work...
			if((tri->getVertex(i)->closeEnough(this->vertData[index], this->vertData[index + 1], this->vertData[index + 2], delta)) &&
				(tri->getNormal(i)->closeEnough(this->normData[index], this->normData[index + 1], this->normData[index + 2], delta)) &&
				(tri->getColor(i)->closeEnough(this->colorData[index], this->colorData[index + 1], this->colorData[index + 2], this->colorData[index + 3], delta)) &&
				(tri->getTexCoord(i)->closeEnough(this->texCoordData[0][texIndex], this->texCoordData[0][texIndex + 1], delta)))
			{
				GLuint vertIndex = index / 3;	
				this->indexData.push_back(vertIndex);
				match = true;
				break;
			}
		}
		
		if(!match)
		{
			//We've got to add all the stuff.
			
			STVec3f* vert = tri->getVertex(i);
			STVec3f* norm = tri->getNormal(i);
			STVec4f* color = tri->getColor(i);
			STVec2f* texCoord = tri->getTexCoord(i);
			
			this->vertData.push_back(vert->getX());
			this->vertData.push_back(vert->getY());
			this->vertData.push_back(vert->getZ());
			
			this->normData.push_back(norm->getX());
			this->normData.push_back(norm->getY());
			this->normData.push_back(norm->getZ());
			
			this->colorData.push_back(color->getX());	//Might want to also make 'getR()', 'getG()', 'getB()' and 'getA()'
			this->colorData.push_back(color->getY());
			this->colorData.push_back(color->getZ());
			this->colorData.push_back(color->getW());
			
			this->texCoordData[0].push_back(texCoord->getX());
			this->texCoordData[0].push_back(texCoord->getY());
			
			this->indexData.push_back((this->vertData.size() / 3) - 1);
		}
	}
}

void STTriangleBatch::finalize()
{
	//So...looks like I need the copyData functions, and to use them here.	
	
	//First, create an ID and bind the vertex buffer array to it. Still figuring this part out, since I don't think it was in the other one...
	glGenVertexArrays(1, &vertexBufferArrayID);
	glBindVertexArray(this->vertexBufferArrayID);
	
	//Now create the other IDs for the attribute arrays.
	glGenBuffers(1, &this->vertID);
	glGenBuffers(1, &this->normID);
	glGenBuffers(1, &this->colorID);
	glGenBuffers(1, &this->indexID);
	glGenBuffers(1, &this->texIDs[0]);
	
	//..and bind them. Unlike STPrimitiveBatch, we KNOW that we're using all of these. We have to.
	glBindBuffer(GL_ARRAY_BUFFER, this->vertID);
	glEnableVertexAttribArray(ST_ATTRIBUTE_VERTEX);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertData.size(), this->vertData.data(), GL_STATIC_DRAW);	//I wonder if static draw vs dynamic draw makes the difference? Nope.
	glVertexAttribPointer(ST_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->normID);
	glEnableVertexAttribArray(ST_ATTRIBUTE_NORMAL);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->normData.size(), this->normData.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(ST_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->normID);
	glEnableVertexAttribArray(ST_ATTRIBUTE_COLOR);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->colorData.size(), this->colorData.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(ST_ATTRIBUTE_COLOR, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->texIDs[0]);
	glEnableVertexAttribArray(ST_ATTRIBUTE_TEXTURE0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->texCoordData[0].size(), this->texCoordData[0].data(), GL_STATIC_DRAW);
	glVertexAttribPointer(ST_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * this->indexData.size(), this->indexData.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(0);	//free up the vertex array binding
	
	//Also clear out all the vectors.
	this->vertData.clear();
	this->normData.clear();
	this->colorData.clear();
	this->texCoordData.clear();
	this->indexData.clear();
}

void STTriangleBatch::draw()
{
	glBindVertexArray(this->vertexBufferArrayID);
	
	glDrawElements(GL_TRIANGLES, this->indexData.size(), GL_UNSIGNED_INT, nullptr);
	
	glBindVertexArray(0);		//Oddly, GLTools' version binds right back to the vbo... I think that's a bug, since it's already bound. Wouldn't be the first bug I've found!

}
