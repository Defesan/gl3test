#ifndef __ST_VECTOR_H__
#define __ST_VECTOR_H__

#include <cmath>
#include <vector>
#include <iostream>
/*
	Apparently I can occasionally use a 2D vector?
 */
 
class STVec2f
{
private:
	std::vector<float> data;

public:
	STVec2f(float x, float y);
	STVec2f() : STVec2f(0.0f, 0.0f) {};
	
	std::vector<float> getData() {return this->data;};
	float* getDataArray() {return this->data.data();};
	
	float getX() {return this->data[0];};
	float getY() {return this->data[1];};

	void setX(float x) {this->data[0] = x;};
	void setY(float y) {this->data[1] = y;};
	
	void addX(float x) {this->data[0] += x;};
	void addY(float y) {this->data[1] += y;};
	
	void subX(float x) {this->data[0] -= x;};
	void subY(float y) {this->data[1] -= y;};
	
	void mulX(float scale) {this->data[0] *= scale;};
	void mulY(float scale) {this->data[1] *= scale;};
	
	void addVec2f(STVec2f* v2);
	void subVec2f(STVec2f* v2);
	STVec2f* sum(STVec2f* v2);		//Returns a new vector that is the sum of this vector and another.
	STVec2f* diff(STVec2f* v2);		//Returns a new vector that is the difference between this vector and another.
	void mulScalar(float scale);
	float dotProduct(STVec2f* v2);
	float length() {return sqrtf(this->dotProduct(this));};
	float distance(STVec2f* v2);
	bool closeEnough(STVec2f* v2, float delta);
	bool closeEnough(float x, float y, float delta);
};


class STVec3f
{
private:
	std::vector<float> data;
	
public:
	STVec3f(float x, float y, float z);
	STVec3f(STVec3f* original);
	STVec3f() : STVec3f(0.0f, 0.0f, 0.0f) {};
	
	std::vector<float> getData() {return this->data;};
	float* getDataArray() {return this->data.data();};
	
	float get(int index) {return this->data[index];};
	void set(int index, float val) {this->data[index] = val;};
	
	float getX() {return this->data[0];};
	float getY() {return this->data[1];};
	float getZ() {return this->data[2];};

	void setX(float x) {this->data[0] = x;};
	void setY(float y) {this->data[1] = y;};
	void setZ(float z) {this->data[2] = z;};
	
	void addX(float x) {this->data[0] += x;};
	void addY(float y) {this->data[1] += y;};
	void addZ(float z) {this->data[2] += z;};
	
	void subX(float x) {this->data[0] -= x;};
	void subY(float y) {this->data[1] -= y;};
	void subZ(float z) {this->data[2] -= z;};
	
	void mulX(float scale) {this->data[0] *= scale;};
	void mulY(float scale) {this->data[1] *= scale;};
	void mulZ(float scale) {this->data[2] *= scale;};
	
	void addVec3f(STVec3f* v2);
	void subVec3f(STVec3f* v2);
	void mulScalar(float scale);
	STVec3f* sum(STVec3f* v2);
	STVec3f* diff(STVec3f* v2);
	float dotProduct(STVec3f* v2);
	STVec3f* crossProduct(STVec3f* v2);
	float length() {return sqrtf(this->dotProduct(this));};
	float distance(STVec3f* v2);
	bool closeEnough(STVec3f* v2, float delta);
	bool closeEnough(float x, float y, float z, float delta);
	void print();
	void normalize();
	STVec3f* copy();
};

class STVec4f
{
private:
	std::vector<float> data;
	
public:
	STVec4f(float x, float y, float z, float w);
	STVec4f() : STVec4f(0.0f, 0.0f, 0.0f, 0.0f) {};
	
	std::vector<float> getData() {return this->data;};
	float* getDataArray() {return this->data.data();};
	
	float getX() {return this->data[0];};
	float getY() {return this->data[1];};
	float getZ() {return this->data[2];};
	float getW() {return this->data[3];};

	void setX(float x) {this->data[0] = x;};
	void setY(float y) {this->data[1] = y;};
	void setZ(float z) {this->data[2] = z;};
	void setW(float w) {this->data[3] = w;};
	
	void addX(float x) {this->data[0] += x;};
	void addY(float y) {this->data[1] += y;};
	void addZ(float z) {this->data[2] += z;};
	void addW(float w) {this->data[3] += w;};
	
	void subX(float x) {this->data[0] -= x;};
	void subY(float y) {this->data[1] -= y;};
	void subZ(float z) {this->data[2] -= z;};
	void subW(float w) {this->data[3] -= w;};
	
