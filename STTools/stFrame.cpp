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

STVec3f* STFrame::getXAxis()
{
	STVec3f* result = new STVec3f();
	
	return result;
}

void STFrame::translateLocalBy(float x, float y, float z)
{


}

STMatrix44f* STFrame::getMatrix(bool rotOnly)
{
	STMatrix44f* frameMatrix = new STMatrix44f();

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
