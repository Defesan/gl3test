#include "stFrustum.h"

void STFrustum::init()
{
	this->projectionMatrix = new STMatrix44f();
	
	this->nearUpLeft = new STVec4f();
	this->nearUpRight = new STVec4f();
	this->nearDownLeft = new STVec4f();
	this->nearDownRight = new STVec4f();
	this->farUpLeft = new STVec4f();
	this->farUpRight = new STVec4f();
	this->farDownLeft = new STVec4f();
	this->farDownRight = new STVec4f();
	
	this->nearUpLeftTrans = new STVec4f();
	this->nearUpRightTrans = new STVec4f();
	this->nearDownLeftTrans = new STVec4f();
	this->nearDownRightTrans = new STVec4f();
	this->farUpLeftTrans = new STVec4f();
	this->farUpRightTrans = new STVec4f();
	this->farDownLeftTrans = new STVec4f();
	this->farDownRightTrans = new STVec4f();
	
	this->nearPlane = new STVec4f();
	this->farPlane = new STVec4f();
	this->leftPlane = new STVec4f();
	this->rightPlane = new STVec4f();
	this->topPlane = new STVec4f();
	this->bottomPlane = new STVec4f();
	
	this->initialized = true;

}

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
	
	if(!initialized)
	{
		this->init();
	}
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
	this->projectionMatrix->setElement(14, -(((2.0f * (farDistance * nearDistance))/(farDistance - nearDistance))));
	this->projectionMatrix->setElement(15, 0.0f);
	//And now we set up the vertices describing the MUCH more interesting frustum.
	
	this->nearUpLeft->setX(xMin);
	this->nearUpLeft->setY(yMax);
	this->nearUpLeft->setZ(-nearDistance);
	this->nearUpLeft->setW(1.0f);
	
	this->nearDownLeft->setX(xMin);
	this->nearDownLeft->setY(yMin);
	this->nearDownLeft->setZ(-nearDistance);
	this->nearDownLeft->setW(1.0f);
	
	this->nearUpRight->setX(xMax);
	this->nearUpRight->setY(yMax);
	this->nearUpRight->setZ(-nearDistance);
	this->nearUpRight->setW(1.0f);
	
	this->nearDownRight->setX(xMax);
	this->nearDownRight->setY(yMin);
	this->nearDownRight->setZ(-nearDistance);
	this->nearDownRight->setW(1.0f);
	
	this->farUpLeft->setX(xMinF);
	this->farUpLeft->setY(yMaxF);
	this->farUpLeft->setZ(-farDistance);
	this->farUpLeft->setW(1.0f);
	
	this->farDownLeft->setX(xMinF);
	this->farDownLeft->setY(yMinF);
	this->farDownLeft->setZ(-farDistance);
	this->farDownLeft->setW(1.0f);
	
	this->farUpRight->setX(xMaxF);
	this->farUpRight->setY(yMaxF);
	this->farUpRight->setZ(-farDistance);
	this->farUpRight->setW(1.0f);
	
	this->farDownRight->setX(xMaxF);
	this->farDownRight->setY(yMinF);
	this->farDownRight->setZ(-farDistance);
	this->farDownRight->setW(1.0f);

}

void STFrustum::setOrthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	
	//Set up the projection matrix
	if(!initialized)
	{
		this->init();
	}
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