	void mulX(float scale) {this->data[0] *= scale;};
	void mulY(float scale) {this->data[1] *= scale;};
	void mulZ(float scale) {this->data[2] *= scale;};
	void mulW(float scale) {this->data[3] *= scale;};
	
	void addVec4f(STVec4f* v2);
	void subVec4f(STVec4f* v2);
	void mulScalar(float scale);
	STVec4f* sum(STVec4f* v2);
	STVec4f* diff(STVec4f* v2);
	float dotProduct(STVec4f* v2);
	float length() {return sqrtf(this->dotProduct(this));};
	float distance(STVec4f* v2);
	bool closeEnough(STVec4f* v2, float delta);
	bool closeEnough(float x, float y, float z, float w, float delta);
	void print() {std::cout << "X = " << this->getX() << " Y = " << this->getY() << " Z = " << this->getZ() << " W = " << this->getW() << std::endl;};
	void genPlaneEquation(STVec4f* p1, STVec4f* p2, STVec4f* p3);
	float planeDistanceFromPoint(STVec3f* point);
};


class STVec2d
{
private:
	std::vector<double> data;

public:
	STVec2d(double x, double y);
	STVec2d() : STVec2d(0.0, 0.0) {};
	
	std::vector<double> getData() {return this->data;};
	double* getDataArray() {return this->data.data();};
	
	double getX() {return this->data[0];};
	double getY() {return this->data[1];};

	void setX(double x) {this->data[0] = x;};
	void setY(double y) {this->data[1] = y;};
	
	void addX(double x) {this->data[0] += x;};
	void addY(double y) {this->data[1] += y;};
	
	void subX(double x) {this->data[0] -= x;};
	void subY(double y) {this->data[1] -= y;};
	
	void mulX(double scale) {this->data[0] *= scale;};
	void mulY(double scale) {this->data[1] *= scale;};
	
	void addVec2d(STVec2d* v2);
	void subVec2d(STVec2d* v2);
	void mulScalar(double scale);
	STVec2d* sum(STVec2d* v2);
	STVec2d* diff(STVec2d* v2);
	double dotProduct(STVec2d* v2);
	double length() {return sqrt(this->dotProduct(this));};
	float distance(STVec2d* v2);
};


class STVec3d
{
private:
	std::vector<double> data;
	
public:
	STVec3d(double x, double y, double z);
	STVec3d() : STVec3d(0.0, 0.0, 0.0) {};
	
	std::vector<double> getData() {return this->data;};
	double* getDataArray() {return this->data.data();};
	
	double getX() {return this->data[0];};
	double getY() {return this->data[1];};
	double getZ() {return this->data[2];};

	void setX(double x) {this->data[0] = x;};
	void setY(double y) {this->data[1] = y;};
	void setZ(double z) {this->data[2] = z;};
	
	void addX(double x) {this->data[0] += x;};
	void addY(double y) {this->data[1] += y;};
	void addZ(double z) {this->data[2] += z;};
	
	void subX(double x) {this->data[0] -= x;};
	void subY(double y) {this->data[1] -= y;};
	void subZ(double z) {this->data[2] -= z;};
	
	void mulX(double scale) {this->data[0] *= scale;};
	void mulY(double scale) {this->data[1] *= scale;};
	void mulZ(double scale) {this->data[2] *= scale;};
	
	void addVec3d(STVec3d* v2);
	void subVec3d(STVec3d* v2);
	void mulScalar(double scale);
	STVec3d* sum(STVec3d* v2);
	STVec3d* diff(STVec3d* v2);
	double dotProduct(STVec3d* v2);
	STVec3d* crossProduct(STVec3d* v2);
	double length() {return sqrt(this->dotProduct(this));};
	float distance(STVec3d* v2);
};

class STVec4d
{
private:
	std::vector<double> data;
	
public:
	STVec4d(double x, double y, double z, double w);
	STVec4d() : STVec4d(0.0, 0.0, 0.0, 0.0) {};
	
	std::vector<double> getData() {return this->data;};
	double* getDataArray() {return this->data.data();};
	
	double getX() {return this->data[0];};
	double getY() {return this->data[1];};
	double getZ() {return this->data[2];};
	double getW() {return this->data[3];};

	void setX(double x) {this->data[0] = x;};
	void setY(double y) {this->data[1] = y;};
	void setZ(double z) {this->data[2] = z;};
	void setW(double w) {this->data[3] = w;};
	
	void addX(double x) {this->data[0] += x;};
	void addY(double y) {this->data[1] += y;};
	void addZ(double z) {this->data[2] += z;};
	void addW(double w) {this->data[3] += w;};
	
	void subX(double x) {this->data[0] -= x;};
	void subY(double y) {this->data[1] -= y;};
	void subZ(double z) {this->data[2] -= z;};
	void subW(double w) {this->data[3] -= w;};
	
