#ifndef __ST_FRUSTUM_H__
#define __ST_FRUSTUM_H__

#include "../STLinear/stMatrix.h"
#include "../STLinear/stVector.h"

#include "stFrame.h"

#include <vector>
#include <cmath>
#include <iostream>

#ifndef PI
#define PI 3.1415926f
#endif


class STFrustum
{
private:
STMatrix44f* projectionMatrix;

//The eight untransformed points describing the frustum:
STVec4f* nearUpLeft;
STVec4f* nearUpRight;
STVec4f* nearDownLeft;
STVec4f* nearDownRight;

STVec4f* farUpLeft;
STVec4f* farUpRight;
STVec4f* farDownLeft;
STVec4f* farDownRight;

//The eight transformed points

STVec4f* nearUpLeftTrans;
STVec4f* nearUpRightTrans;
STVec4f* nearDownLeftTrans;
STVec4f* nearDownRightTrans;

STVec4f* farUpLeftTrans;
STVec4f* farUpRightTrans;
STVec4f* farDownLeftTrans;
STVec4f* farDownRightTrans;

//The six planar vectors
STVec4f* nearPlane;
STVec4f* farPlane;	//Wasn't this a thing in Final Fantasy X?
STVec4f* topPlane;
STVec4f* bottomPlane;
STVec4f* rightPlane;
STVec4f* leftPlane;

bool initialized = false;

public:
STFrustum() {this->init();};
STFrustum(float fov, float aspect, float nearDistance, float farDistance) {this->setPerspective(fov, aspect, nearDistance, farDistance);};
STFrustum(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {this->setOrthographic(xMin, xMax, yMin, yMax, zMin, zMax);};

void init();	//Initialize members

STMatrix44f* getProjectionMatrix() {return this->projectionMatrix;};

void setPerspective(float fov, float aspect, float nearDistance, float farDistance);
void setOrthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

void transform(STFrame* camera);

bool testSphere(float x, float y, float z, float radius) {return this->testSphere(new STVec3f(x,y,z), radius);};
bool testSphere(STVec3f* origin, float radius);

};
#endif //ST_FRUSTUM_H__
