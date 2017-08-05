#include "stMatrix.h"

/*	STMatrix33f
	3x3 column-major matrix with floats
 */

STMatrix33f::STMatrix33f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{	
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);

}

STMatrix33f* STMatrix33f::mul(STMatrix33f* m2)
{
	STMatrix33f* result = new STMatrix33f();
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			float val = (this->get(i,0) * m2->get(0,j)) + (this->get(i,1) * m2->get(1,j)) + (this->get(i,2) * m2->get(2,j));
			result->set(i,j,val);
		}
	}
	return result;
}

STVec3f* STMatrix33f::mulVector(STVec3f* vec)
{
	STVec3f* result = new STVec3f();
	
	float x = vec->getX();
	float y = vec->getY();
	float z = vec->getZ();
	
	result->setX((this->get(0,0) * x) + (this->get(0,1) * y) + (this->get(0,2) * z));
	result->setY((this->get(1,0) * x) + (this->get(1,1) * y) + (this->get(1,2) * z));
	result->setZ((this->get(2,0) * x) + (this->get(2,1) * y) + (this->get(2,2) * z));
	
	return result;
}
	
void STMatrix33f::loadIdentity()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i == j)
			{
				this->set(i,j,1.0f);
			}
			else
			{
				this->set(i,j,0.0f);
			}
		}
	}
}

//Note that, while I'd like to use degrees for this, using radians just makes sense. Otherwise, they'll have to be converted at some point, and these operations should be fast.
void STMatrix33f::loadRotationMatrix(float angle, float x, float y, float z)
{
	//This seems like a fairly obvious optimization, though how much time it really saves...
	float mag = sqrt((x * x) + (y * y) + (z * z));	//float-overloaded sqrt functions! C and C++ never stop improving, it seems.
	if(mag == 0.0f)
	{
		this->loadIdentity();
		return;
	}
	
	//Normalize our axis elements
	x /= mag;
	y /= mag;
	z /= mag;
	
	float s = sin(angle);
	float c = cos(angle);
	float ci = (1.0f - c);
	
	this->set(0,0,((ci * x * x) + c));
	this->set(0,1,((ci * x * y) - (z * s)));
	this->set(0,2,((ci * x * z) + (y * s)));
	
	this->set(1,0,((ci * y * x) + (z * s)));
	this->set(1,1,((ci * y * y) + c));
	this->set(1,2,((ci * y * z) - (x * s)));
	
	this->set(2,0,((ci * z * x) - (y * s)));
	this->set(2,1,((ci * z * y) + (x * s)));
	this->set(2,2,((ci * z * z) + c));

}

STMatrix33f* STMatrix33f::copyMatrix()
{
	STMatrix33f* copy = new STMatrix33f();
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}
	return copy;
}

float STMatrix33f::determinant()
{
	float determinant = 0.0f;
	
	STMatrix22f* det00 = new STMatrix22f(this->get(1,1), this->get(1,2), this->get(2,1), this->get(2,2));
	STMatrix22f* det01 = new STMatrix22f(this->get(1,0), this->get(1,2), this->get(2,0), this->get(2,2));
	STMatrix22f* det02 = new STMatrix22f(this->get(1,0), this->get(1,1), this->get(2,0), this->get(2,1));
	
	determinant = determinant + det00->determinant() - det01->determinant() + det02->determinant();
	
	return determinant;	//And that was the easy one.
}

/*  STMatrix44f
	4x4 column-major matrix with floats
 */
 
STMatrix44f::STMatrix44f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(x4);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(y4);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);
	this->data.push_back(z4);
	this->data.push_back(w1);
	this->data.push_back(w2);
	this->data.push_back(w3);
	this->data.push_back(w4);
}

