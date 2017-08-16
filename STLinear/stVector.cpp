#include "stVector.h"

/*
	STVec2f
	2 element vector with floats	
*/
STVec2f::STVec2f(float x, float y)
{
	this->data.push_back(x);
	this->data.push_back(y);
}

void STVec2f::addVec2f(STVec2f* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
}

void STVec2f::subVec2f(STVec2f* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
}

void STVec2f::mulScalar(float scale)
{
	this->mulX(scale);
	this->mulY(scale);
}

STVec2f* STVec2f::sum(STVec2f* v2)
{
	STVec2f* result = new STVec2f(this->getX() + v2->getX(), this->getY() + v2->getY());
	return result; //Probably could have inlined this...
}

STVec2f* STVec2f::diff(STVec2f* v2)
{
	STVec2f* result = new STVec2f(this->getX() - v2->getX(), this->getY() - v2->getY());
	return result; //Probably could have inlined this...
}

float STVec2f::dotProduct(STVec2f* v2)
{
	float product = 0.0f;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();

	return product;
}

float STVec2f::distance(STVec2f* v2)
{
	STVec2f* connecting = this->diff(v2);
	return std::abs(connecting->length());

}

bool STVec2f::closeEnough(STVec2f* v2, float delta)
{
	float dX = std::abs(v2->getX() - this->getX());
	float dY = std::abs(v2->getY() - this->getY());
	
	if((dX < delta) && (dY < delta))
	{
		return true;
	}
	return false;
}

bool STVec2f::closeEnough(float x, float y, float delta)
{
	float dX = std::abs(x - this->getX());
	float dY = std::abs(y - this->getY());
	
	if((dX < delta) && (dY < delta))
	{
		return true;
	}
	return false;
}

/*
	STVec3f
	3 element vector with floats	
*/
STVec3f::STVec3f(float x, float y, float z)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
}

//Initialize from another vector
STVec3f::STVec3f(STVec3f* original)
{
	this->data.push_back(original->getX());
	this->data.push_back(original->getY());
	this->data.push_back(original->getZ());
}

void STVec3f::addVec3f(STVec3f* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
	this->addZ(v2->getZ());
}

void STVec3f::subVec3f(STVec3f* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
	this->subZ(v2->getZ());
}

void STVec3f::mulScalar(float scale)
{
	this->mulX(scale);
	this->mulY(scale);
	this->mulZ(scale);
}

STVec3f* STVec3f::sum(STVec3f* v2)
{
	STVec3f* result = new STVec3f(this->getX() + v2->getX(), this->getY() + v2->getY(), this->getZ() + v2->getZ());
	return result; //Probably could have inlined this...
}

STVec3f* STVec3f::diff(STVec3f* v2)
{
	STVec3f* result = new STVec3f(this->getX() - v2->getX(), this->getY() - v2->getY(), this->getZ() - v2->getZ());
	return result; //Probably could have inlined this...
}

float STVec3f::dotProduct(STVec3f* v2)
{
	float product = 0.0f;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();
	product += this->getZ() * v2->getZ();

	return product;
}

float STVec3f::distance(STVec3f* v2)
{
	STVec3f* connecting = this->diff(v2);
	return std::abs(connecting->length());

}

STVec3f* STVec3f::crossProduct(STVec3f* v2)
{
	STVec3f* result = new STVec3f();
	
	result->setX((this->getY() * v2->getZ()) - (this->getZ() * v2->getY()));
	result->setY((this->getZ() * v2->getX()) - (this->getX() * v2->getZ()));
	result->setZ((this->getX() * v2->getY()) - (this->getY() * v2->getX()));
	
	return result;
}

bool STVec3f::closeEnough(STVec3f* v2, float delta)
{
	float dX = std::abs(v2->getX() - this->getX());
	float dY = std::abs(v2->getY() - this->getY());
	float dZ = std::abs(v2->getZ() - this->getZ());
	
	if((dX < delta) && (dY < delta) && (dZ < delta))
	{
		return true;
	}
	return false;
}

bool STVec3f::closeEnough(float x, float y, float z, float delta)
{
	float dX = std::abs(x - this->getX());
	float dY = std::abs(y - this->getY());
	float dZ = std::abs(z - this->getZ());
	
	if((dX < delta) && (dY < delta) && (dZ < delta))
	{
		return true;
	}
	return false;
}

void STVec3f::print()
{
	std::cout << "X = " << this->getX() << " Y = " << this->getY() << " Z = " << this->getZ() << std::endl;

}

void STVec3f::normalize()
{
	float length = this->length();
	this->mulScalar(1.0f / length);	//So that's why we had a length function.
}

STVec3f* STVec3f::copy()
{
	STVec3f* returnVector = new STVec3f();
	
	returnVector->setX(this->getX());
	returnVector->setY(this->getY());
	returnVector->setZ(this->getZ());
	
	return returnVector;
}

