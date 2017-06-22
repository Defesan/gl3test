#include "stFrame.h"

STFrame::STFrame()
{
	this->origin = new STVec3f(0.0f, 0.0f, 0.0f);
	this->upVector = new STVec3f(0.0f, 1.0f, 0.0f);
	this->forwardVector = new STVec3f(0.0f, 0.0f, -1.0f);
}

STFrame::~STFrame()
{


}

void STFrame::translateLocal(float x, float y, float z)
{
	//Now this one's tricky. GLTools has it as three function calls:
	//MoveForward(z)
	//MoveUp(y)
	//MoveRight(x)
	//Of course, negative values for x, y and z, move left, down and back, rsepectively.
	//..Come to think of it, that makes those three functions quite poorly named.
	//Beyond that, they're used ONLY in the context of this function.
	//MoveForward(z) is functionally equivalent to TranslateLocal(0.0f, 0.0f, z), so...
	//Really, it just complicates the class.
	
	//now for the actual movements.
	//Given point O(the origin,) and vectors F and U(the forward and up vectors, respectively,
	//as well as a perpendicular vector R(the 'right' vector, which is constructed here by crossing F and U)
	//the function goes as follows:
	//x translation: O = O + xR
	//y translation: O = O + yU
	//z translation: O = O + zF
	//This makes sense, logically -- we're moving the origin along each vector, with the distance measured by a scaling factor.
	
	if(x != 0.0f)
	{
		STVec3f* rightVector = this->upVector->crossProduct(forwardVector);
		this->origin->setX(this->origin->getX() + rightVector->getX() * x);
		this->origin->setY(this->origin->getY() + rightVector->getY() * x);
		this->origin->setZ(this->origin->getZ() + rightVector->getZ() * x);
	}
	
	if(y != 0.0f)
	{
		this->origin->setX(this->origin->getX() + upVector->getX() * y);
		this->origin->setY(this->origin->getY() + upVector->getY() * y);
		this->origin->setZ(this->origin->getZ() + upVector->getZ() * y);
	}
	
	if(z != 0.0f)
	{
		this->origin->setX(this->origin->getX() + forwardVector->getX() * z);
		this->origin->setY(this->origin->getY() + forwardVector->getY() * z);
		this->origin->setZ(this->origin->getZ() + forwardVector->getZ() * z);
	}

}

STMatrix44f* STFrame::getMatrix(bool rotOnly)
{
	STMatrix44f* frameMatrix = new STMatrix44f();
	STVec3f* rightVector = this->upVector->crossProduct(forwardVector);
	
	frameMatrix->setColumn(0, rightVector);
	frameMatrix->setColumn(1, upVector);
	frameMatrix->setColumn(2, forwardVector);
	
	if(!rotOnly)
	{
		//If the matrix is only supposed to be the rotation matrix, the last column is all zeros...which it is, anyway.
		//Otherwise, we put in the origin.
		frameMatrix->setColumn(3, origin);
	}
	
	//The last element is a 1.
	frameMatrix->setElement(15, 1.0f);
	
	return frameMatrix;
}
	
	
STMatrix44f* STFrame::getCameraMatrix(bool rotOnly)
{
	STMatrix44f* cameraMatrix = new STMatrix44f();

	return cameraMatrix;
}

void STFrame::rotateLocalX(float angle)
{

}

void STFrame::rotateLocalY(float angle)
{

}

void STFrame::rotateLocalZ(float angle)
{

}
	
void STFrame::normalize()
{

}

void STFrame::rotateWorld(float angle, float x, float y, float z)
{

}

void STFrame::rotateLocal(float angle, float x, float y, float z)
{

}

STVec3f* worldFromLocal(STVec3f* localVector, bool rotOnly)
{
	STVec3f* worldCoords = new STVec3f();
	
	return worldCoords;
}

STVec3f* localFromWorld(STVec3f* worldVector)
{
	STVec3f* localCoords = new STVec3f();

	return localCoords;
}
	
STVec3f* transformPoint(STVec3f* point)
{
	STVec3f* result = new STVec3f();
	
	return result;
}

STVec3f* rotateVector(STVec3f* vector)
{
	STVec3f* result = new STVec3f();
	
	return result;
}