float STMatrix44f::determinant()
{
	float determinant = 0.0f;
	
	STMatrix33f* det00 = new STMatrix33f(this->get(1,1), this->get(1,2), this->get(1,3), this->get(2,1), this->get(2,2), this->get(2,3), this->get(3,1), this->get(3,2), this->get(3,3));
	STMatrix33f* det01 = new STMatrix33f(this->get(1,0), this->get(1,2), this->get(1,3), this->get(2,0), this->get(2,2), this->get(2,3), this->get(3,0), this->get(3,2), this->get(3,3));
	STMatrix33f* det02 = new STMatrix33f(this->get(1,0), this->get(1,1), this->get(1,3), this->get(2,0), this->get(2,1), this->get(2,3), this->get(3,0), this->get(3,1), this->get(3,3));
	STMatrix33f* det03 = new STMatrix33f(this->get(1,0), this->get(1,1), this->get(1,2), this->get(2,0), this->get(2,1), this->get(2,2), this->get(3,0), this->get(3,1), this->get(3,2));

	determinant = determinant + det00->determinant() - det01->determinant() + det02->determinant() - det03->determinant();
	
	return determinant;
}

float STMatrix44f::detIJ(int i, int j)
{
	STMatrix33f* subMatrix = new STMatrix33f();
	int x = 0;
	int y = 0;

	//Starting to see why all that ii and jj nonsense was in there...
	for(int k = 0; k < 4; k++)
	{
		//First step is to iterate through the full matrix.
		//We don't want to use the i or j elements.
		if(k != i)
		{
			y = 0;
			for(int l = 0; l < 4; l++)
			{
				if(l != j)
				{
					subMatrix->set(x,y,this->get(k,l));					
				}
				y++;
			}
			x++;
		}
	}
	return subMatrix->determinant();
}

STMatrix44f* STMatrix44f::mul(STMatrix44f* m2)
{
	STMatrix44f* result = new STMatrix44f();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float val = (this->get(i,0) * m2->get(0,j)) + (this->get(i,1) * m2->get(1,j)) + (this->get(i,2) * m2->get(2,j)) + (this->get(i,3) * m2->get(3,j));
			result->set(i,j,val);
		}
	}
	return result;
}

STVec4f* STMatrix44f::mulVector(STVec4f* vec)
{
	STVec4f* result = new STVec4f();
	
	float x = vec->getX();
	float y = vec->getY();
	float z = vec->getZ();
	float w = vec->getW();
	
	result->setX((this->get(0,0) * x) + (this->get(0,1) * y) + (this->get(0,2) * z) + (this->get(0,3) * w));
	result->setY((this->get(1,0) * x) + (this->get(1,1) * y) + (this->get(1,2) * z) + (this->get(1,3) * w));
	result->setZ((this->get(2,0) * x) + (this->get(2,1) * y) + (this->get(2,2) * z) + (this->get(2,3) * w));
	result->setW((this->get(3,0) * x) + (this->get(3,1) * y) + (this->get(3,2) * z) + (this->get(3,3) * w));
	
	return result;
}

void STMatrix44f::loadIdentity()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
			{
				this->set(i,j,1.0f);
			}
			else
			{
				this->set(i,j,0.0f);
			}
		}
	}
}

void STMatrix44f::loadRotationMatrix(float angle, float x, float y, float z)
{
	float mag = sqrt((x * x) + (y * y) + (z * z));	//float-overloaded sqrt functions! C and C++ never stop improving, it seems.
	if(mag == 0.0f)
	{
		this->loadIdentity();
		return;
	}
	
	//Normalize our axis elements
	x /= mag;
	y /= mag;
	z /= mag;
	
	float s = sin(angle);
	float c = cos(angle);
	float ci = (1.0f - c);
	
	this->set(0,0,((ci * x * x) + c));
	this->set(0,1,((ci * x * y) - (z * s)));
	this->set(0,2,((ci * x * z) + (y * s)));
	this->set(0,3,0.0f);
	
	this->set(1,0,((ci * y * x) + (z * s)));
	this->set(1,1,((ci * y * y) + c));
	this->set(1,2,((ci * y * z) - (x * s)));
	this->set(1,3,0.0f);
	
	this->set(2,0,((ci * z * x) - (y * s)));
	this->set(2,1,((ci * z * y) + (x * s)));
	this->set(2,2,((ci * z * z) + c));
	this->set(2,3,0.0f);
	
	this->set(3,0,0.0f);
	this->set(3,1,0.0f);
	this->set(3,2,0.0f);
	this->set(3,3,1.0f);

}

