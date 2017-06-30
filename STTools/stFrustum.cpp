#include "stFrustum.h"

void STFrustum::setPerspective(float fov, float aspect, float nearDistance, float farDistance)
{
	//For this, we'll be calculating the x and y minimums and maximums. The far clipping plane is larger than the near one,
	//by a factor determined by the field of view, and the minimum and maximum Z values are nearDistance and farDistance
	//Near plane corners
	float xMin = 0.0f;
	float xMax = 0.0f;
	float yMin = 0.0f;
	float yMax = 0.0f;
	
	//Far plane corners
	float xMinF = 0.0f;
	float xMaxF = 0.0f;
	float yMinF = 0.0f;
	float yMaxF = 0.0f;	
	
	this->projectionMatrix = new STMatrix44f();
	this->projectionMatrix->loadIdentity();
	
	//Near plane calculations
	//We start by calculating one of the x or y values(yMax in this case) based on the field of view.
	//I'll admit that I don't fully understand this one -- not enough to explain it -- but it does make intuitive sense.
	yMax = nearDistance * (float)(tan(fov * (PI/360.0f)));
	yMin = -yMax;
	xMin = aspect * yMin; //Once one is calculated, the other is simple enough.
	xMax = -xMin;
	
	//Far plane calculations
	yMaxF = farDistance * (float)(tan(fov * (PI/360.0f)));
	yMinF = -yMaxF;
	xMinF = aspect * yMinF; 
	xMaxF = -xMinF;
	
	this->projectionMatrix->setElement(0, ((2.0f * nearDistance) / (xMax - xMin)));
	this->projectionMatrix->setElement(5, ((2.0f * nearDistance) / (yMax - yMin)));
	this->projectionMatrix->setElement(8, ((xMax + xMin) / (xMax - xMin)));
	this->projectionMatrix->setElement(9, ((yMax + yMin) / (yMax - yMin)));
	this->projectionMatrix->setElement(10, -((farDistance + nearDistance) / (farDistance - nearDistance)));
	this->projectionMatrix->setElement(11, -1.0f);
	this->projectionMatrix->setElement(14, -((2.0f * (farDistance * nearDistance))/(farDistance - nearDistance)));
	this->projectionMatrix->setElement(15, 0.0f);
	
	//And now we set up the vertices describing the MUCH more interesting frustum.
	
	this->nearUpLeft->setX(xMin);
	this->nearUpLeft->setY(yMax);
	this->nearUpLeft->setZ(nearDistance);
	this->nearUpLeft->setW(1.0f);
	
	this->nearDownLeft->setX(xMin);
	this->nearDownLeft->setY(yMin);
	this->nearDownLeft->setZ(nearDistance);
	this->nearDownLeft->setW(1.0f);
	
	this->nearUpRight->setX(xMax);
	this->nearUpRight->setY(yMax);
	this->nearUpRight->setZ(nearDistance);
	this->nearUpRight->setW(1.0f);
	
	this->nearDownRight->setX(xMax);
	this->nearDownRight->setY(yMin);
	this->nearDownRight->setZ(nearDistance);
	this->nearDownRight->setW(1.0f);
	
	this->farUpLeft->setX(xMinF);
	this->farUpLeft->setY(yMaxF);
	this->farUpLeft->setZ(farDistance);
	this->farUpLeft->setW(1.0f);
	
	this->farDownLeft->setX(xMinF);
	this->farDownLeft->setY(yMinF);
	this->farDownLeft->setZ(farDistance);
	this->farDownLeft->setW(1.0f);
	
	this->farUpRight->setX(xMaxF);
	this->farUpRight->setY(yMaxF);
	this->farUpRight->setZ(farDistance);
	this->farUpRight->setW(1.0f);
	
	this->farDownRight->setX(xMaxF);
	this->farDownRight->setY(yMinF);
	this->farDownRight->setZ(farDistance);
	this->farDownRight->setW(1.0f);
	

}

void STFrustum::setOrthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//Set up the projection matrix
	this->projectionMatrix = new STMatrix44f();
	this->projectionMatrix->loadOrthoMatrix(xMin, xMax, yMin, yMax, zMin, zMax);
	this->projectionMatrix->set(3,3,1.0f);
	
	//This sequence is just describing the coordinates of the view frustum's eight vertices
	//In the orthographic case, it's less of a frustum than, you know, *a rectangular solid*.
	//e.g. nearUpLeft: X is 'left', or xMin; Y is 'up', or yMax; Z is 'near', or zMin.
	this->nearUpLeft->setX(xMin);
	this->nearUpLeft->setY(yMax);
	this->nearUpLeft->setZ(zMin);
	this->nearUpLeft->setW(1.0f);
	
	this->nearDownLeft->setX(xMin);
	this->nearDownLeft->setY(yMin);
	this->nearDownLeft->setZ(zMin);
	this->nearDownLeft->setW(1.0f);
	
	this->nearUpRight->setX(xMax);
	this->nearUpRight->setY(yMax);
	this->nearUpRight->setZ(zMin);
	this->nearUpRight->setW(1.0f);
	
	this->nearDownRight->setX(xMax);
	this->nearDownRight->setY(yMin);
	this->nearDownRight->setZ(zMin);
	this->nearDownRight->setW(1.0f);
	
	this->farUpLeft->setX(xMin);
	this->farUpLeft->setY(yMax);
	this->farUpLeft->setZ(zMax);
	this->farUpLeft->setW(1.0f);
	
	this->farDownLeft->setX(xMin);
	this->farDownLeft->setY(yMin);
	this->farDownLeft->setZ(zMax);
	this->farDownLeft->setW(1.0f);
	
	this->farUpRight->setX(xMax);
	this->farUpRight->setY(yMax);
	this->farUpRight->setZ(zMax);
	this->farUpRight->setW(1.0f);
	
	this->farDownRight->setX(xMax);
	this->farDownRight->setY(yMin);
	this->farDownRight->setZ(zMax);
	this->farDownRight->setW(1.0f);

}

void STFrustum::transform(STFrame* camera)
{


}

bool STFrustum::testSphere(STVec3f* origin, float radius)
{
	bool returnVal = false;
	
	
	return returnVal;
}
