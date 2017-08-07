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
	//This one's pretty much straightforward. It's a matrix that contains the three vectors describing the frame's rotation in R3, plus(if desired), the origin,
	//which describes its location in space.
	STMatrix44f* frameMatrix = new STMatrix44f();
	STVec3f* rightVector = this->upVector->crossProduct(forwardVector);
	
	frameMatrix->setColumn(0, rightVector);
	frameMatrix->setColumn(1, this->upVector);
	frameMatrix->setColumn(2, this->forwardVector);
	
	if(!rotOnly)
	{
		//If the matrix is only supposed to be the rotation matrix, the last column is all zeros...which it is, anyway.
		//Otherwise, we put in the origin.
		frameMatrix->setColumn(3, origin);
	}
	
	//The last element is a 1.
	frameMatrix->set(3, 3, 1.0f);
	return frameMatrix;
}
	
	
STMatrix44f* STFrame::getCameraMatrix(bool rotOnly)
{
	//This... I'm going to have to closely examine this.
	STMatrix44f* cameraMatrix = new STMatrix44f();
	
	STVec3f* backVector = new STVec3f(this->forwardVector);
	backVector->mulScalar(-1.0f);
	
	STVec3f* leftVector = this->upVector->crossProduct(backVector);
	
	//The matrix in this case is the transpose of the one above, with the back and left vectors substituted for forward and right. Up is still up.
	cameraMatrix->setRow(0, leftVector);
	cameraMatrix->setRow(1, this->upVector);
	cameraMatrix->setRow(2, backVector);
	cameraMatrix->set(3, 3, 1.0f);
	
	//And for this one, translation is a bit harder, as well.
	if(!rotOnly)
	{
		STMatrix44f* translationMatrix = new STMatrix44f();
		STMatrix44f* resultMatrix;
		
		translationMatrix->loadTranslationMatrix((this->origin->getX() * -1.0f), (this->origin->getY() * -1.0f), (this->origin->getZ() * -1.0f));
		resultMatrix = cameraMatrix->mul(translationMatrix);
		
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				cameraMatrix->set(i, j, resultMatrix->get(i, j));
			}
		}
	
	}

	return cameraMatrix;
}

void STFrame::rotateLocalX(float angle)
{
	STVec3f* rightVector = this->upVector->crossProduct(this->forwardVector);
	STVec3f* resultVector = new STVec3f();
	
	STMatrix44f* rotationMatrix = new STMatrix44f();
	rotationMatrix->loadRotationMatrix(angle, rightVector->getX(), rightVector->getY(), rightVector->getZ());
	
	resultVector->setX((rotationMatrix->getElement(0) * this->upVector->getX()) +
						(rotationMatrix->getElement(4) * this->upVector->getY()) +
						(rotationMatrix->getElement(8) * this->upVector->getZ()));
	resultVector->setY((rotationMatrix->getElement(1) * this->upVector->getX()) +
						(rotationMatrix->getElement(5) * this->upVector->getY()) +
						(rotationMatrix->getElement(9) * this->upVector->getZ()));
	resultVector->setZ((rotationMatrix->getElement(2) * this->upVector->getX()) +
						(rotationMatrix->getElement(6) * this->upVector->getY()) +
						(rotationMatrix->getElement(10) * this->upVector->getZ()));
						
	this->upVector = new STVec3f(resultVector);
	
	resultVector->setX((rotationMatrix->getElement(0) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(4) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(8) * this->forwardVector->getZ()));
	resultVector->setY((rotationMatrix->getElement(1) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(5) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(9) * this->forwardVector->getZ()));
	resultVector->setZ((rotationMatrix->getElement(2) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(6) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(10) * this->forwardVector->getZ()));
						
	this->forwardVector = new STVec3f(resultVector);
}

void STFrame::rotateLocalY(float angle)
{
	STVec3f* resultVector = new STVec3f();
	
	STMatrix44f* rotationMatrix = new STMatrix44f();
	rotationMatrix->loadRotationMatrix(angle, this->upVector->getX(), this->upVector->getY(), this->upVector->getZ());
	
	resultVector->setX((rotationMatrix->getElement(0) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(4) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(8) * this->forwardVector->getZ()));
	resultVector->setY((rotationMatrix->getElement(1) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(5) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(9) * this->forwardVector->getZ()));
	resultVector->setZ((rotationMatrix->getElement(2) * this->forwardVector->getX()) +
						(rotationMatrix->getElement(6) * this->forwardVector->getY()) +
						(rotationMatrix->getElement(10) * this->forwardVector->getZ()));
						
	this->forwardVector = new STVec3f(resultVector);
}