/*
	STVec4f
	4 element vector with floats	
*/

STVec4f::STVec4f(float x, float y, float z, float w)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
	this->data.push_back(w);
}

void STVec4f::addVec4f(STVec4f* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
	this->addZ(v2->getZ());
	this->addW(v2->getW());
}

void STVec4f::subVec4f(STVec4f* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
	this->subZ(v2->getZ());
	this->subW(v2->getW());
}

void STVec4f::mulScalar(float scale)
{
	this->mulX(scale);
	this->mulY(scale);
	this->mulZ(scale);
	this->mulW(scale);
}

STVec4f* STVec4f::sum(STVec4f* v2)
{
	STVec4f* result = new STVec4f(this->getX() + v2->getX(), this->getY() + v2->getY(), this->getZ() + v2->getZ(), this->getW() + v2->getW());
	return result; //Probably could have inlined this...
}

STVec4f* STVec4f::diff(STVec4f* v2)
{
	STVec4f* result = new STVec4f(this->getX() - v2->getX(), this->getY() - v2->getY(), this->getZ() - v2->getZ(), this->getW() - v2->getW());
	return result; //Probably could have inlined this...
}


float STVec4f::dotProduct(STVec4f* v2)
{
	float product = 0.0f;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();
	product += this->getZ() * v2->getZ();
	product += this->getW() * v2->getW();

	return product;
}

float STVec4f::distance(STVec4f* v2)
{
	STVec4f* connecting = this->diff(v2);
	return std::abs(connecting->length());

}

bool STVec4f::closeEnough(STVec4f* v2, float delta)
{
	float dX = std::abs(v2->getX() - this->getX());
	float dY = std::abs(v2->getY() - this->getY());
	float dZ = std::abs(v2->getZ() - this->getZ());
	float dW = std::abs(v2->getW() - this->getW());
	
	if((dX < delta) && (dY < delta) && (dZ < delta) && (dW < delta))
	{
		return true;
	}
	return false;
}

bool STVec4f::closeEnough(float x, float y, float z, float w, float delta)
{
	float dX = std::abs(x - this->getX());
	float dY = std::abs(y - this->getY());
	float dZ = std::abs(z - this->getZ());
	float dW = std::abs(w - this->getW());
	
	if((dX < delta) && (dY < delta) && (dZ < delta) && (dW < delta))
	{
		return true;
	}
	return false;
}

void STVec4f::genPlaneEquation(STVec4f* p1, STVec4f* p2, STVec4f* p3)
{
	STVec3f* protoPlane = new STVec3f();
	STVec3f* v1 = new STVec3f();
	STVec3f* v2 = new STVec3f();
	
	//The first vector in the plane is p3 - p1(really, we could use any vectors created from the three given points)
	v1->setX(p3->getX() - p1->getX());
	v1->setY(p3->getY() - p1->getY());
	v1->setZ(p3->getZ() - p1->getZ());
	
	//Now let's go with p2 - p1.
	v2->setX(p2->getX() - p1->getX());
	v2->setY(p2->getY() - p1->getY());
	v2->setZ(p2->getZ() - p1->getZ());
	
	protoPlane = v1->crossProduct(v2);
	protoPlane->normalize();
	
	this->setX(protoPlane->getX());
	this->setY(protoPlane->getY());
	this->setZ(protoPlane->getZ());
	//And the slightly more complex fourth element...
	this->setW(-1.0f * ((protoPlane->getX() * p3->getX()) + (protoPlane->getY() * p3->getY()) + (protoPlane->getZ() * p3->getZ())));
	
}

float STVec4f::planeDistanceFromPoint(STVec3f* point)
{
	float distance = (this->getX() * point->getX()) + (this->getY() * point->getY()) + (this->getZ() * point->getZ()) + this->getW();
	
	return distance;
}


/*
	STVec2d
	2 element vector with double	
*/
STVec2d::STVec2d(double x, double y)
{
	this->data.push_back(x);
	this->data.push_back(y);
}

void STVec2d::addVec2d(STVec2d* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
}

void STVec2d::subVec2d(STVec2d* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
}

void STVec2d::mulScalar(double scale)
{
	this->mulX(scale);
	this->mulY(scale);
}

STVec2d* STVec2d::sum(STVec2d* v2)
{
	STVec2d* result = new STVec2d(this->getX() + v2->getX(), this->getY() + v2->getY());
	return result; //Probably could have inlined this...
}

STVec2d* STVec2d::diff(STVec2d* v2)
{
	STVec2d* result = new STVec2d(this->getX() - v2->getX(), this->getY() - v2->getY());
	return result; //Probably could have inlined this...
}

double STVec2d::dotProduct(STVec2d* v2)
{
	double product = 0.0;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();

	return product;
}

