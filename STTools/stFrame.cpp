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
	STVec3f* crossVector = this->upVector->crossProduct(this->forwardVector);
	this->forwardVector = crossVector->crossProduct(this->upVector);
	this->upVector->normalize();
	this->forwardVector->normalize();
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