void STFrame::rotateLocalZ(float angle)
{
	STVec3f* resultVector = new STVec3f();
	
	STMatrix44f* rotationMatrix = new STMatrix44f();
	rotationMatrix->loadRotationMatrix(angle, this->forwardVector->getX(), this->forwardVector->getY(), this->forwardVector->getZ());
	
	resultVector->setX((rotationMatrix->getElement(0) * this->upVector->getX()) +
						(rotationMatrix->getElement(4) * this->upVector->getY()) +
						(rotationMatrix->getElement(8) * this->upVector->getZ()));
	resultVector->setY((rotationMatrix->getElement(1) * this->upVector->getX()) +
						(rotationMatrix->getElement(5) * this->upVector->getY()) +
						(rotationMatrix->getElement(9) * this->upVector->getZ()));
	resultVector->setZ((rotationMatrix->getElement(2) * this->upVector->getX()) +
						(rotationMatrix->getElement(6) * this->upVector->getY()) +
						(rotationMatrix->getElement(10) * this->upVector->getZ()));
						
	this->upVector = new STVec3f(resultVector);
}
	
void STFrame::normalize()
{
	//Going by pure math, this shouldn't change anything. But unfortunately, we live in the real world, so floating point drift happens.
	STVec3f* crossVector = this->upVector->crossProduct(this->forwardVector);
	this->forwardVector = crossVector->crossProduct(this->upVector);		
	this->upVector->normalize();
	this->forwardVector->normalize();
}

void STFrame::rotateWorld(float angle, float x, float y, float z)
{
	STMatrix44f* rotationMatrix = new STMatrix44f();
	STVec3f* tempVec = new STVec3f();

	rotationMatrix->loadRotationMatrix(angle, x, y, z);
	
	tempVec->setX((rotationMatrix->getElement(0) * this->upVector->getX()) +
					(rotationMatrix->getElement(4) * this->upVector->getY()) +
					(rotationMatrix->getElement(8) * this->upVector->getZ()));
	tempVec->setY((rotationMatrix->getElement(1) * this->upVector->getX()) +
					(rotationMatrix->getElement(5) * this->upVector->getY()) +
					(rotationMatrix->getElement(9) * this->upVector->getZ()));
	tempVec->setZ((rotationMatrix->getElement(2) * this->upVector->getX()) +
					(rotationMatrix->getElement(6) * this->upVector->getY()) +
					(rotationMatrix->getElement(10) * this->upVector->getZ()));
						
	this->upVector = new STVec3f(tempVec);
	
	tempVec->setX((rotationMatrix->getElement(0) * this->forwardVector->getX()) +
					(rotationMatrix->getElement(4) * this->forwardVector->getY()) +
					(rotationMatrix->getElement(8) * this->forwardVector->getZ()));
	tempVec->setY((rotationMatrix->getElement(1) * this->forwardVector->getX()) +
					(rotationMatrix->getElement(5) * this->forwardVector->getY()) +
					(rotationMatrix->getElement(9) * this->forwardVector->getZ()));
	tempVec->setZ((rotationMatrix->getElement(2) * this->forwardVector->getX()) +
					(rotationMatrix->getElement(6) * this->forwardVector->getY()) +
					(rotationMatrix->getElement(10) * this->forwardVector->getZ()));
	
	this->forwardVector = new STVec3f(tempVec);
}

void STFrame::rotateLocal(float angle, float x, float y, float z)
{
	STVec3f* worldVec = new STVec3f();
	STVec3f* localVec = new STVec3f(x, y, z);
	
	worldVec = this->worldFromLocal(localVec, true);
	this->rotateWorld(angle, worldVec->getX(), worldVec->getY(), worldVec->getZ());
	//Well THAT was easy!
}