float STVec2d::distance(STVec2d* v2)
{
	STVec2d* connecting = this->diff(v2);
	return std::abs(connecting->length());

}



/*
	STVec3d
	3 element vector with doubles	
*/

STVec3d::STVec3d(double x, double y, double z)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
}

void STVec3d::addVec3d(STVec3d* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
	this->addZ(v2->getZ());
}

void STVec3d::subVec3d(STVec3d* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
	this->subZ(v2->getZ());
}

void STVec3d::mulScalar(double scale)
{
	this->mulX(scale);
	this->mulY(scale);
	this->mulZ(scale);

}

double STVec3d::dotProduct(STVec3d* v2)
{
	double product = 0.0;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();
	product += this->getZ() * v2->getZ();

	return product;
}

STVec3d* STVec3d::sum(STVec3d* v2)
{
	STVec3d* result = new STVec3d(this->getX() + v2->getX(), this->getY() + v2->getY(), this->getZ() + v2->getZ());
	return result; //Probably could have inlined this...
}

STVec3d* STVec3d::diff(STVec3d* v2)
{
	STVec3d* result = new STVec3d(this->getX() - v2->getX(), this->getY() - v2->getY(), this->getZ() - v2->getZ());
	return result; //Probably could have inlined this...
}

STVec3d* STVec3d::crossProduct(STVec3d* v2)
{
	STVec3d* result = new STVec3d();
	
	result->setX((this->getY() * v2->getZ()) - (this->getZ() * v2->getY()));
	result->setY((this->getZ() * v2->getX()) - (this->getX() * v2->getZ()));
	result->setZ((this->getX() * v2->getY()) - (this->getY() * v2->getX()));
	
	return result;
}

float STVec3d::distance(STVec3d* v2)
{
	STVec3d* connecting = this->diff(v2);
	return std::abs(connecting->length());

}


/*
	STVec4d
	4 element vector with doubles	
*/

STVec4d::STVec4d(double x, double y, double z, double w)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
	this->data.push_back(w);
}

void STVec4d::addVec4d(STVec4d* v2)
{
	this->addX(v2->getX());
	this->addY(v2->getY());
	this->addZ(v2->getZ());
	this->addW(v2->getW());
}

void STVec4d::subVec4d(STVec4d* v2)
{
	this->subX(v2->getX());
	this->subY(v2->getY());
	this->subZ(v2->getZ());
	this->subW(v2->getW());
}

void STVec4d::mulScalar(double scale)
{
	this->mulX(scale);
	this->mulY(scale);
	this->mulZ(scale);
	this->mulW(scale);
}

STVec4d* STVec4d::sum(STVec4d* v2)
{
	STVec4d* result = new STVec4d(this->getX() + v2->getX(), this->getY() + v2->getY(), this->getZ() + v2->getZ(), this->getW() + v2->getW());
	return result; //Probably could have inlined this...
}

STVec4d* STVec4d::diff(STVec4d* v2)
{
	STVec4d* result = new STVec4d(this->getX() - v2->getX(), this->getY() - v2->getY(), this->getZ() - v2->getZ(), this->getW() - v2->getW());
	return result; //Probably could have inlined this...
}

double STVec4d::dotProduct(STVec4d* v2)
{
	double product = 0.0;
	
	product += this->getX() * v2->getX();
	product += this->getY() * v2->getY();
	product += this->getZ() * v2->getZ();
	product += this->getW() * v2->getW();
	
	return product;
}

float STVec4d::distance(STVec4d* v2)
{
	STVec4d* connecting = this->diff(v2);
	return std::abs(connecting->length());

}

// GLSL Compatibility Vectors

/*	STVec2i
 *	2-dimensional vector with ints
 */

STVec2i::STVec2i(int x, int y)
{
	this->data.push_back(x);
	this->data.push_back(y);
}


/*	STVec3i
 *	3-dimensional vector with ints
 */

STVec3i::STVec3i(int x, int y, int z)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
}

/*	STVec4i
 *	4-dimensional vector with ints
 */

STVec4i::STVec4i(int x, int y, int z, int w)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
	this->data.push_back(w);
}

/*	STVec2ui
 *	2-dimensional vector with unsigned ints
 */

STVec2ui::STVec2ui(unsigned int x, unsigned int y)
{
	this->data.push_back(x);
	this->data.push_back(y);
}

/*	STVec3ui
 *	3-dimensional vector with unsigned ints
 */

STVec3ui::STVec3ui(unsigned int x, unsigned int y, unsigned int z)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
}

/*	STVec4ui
 *	4-dimensional vector with unsigned ints
 */

STVec4ui::STVec4ui(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	this->data.push_back(x);
	this->data.push_back(y);
	this->data.push_back(z);
	this->data.push_back(w);
}