//Transforms the frustum so that it encloses the volume actually seen by the 'camera', the associated STFrame.
//Apparently tricky. Also apparently I don't have to do the heavy lifting, because I have an example to work off of.
//Really looking forward to stretching my brain with some exercises that even I will admit are more my speed right now.
void STFrustum::transform(STFrame* camera)
{
	STMatrix44f* rotationMatrix = new STMatrix44f();
	
	STVec3f* forwardVector = camera->getForward()->copy();
	STVec3f* upVector = camera->getUp();
	STVec3f* origin = camera->getOrigin();
	STVec3f* rightVector = upVector->crossProduct(forwardVector);
	
	//Point down the negative z axis
	forwardVector->mulScalar(-1.0f);
	
	//Build the (slightly non-standard) rotation matrix
	//We're working off of a transform, not a straight up rotation,
	//but since the transformation SHOULD be orthonormal, it functions as a rotation.
	rotationMatrix->setElement(0, rightVector->getX());
	rotationMatrix->setElement(1, rightVector->getY());
	rotationMatrix->setElement(2, rightVector->getZ());
	rotationMatrix->setElement(3, 0.0f);
	
	rotationMatrix->setElement(4, upVector->getX());
	rotationMatrix->setElement(5, upVector->getY());
	rotationMatrix->setElement(6, upVector->getZ());
	rotationMatrix->setElement(7, 0.0f);
	
	rotationMatrix->setElement(8, forwardVector->getX());
	rotationMatrix->setElement(9, forwardVector->getY());
	rotationMatrix->setElement(10, forwardVector->getZ());
	rotationMatrix->setElement(11, 0.0f);
	
	rotationMatrix->setElement(12, origin->getX());
	rotationMatrix->setElement(13, origin->getY());
	rotationMatrix->setElement(14, origin->getZ());
	rotationMatrix->setElement(15, 1.0f);
	
	//Now that we have the transformation matrix, transform the vertices of the frustum to their new positions relative to the camera.
	this->nearUpLeftTrans = rotationMatrix->mulVector(this->nearUpLeft);
	this->nearUpRightTrans = rotationMatrix->mulVector(this->nearUpRight);
	this->nearDownLeftTrans = rotationMatrix->mulVector(this->nearDownLeft);
	this->nearDownRightTrans = rotationMatrix->mulVector(this->nearDownRight);
	
	this->farUpLeftTrans = rotationMatrix->mulVector(this->farUpLeft);
	this->farUpRightTrans = rotationMatrix->mulVector(this->farUpRight);
	this->farDownLeftTrans = rotationMatrix->mulVector(this->farDownLeft);
	this->farDownRightTrans = rotationMatrix->mulVector(this->farDownRight);

	//Now generate the plane equations.
	this->nearPlane = new STVec4f();
	this->farPlane = new STVec4f();
	this->topPlane = new STVec4f();
	this->bottomPlane = new STVec4f();
	this->rightPlane = new STVec4f();
	this->leftPlane = new STVec4f();
	
	//This one is actually a bit of mind bender if you come at it cold. The points have to be listed counter-clockwise,
	//facing *into* the frustum *through* the plane they define. The near plane is the easiest, since that's the default.
	//The far plane is only a little harder, since it's the near plane, just reversed.
	//Then you have to stretch your spacial reorientation muscles and look at the frustum from different angles, which is...
	//Well, it's not easy. 
	this->nearPlane->genPlaneEquation(this->nearUpRightTrans, this->nearUpLeftTrans, this->nearDownLeftTrans);
	this->farPlane->genPlaneEquation(this->farUpLeftTrans, this->farUpRightTrans, this->farDownLeftTrans);
	
	this->topPlane->genPlaneEquation(this->nearUpLeftTrans, this->nearUpRightTrans, this->farUpRightTrans);
	this->bottomPlane->genPlaneEquation(this->nearDownLeftTrans, this->farDownLeftTrans, this->farDownRightTrans);
	
	this->leftPlane->genPlaneEquation(this->nearDownLeftTrans, this->nearUpLeftTrans, this->farUpLeftTrans);
	this->rightPlane->genPlaneEquation(this->nearDownRightTrans, this->farDownRightTrans, this->farUpRightTrans);
	//Whew!
}

bool STFrustum::testSphere(STVec3f* origin, float radius)
{
	
	float distance = 0.0f;
	
	distance = this->nearPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	distance = this->farPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	distance = this->leftPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	distance = this->rightPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	distance = this->topPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	distance = this->bottomPlane->planeDistanceFromPoint(origin);
	if(distance + radius <= 0.0f)
	{
		return false;
	}
	
	return true;
}