	void mulX(double scale) {this->data[0] *= scale;};
	void mulY(double scale) {this->data[1] *= scale;};
	void mulZ(double scale) {this->data[2] *= scale;};
	void mulW(double scale) {this->data[3] *= scale;};
	
	void addVec4d(STVec4d* v2);
	void subVec4d(STVec4d* v2);
	void mulScalar(double scale);
	STVec4d* sum(STVec4d* v2);
	STVec4d* diff(STVec4d* v2);
	double dotProduct(STVec4d* v2);
	double length() {return sqrt(this->dotProduct(this));};
	float distance(STVec4d* v2);
};


/*	GLSL Compatibility vectors, six of them. There would be eight, but let's face it, a one-dimensional vector...is just a number.
 */
 
 
class STVec2i
{
private:
	std::vector<int> data;

public:
	STVec2i(int x, int y);
	STVec2i() : STVec2i(0, 0) {};
	
	std::vector<int> getData() {return this->data;};
	int* getDataArray() {return this->data.data();};
	
	int getX() {return this->data[0];};
	int getY() {return this->data[1];};
	
	void setX(int x) {this->data[0] = x;}; 
	void setY(int y) {this->data[1] = y;};
};

class STVec3i
{
private:
	std::vector<int> data;

public:
	STVec3i(int x, int y, int z);
	STVec3i() : STVec3i(0, 0, 0) {};
	
	std::vector<int> getData() {return this->data;};
	int* getDataArray() {return this->data.data();};
	
	int getX() {return this->data[0];};
	int getY() {return this->data[1];};
	int getZ() {return this->data[2];};
	
	void setX(int x) {this->data[0] = x;}; 
	void setY(int y) {this->data[1] = y;};
	void setZ(int z) {this->data[2] = z;};
};

class STVec4i
{
private:
	std::vector<int> data;

public:
	STVec4i(int x, int y, int z, int w);
	STVec4i() : STVec4i(0, 0, 0, 0) {};
	
	std::vector<int> getData() {return this->data;};
	int* getDataArray() {return this->data.data();};
	
	int getX() {return this->data[0];};
	int getY() {return this->data[1];};
	int getZ() {return this->data[2];};
	int getW() {return this->data[3];};
	
	void setX(int x) {this->data[0] = x;}; 
	void setY(int y) {this->data[1] = y;};
	void setZ(int z) {this->data[2] = z;};
	void setW(int w) {this->data[3] = w;};
};

class STVec2ui
{
private:
	std::vector<unsigned int> data;

public:
	STVec2ui(unsigned int x, unsigned int y);
	STVec2ui() : STVec2ui(0, 0) {};
	
	std::vector<unsigned int> getData() {return this->data;};
	unsigned int* getDataArray() {return this->data.data();};
	
	unsigned int getX() {return this->data[0];};
	unsigned int getY() {return this->data[1];};
	
	void setX(unsigned int x) {this->data[0] = x;}; 
	void setY(unsigned int y) {this->data[1] = y;};
};

class STVec3ui
{
private:
	std::vector<unsigned int> data;

public:
	STVec3ui(unsigned int x, unsigned int y, unsigned int z);
	STVec3ui() : STVec3ui(0, 0, 0) {};
	
	std::vector<unsigned int> getData() {return this->data;};
	unsigned int* getDataArray() {return this->data.data();};
	
	unsigned int getX() {return this->data[0];};
	unsigned int getY() {return this->data[1];};
	unsigned int getZ() {return this->data[2];};
	
	void setX(unsigned int x) {this->data[0] = x;}; 
	void setY(unsigned int y) {this->data[1] = y;};
	void setZ(unsigned int z) {this->data[2] = z;}; 
};

class STVec4ui
{
private:
	std::vector<unsigned int> data;

public:
	STVec4ui(unsigned int x, unsigned int y, unsigned int z, unsigned int w);
	STVec4ui() : STVec4ui(0, 0, 0, 0) {};
	
	std::vector<unsigned int> getData() {return this->data;};
	unsigned int* getDataArray() {return this->data.data();};
	
	unsigned int getX() {return this->data[0];};
	unsigned int getY() {return this->data[1];};
	unsigned int getZ() {return this->data[2];};
	unsigned int getW() {return this->data[3];};
	
	void setX(unsigned int x) {this->data[0] = x;}; 
	void setY(unsigned int y) {this->data[1] = y;};
	void setZ(unsigned int z) {this->data[2] = z;};
	void setW(unsigned int w) {this->data[3] = w;};
};
#endif //__ST_VECTOR_H__
