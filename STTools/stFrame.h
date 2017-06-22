#ifndef __ST_FRAME_H__
#define __ST_FRAME_H__

#include "../STLinear/stMatrix.h"
#include "../STLinear/stVector.h"

#include <vector>
#include <cmath>
#include <iostream>

//This class defines the POV that the environment is seen through, in terms of an up vector, a forward vector, and an origin point.
//Basically, it describes a translated plane in 3D coordinate space. This is combined with the frustum(which describes the volume of space visible to the frame)
//and transformed by the model-view-projection matrix into two-dimensional screen coordinates.

class STFrame
{
private:
//So... There's only three vectors here. For some reason(?) RSW made these protected, but there's no hint that he ever derives a class from this one, so...
	STVec3f* origin;
	STVec3f* upVector;
	STVec3f* forwardVector;

public:
	STFrame();	//Constructor.
	~STFrame();
	
	void setOrigin(STVec3f* origin) {this->origin = origin;};
	void setOrigin(float x, float y, float z) {this->origin = new STVec3f(x, y, z);};
	
	void setUp(STVec3f* upVector) {this->upVector = upVector;};
	void setUp(float x, float y, float z) {this->upVector = new STVec3f(x, y, z);};
	
	void setForward(STVec3f* forwardVector) {this->forwardVector = forwardVector;};
	void setForward(float x, float y, float z) {this->forwardVector = new STVec3f(x, y, z);};
	
	STVec3f* getOrigin() {return this->origin;};
	STVec3f* getUp() {return this->upVector;};
	STVec3f* getForward() {return this->forwardVector;};
	
	//These two are simple enough -- we HAVE these axes.
	STVec3f* getYAxis() {return this->upVector;};
	STVec3f* getZAxis() {return this->forwardVector;};
	
	//This one's a bit trickier.
	STVec3f* getXAxis() {return this->upVector->crossProduct(forwardVector);};
	
	//Again, this is simple enough, and straightforward.
	void translateWorldBy(float x, float y, float z) {this->origin->addVec3f(new STVec3f(x, y, z));};
	
	//But this...slightly trickier.
	void translateLocal(float x, float y, float z);
	
	//Now all of the functions that most definitely don't fit in the header. Sorry, RSW, but I don't roll that way unless told to.
	STMatrix44f* getMatrix(bool rotOnly);
	STMatrix44f* getCameraMatrix(bool rotOnly);	//C++ no longer appreciates default parameters.
	
	void rotateLocalX(float angle);
	void rotateLocalY(float angle);
	void rotateLocalZ(float angle);
	
	void normalize();
	
	void rotateWorld(float angle, STVec3f* axis) {this->rotateWorld(angle, axis->getX(), axis->getY(), axis->getZ());};
	void rotateWorld(float angle, float x, float y, float z);
	
	void rotateLocal(float angle, STVec3f* axis) {this->rotateLocal(angle, axis->getX(), axis->getY(), axis->getZ());};
	void rotateLocal(float angle, float x, float y, float z);
	
	//Testing a theory postumated in the GLTools code...
	STVec3f* worldFromLocal(STVec3f* localVector, bool rotOnly);
	STVec3f* localFromWorld(STVec3f* worldVector);
	
	STVec3f* transformPoint(STVec3f* point);
	STVec3f* rotateVector(STVec3f* vector);
};
#endif //__ST_FRAME_H__