STVec3f* STFrame::worldFromLocal(STVec3f* localVector, bool rotOnly)
{
	STVec3f* worldCoords = new STVec3f();
	
	STMatrix44f* rotationMatrix = this->getMatrix(true);
	
	//Rotate the local vector by the frame's coordinate system
	worldCoords->setX((rotationMatrix->getElement(0) * localVector->getX()) +
					(rotationMatrix->getElement(4) * localVector->getY()) +
					(rotationMatrix->getElement(8) * localVector->getZ()));
	worldCoords->setY((rotationMatrix->getElement(1) * localVector->getX()) +
					(rotationMatrix->getElement(5) * localVector->getY()) +
					(rotationMatrix->getElement(9) * localVector->getZ()));
	worldCoords->setZ((rotationMatrix->getElement(2) * localVector->getX()) +
					(rotationMatrix->getElement(6) * localVector->getY()) +
					(rotationMatrix->getElement(10) * localVector->getZ()));
	
	//For absolute coords, add the frame's origin, as well.			
	if(!rotOnly)
	{
		worldCoords->addVec3f(this->origin);	
	}
	
	return worldCoords;
}

STVec3f* STFrame::localFromWorld(STVec3f* worldVector)
{
	STVec3f* localCoords = new STVec3f();
	
	STMatrix44f* rotationMatrix = this->getMatrix(true);
	STMatrix44f* inverseMatrix = rotationMatrix->invert();
	
	//Translate the world coordinates
	localCoords->setX(worldVector->getX() - this->origin->getX());
	localCoords->setX(worldVector->getY() - this->origin->getY());
	localCoords->setX(worldVector->getZ() - this->origin->getZ());
	
	//Rotate back from world coordinates with the inverse matrix
	//I think I'll pull this block out as its own function... I'm using it too often.
	localCoords->setX((inverseMatrix->getElement(0) * worldVector->getX()) +
					(inverseMatrix->getElement(4) * worldVector->getY()) +
					(inverseMatrix->getElement(8) * worldVector->getZ()));
	localCoords->setY((inverseMatrix->getElement(1) * worldVector->getX()) +
					(inverseMatrix->getElement(5) * worldVector->getY()) +
					(inverseMatrix->getElement(9) * worldVector->getZ()));
	localCoords->setZ((inverseMatrix->getElement(2) * worldVector->getX()) +
					(inverseMatrix->getElement(6) * worldVector->getY()) +
					(inverseMatrix->getElement(10) * worldVector->getZ()));
	

	return localCoords;
}
	
STVec3f* STFrame::transformPoint(STVec3f* point)
{
	STVec3f* result = new STVec3f();
	STMatrix44f* frameMatrix = this->getMatrix(false);
	
	result->setX((frameMatrix->getElement(0) * point->getX()) + 
					(frameMatrix->getElement(4) * point->getY()) +
					(frameMatrix->getElement(8) * point->getZ()) + 
					frameMatrix->getElement(12));
	result->setY((frameMatrix->getElement(1) * point->getX()) + 
					(frameMatrix->getElement(5) * point->getY()) +
					(frameMatrix->getElement(9) * point->getZ()) + 
					frameMatrix->getElement(13));
	result->setZ((frameMatrix->getElement(2) * point->getX()) + 
					(frameMatrix->getElement(6) * point->getY()) +
					(frameMatrix->getElement(10) * point->getZ()) + 
					frameMatrix->getElement(14));
	
	return result;
}

STVec3f* STFrame::rotateVector(STVec3f* vector)
{
	STVec3f* result = new STVec3f();
	STMatrix44f* frameRotation = this->getMatrix(true);
	
	result->setX((frameRotation->getElement(0) * vector->getX()) + 
					(frameRotation->getElement(4) * vector->getY()) +
					(frameRotation->getElement(8) * vector->getZ()));
	result->setY((frameRotation->getElement(1) * vector->getX()) + 
					(frameRotation->getElement(5) * vector->getY()) +
					(frameRotation->getElement(9) * vector->getZ()));
	result->setZ((frameRotation->getElement(2) * vector->getX()) + 
					(frameRotation->getElement(6) * vector->getY()) +
					(frameRotation->getElement(10) * vector->getZ()));
	
	return result;
}