void STMatrix44f::loadPerspectiveMatrix(float fov, float aspect, float zMin, float zMax)
{
	//Basically an object-oriented refactor of the same function in the glTools m3d library.
	this->loadIdentity();
	
	float yMax = zMin * tan(fov * 0.5f);
	float yMin = -yMax;
	float xMin = yMin * aspect;
	float xMax = -xMin;
	
	this->data[0] = (2.0f * zMin) / (xMax - xMin);
	this->data[5] = (2.0f * zMin) / (yMax - yMin);
	this->data[8] = (xMax + xMin) / (xMax - xMin);
	this->data[9] = (yMax + yMin) / (yMax - yMin);
	this->data[10] = -((zMax + zMin) / (zMax - zMin));
	this->data[11] = -1.0f;
	this->data[14] = -((2.0f * (zMax*zMin))/(zMax - zMin));
	this->data[15] = 0.0f;

}

void STMatrix44f::loadOrthoMatrix(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//compared to the perspective matrix, this is downright straightforward!
	this->loadIdentity();
	
	this->data[0] = 2.0f / (xMax - xMin);
	this->data[5] = 2.0f / (yMax - yMin);
	this->data[10] = -2.0f / (zMax - zMin);
	this->data[12] = -((xMax + xMin)/(xMax - xMin));
	this->data[13] = -((yMax + yMin)/(yMax - yMin));
	this->data[14] = -((zMax + zMin)/(zMax - zMin));


}

STMatrix44f* STMatrix44f::copyMatrix()
{
	STMatrix44f* copy = new STMatrix44f();
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}
	return copy;
}

void STMatrix44f::print()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			std::cout << this->get(i,j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void STMatrix44f::setColumn(int index, STVec3f* column)
{
	for(int i = 0; i < 3; i++)
	{
		this->set(i, index, column->get(i)); 	
	}
	this->set(3, index, 0.0f);
}

void STMatrix44f::setRow(int index, STVec3f* row)
{
	for(int i = 0; i < 3; i++)
	{
		this->set(index, i, row->get(i));
	}
	this->set(index, 3, 0.0f);
}

STMatrix44f* STMatrix44f::invert()
{
	float determinant = this->determinant();	
	float invDet = 1.0f / determinant;		//We're going to be using this sixteen times. It's not MUCH of a time saver, given the determinant calculation process, but it helps. 
	STMatrix44f* inverse = new STMatrix44f();
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float ijVal = this->detIJ(i,j) * invDet;
			if((i + j) & 0x1)
			{
				ijVal = -ijVal;
			}
			inverse->set(i, j, ijVal);
		}
	}
	return inverse;
}

/*	STMatrix33d
	3x3 column-major matrix with doubles
 */
 
STMatrix33d::STMatrix33d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);
}

STMatrix33d* STMatrix33d::mul(STMatrix33d* m2)
{
	STMatrix33d* result = new STMatrix33d();
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			double val = (this->get(i,0) * m2->get(0,j)) + (this->get(i,1) * m2->get(1,j)) + (this->get(i,2) * m2->get(2,j));
			result->set(i,j,val);
		}
	}
	return result;
	
}

STVec3d* STMatrix33d::mulVector(STVec3d* vec)
{
	STVec3d* result = new STVec3d();
	
	double x = vec->getX();
	double y = vec->getY();
	double z = vec->getZ();
	
	result->setX((this->get(0,0) * x) + (this->get(0,1) * y) + (this->get(0,2) * z));
	result->setY((this->get(1,0) * x) + (this->get(1,1) * y) + (this->get(1,2) * z));
	result->setZ((this->get(2,0) * x) + (this->get(2,1) * y) + (this->get(2,2) * z));
	
	return result;
}
	
void STMatrix33d::loadIdentity()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i == j)
			{
				this->set(i,j,1.0);
			}
			else
			{
				this->set(i,j,0.0);
			}
		}
	}
}

void STMatrix33d::loadRotationMatrix(double angle, double x, double y, double z)
{
	double mag = sqrt((x * x) + (y * y) + (z * z));
	if(mag == 0.0)
	{
		this->loadIdentity();
		return;
	}
	
	//Normalize our axis elements
	x /= mag;
	y /= mag;
	z /= mag;
	
	double s = sin(angle);
	double c = cos(angle);
	double ci = (1.0 - c);
	
	this->set(0,0,((ci * x * x) + c));
	this->set(0,1,((ci * x * y) - (z * s)));
	this->set(0,2,((ci * x * z) + (y * s)));
	
	this->set(1,0,((ci * y * x) + (z * s)));
	this->set(1,1,((ci * y * y) + c));
	this->set(1,2,((ci * y * z) - (x * s)));
	
	this->set(2,0,((ci * z * x) - (y * s)));
	this->set(2,1,((ci * z * y) + (x * s)));
	this->set(2,2,((ci * z * z) + c));

}

STMatrix33d* STMatrix33d::copyMatrix()
{
	STMatrix33d* copy = new STMatrix33d();
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}
	return copy;
}

/*  STMatrix44d
	4x4 column-major matrix with doubles
 */
 
STMatrix44d::STMatrix44d(double x1, double y1, double z1, double w1, double x2, double y2, double z2, double w2, double x3, double y3, double z3, double w3, double x4, double y4, double z4, double w4)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(x4);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(y4);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);
	this->data.push_back(z4);
	this->data.push_back(w1);
	this->data.push_back(w2);
	this->data.push_back(w3);
	this->data.push_back(w4);
}

STMatrix44d* STMatrix44d::mul(STMatrix44d* m2)
{
	STMatrix44d* result = new STMatrix44d();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			double val = (this->get(i,0) * m2->get(0,j)) + (this->get(i,1) * m2->get(1,j)) + (this->get(i,2) * m2->get(2,j)) + (this->get(i,3) * m2->get(3,j));
			result->set(i,j,val);
		}
	}
	return result;
}

STVec4d* STMatrix44d::mulVector(STVec4d* vec)
{
	STVec4d* result = new STVec4d();
	
	double x = vec->getX();
	double y = vec->getY();
	double z = vec->getZ();
	double w = vec->getW();
	
	result->setX((this->get(0,0) * x) + (this->get(0,1) * y) + (this->get(0,2) * z) + (this->get(0,3) * w));
	result->setY((this->get(1,0) * x) + (this->get(1,1) * y) + (this->get(1,2) * z) + (this->get(1,3) * w));
	result->setZ((this->get(2,0) * x) + (this->get(2,1) * y) + (this->get(2,2) * z) + (this->get(2,3) * w));
	result->setW((this->get(3,0) * x) + (this->get(3,1) * y) + (this->get(3,2) * z) + (this->get(3,3) * w));
	
	return result;
}

void STMatrix44d::loadIdentity()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
			{
				this->set(i,j,1.0);
			}
			else
			{
				this->set(i,j,0.0);
			}
		}
	}
}

void STMatrix44d::loadRotationMatrix(double angle, double x, double y, double z)
{
	double mag = sqrt((x * x) + (y * y) + (z * z));
	if(mag == 0.0)
	{
		this->loadIdentity();
		return;
	}
	
	//Normalize our axis elements
	x /= mag;
	y /= mag;
	z /= mag;
	
	double s = sin(angle);
	double c = cos(angle);
	double ci = (1.0f - c);
	
	this->set(0,0,((ci * x * x) + c));
	this->set(0,1,((ci * x * y) - (z * s)));
	this->set(0,2,((ci * x * z) + (y * s)));
	this->set(0,3,0.0);
	
	this->set(1,0,((ci * y * x) + (z * s)));
	this->set(1,1,((ci * y * y) + c));
	this->set(1,2,((ci * y * z) - (x * s)));
	this->set(1,3,0.0);
	
	this->set(2,0,((ci * z * x) - (y * s)));
	this->set(2,1,((ci * z * y) + (x * s)));
	this->set(2,2,((ci * z * z) + c));
	this->set(2,3,0.0);
	
	this->set(3,0,0.0);
	this->set(3,1,0.0);
	this->set(3,2,0.0);
	this->set(3,3,1.0);

}


void STMatrix44d::loadPerspectiveMatrix(double fov, double aspect, double zMin, double zMax)
{
	//Basically an object-oriented refactor of the same function in the glTools m3d library.
	this->loadIdentity();
	
	double yMax = zMin * tan(fov * 0.5f);
	double yMin = -yMax;
	double xMin = yMin * aspect;
	double xMax = -xMin;
	
	this->data[0] = (2.0f * zMin) / (xMax - xMin);
	this->data[5] = (2.0f * zMin) / (yMax - yMin);
	this->data[8] = (xMax + xMin) / (xMax - xMin);
	this->data[9] = (yMax + yMin) / (yMax - yMin);
	this->data[10] = -((zMax + zMin) / (zMax - zMin));
	this->data[11] = -1.0f;
	this->data[14] = -((2.0f * (zMax*zMin))/(zMax - zMin));
	this->data[15] = 0.0f;

}

void STMatrix44d::loadOrthoMatrix(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
{
	this->loadIdentity();
	
	this->data[0] = 2.0f / (xMax - xMin);
	this->data[5] = 2.0f / (yMax - yMin);
	this->data[10] = -2.0f / (zMax - zMin);
	this->data[12] = -((xMax + xMin)/(xMax - xMin));
	this->data[13] = -((yMax + yMin)/(yMax - yMin));
	this->data[14] = -((zMax + zMin)/(zMax - zMin));
}

STMatrix44d* STMatrix44d::copyMatrix()
{
	STMatrix44d* copy = new STMatrix44d();
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}
	return copy;
}

/* GLSL Uniform Compatibility Types */
/*  STMatrix22f
 *	2x2 column-major matrix with floats
 */

STMatrix22f::STMatrix22f(float x1, float y1, float x2, float y2)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(y1);
	this->data.push_back(y2);
}

void STMatrix22f::loadIdentity()
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(i == j)
			{
				this->set(i,j,1.0f);
			}
			else
			{
				this->set(i,j,0.0f);
			}
		}
	}
}

STMatrix22f* STMatrix22f::copyMatrix()
{
	STMatrix22f* copy = new STMatrix22f();
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}
	return copy;
}

/*  STMatrix23f
	2x3 column-major matrix with floats
	Just so I get it right this time, the matrix is supposed to look like this:
	x1 y1 z1
	x2 y2 z2
	
	and the array representation looks like this:
	x1 x2 y1 y2 z1 z2
	
	and since the nominal ordering is:
	0,0 0,1 0,2
	1,0 1,1 1,2
	
	and the indices are
	0   2   4
	1   3   5
	
	get(i,j) = i + 2j
 */
 
STMatrix23f::STMatrix23f(float x1, float y1, float z1, float x2, float y2, float z2)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(z1);
	this->data.push_back(z2);
}

STMatrix23f* STMatrix23f::copyMatrix()
{
	STMatrix23f* copy = new STMatrix23f();

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}

/*  STMatrix24f
 *	2x4 column-major matrix with floats
 */
STMatrix24f::STMatrix24f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(w1);
	this->data.push_back(w2);
}

STMatrix24f* STMatrix24f::copyMatrix()
{
	STMatrix24f* copy = new STMatrix24f();

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}

/* STMatrix32f
 * 3x2 column-major matrix with floats
 */
STMatrix32f::STMatrix32f(float x1, float y1, float x2, float y2, float x3, float y3)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
}

STMatrix32f* STMatrix32f::copyMatrix()
{
	STMatrix32f* copy = new STMatrix32f();

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}

/* STMatrix34f
 * 3x4 column-major matrix with floats
 */
STMatrix34f::STMatrix34f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);
	this->data.push_back(w1);
	this->data.push_back(w2);
	this->data.push_back(w3);
}

STMatrix34f* STMatrix34f::copyMatrix()
{
	STMatrix34f* copy = new STMatrix34f();

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}

/* STMatrix42f
 * 4x2 column-major matrix with floats
 */
STMatrix42f::STMatrix42f(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(x4);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(y4);
}

STMatrix42f* STMatrix42f::copyMatrix()
{
	STMatrix42f* copy = new STMatrix42f();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}

/* STMatrix43f
 * 4x3 column-major matrix with floats
 */
STMatrix43f::STMatrix43f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	this->data.push_back(x1);
	this->data.push_back(x2);
	this->data.push_back(x3);
	this->data.push_back(x4);
	this->data.push_back(y1);
	this->data.push_back(y2);
	this->data.push_back(y3);
	this->data.push_back(y4);
	this->data.push_back(z1);
	this->data.push_back(z2);
	this->data.push_back(z3);
	this->data.push_back(z4);
}

STMatrix43f* STMatrix43f::copyMatrix()
{
	STMatrix43f* copy = new STMatrix43f();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			copy->set(i,j,this->get(i,j));
		}
	}

	return copy;
}
