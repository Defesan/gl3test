#ifndef __ST_MATRIX_H__
#define __ST_MATRIX_H__

#include "stVector.h"

//Four types of matrices, as classes: Two 3x3 and two 4x4

class STMatrix33f {
private:
	std::vector<float> data;
public:
	STMatrix33f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	STMatrix33f() : STMatrix33f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};	//In case you want to make an empty matrix easily.
	
	void set(int row,int col, float val) {this->data[row + (col * 3)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 3)];};
	
	float* getData() {return this->data.data();};
	
	float determinant();
	
	STMatrix33f* mul(STMatrix33f* m2);
	STVec3f* mulVector(STVec3f* vec);
	
	void loadIdentity();
	void loadRotationMatrix(float angle, float x, float y, float z);
	void loadScaleMatrix(float x, float y, float z) {this->loadIdentity(); this->data[0] = x; this->data[4] = y; this->data[8] = z;};
	
	STMatrix33f* copyMatrix();
};

class STMatrix44f {
private:
	std::vector<float> data;
public:
	STMatrix44f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4);
	STMatrix44f() : STMatrix44f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};	//In case you want to make an empty matrix easily.
	
	void set(int row,int col, float val) {this->data[row + (col * 4)] = val;};	
	void setElement(int index, float val) {this->data[index] = val;};
	float get(int row, int col) {return this->data[row + (col * 4)];};
	float getElement(int index) {return this->data[index];};
	
	float determinant();
	float detIJ(int i, int j);
	
	float* getData() {return this->data.data();};

	STMatrix44f* mul(STMatrix44f* m2);
	STVec4f* mulVector(STVec4f* vec);
	
	void loadIdentity();
	void loadRotationMatrix(float angle, float x, float y, float z);
	void loadTranslationMatrix(float x, float y, float z) {this->loadIdentity(); this->data[12] = x; this->data[13] = y; this->data[14] = z;};
	void loadScaleMatrix(float x, float y, float z) {this->loadIdentity(); this->data[0] = x; this->data[5] = y; this->data[10] = z;};
	void loadPerspectiveMatrix(float fov, float aspect, float zMin, float zMax);
	void loadOrthoMatrix(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	void setColumn(int index, STVec3f* column);
	void setRow(int index, STVec3f* row);
	void print(); //Always handy for debug purposes!
	STMatrix44f* invert();
	STMatrix44f* copyMatrix();
};

class STMatrix33d {
private:
	std::vector<double> data;
public:
	STMatrix33d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
	STMatrix33d() : STMatrix33d(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) {};	//In case you want to make an empty matrix easily.
	
	void set(int row,int col, double val) {this->data[row + (col * 3)] = val;};	
	double get(int row, int col) {return this->data[row + (col * 3)];};
	
	double* getData() {return this->data.data();};
	
	STMatrix33d* mul(STMatrix33d* m2);
	STVec3d* mulVector(STVec3d* vec);
	
	void loadIdentity();
	void loadRotationMatrix(double angle, double x, double y, double z);
	void loadScaleMatrix(double x, double y, double z) {this->loadIdentity(); this->data[0] = x; this->data[4] = y; this->data[8] = z;};
	
	STMatrix33d* copyMatrix();
};

class STMatrix44d {
private:
	std::vector<double> data;
public:
	STMatrix44d(double x1, double y1, double z1, double w1, double x2, double y2, double z2, double w2, double x3, double y3, double z3, double w3, double x4, double y4, double z4, double w4);
	STMatrix44d() : STMatrix44d(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) {};	//In case you want to make an empty matrix easily.
	

	void set(int row,int col, double val) {this->data[row + (col * 4)] = val;};	
	double get(int row, int col) {return this->data[row + (col * 4)];};
	
	double* getData() {return this->data.data();};
	
	STMatrix44d* mul(STMatrix44d* m2);
	STVec4d* mulVector(STVec4d* vec);
	
	void loadIdentity();
	void loadRotationMatrix(double angle, double x, double y, double z);
	void loadTranslationMatrix(double x, double y, double z) {this->loadIdentity(); this->data[12] = x; this->data[13] = y; this->data[14] = z;};
	void loadScaleMatrix(double x, double y, double z) {this->loadIdentity(); this->data[0] = x; this->data[5] = y; this->data[10] = z;};
	void loadPerspectiveMatrix(double fov, double aspect, double zMin, double zMax);
	void loadOrthoMatrix(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
	
	STMatrix44d* copyMatrix();
};

//Now, for uniform support, I need:
//STMatrix22f
//STMatrix23f
//STMatrix24f
//STMatrix32f
//STMatrix34f
//STMatrix42f
//STMatrix43f
//All I can say is thank goodness(sort of) that OpenGL doesn't support doubles at a shader level. On the other hand...dammit!
//Though none of them need too much, since none of them really support any of the major matrix archetypes. They're just there in case...
//I'll probably add multiplication by vectors and matrices, maybe other functions later.

class STMatrix22f {
private:
	std::vector<float> data;
public:
	STMatrix22f(float x1, float y1, float x2, float y2);
	STMatrix22f() : STMatrix22f(0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 2)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 2)];};
	
	float* getData() {return this->data.data();};
	
	float determinant() {return (this->get(0,0) * this->get(1,1)) - (this->get(0,1) * this->get(1,0));};
	
	void loadIdentity();
	STMatrix22f* copyMatrix();
};

class STMatrix23f {
private:
	std::vector<float> data;
public:
	STMatrix23f(float x1, float y1, float z1, float x2, float y2, float z2);
	STMatrix23f() : STMatrix23f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 2)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 2)];};
	
	float* getData() {return this->data.data();};

	STMatrix23f* copyMatrix();
};

class STMatrix24f {
private:
	std::vector<float> data;
public:
	STMatrix24f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2);
	STMatrix24f() : STMatrix24f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 2)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 2)];};
	
	float* getData() {return this->data.data();};

	STMatrix24f* copyMatrix();
};

class STMatrix32f {
private:
	std::vector<float> data;
public:
	STMatrix32f(float x1, float y1, float x2, float y2, float x3, float y3);
	STMatrix32f() : STMatrix32f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 3)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 3)];};
	
	float* getData() {return this->data.data();};

	STMatrix32f* copyMatrix();
};

class STMatrix34f {
private:
	std::vector<float> data;
public:
	STMatrix34f(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3);
	STMatrix34f() : STMatrix34f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 3)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 3)];};
	
	float* getData() {return this->data.data();};

	STMatrix34f* copyMatrix();
};

class STMatrix42f {
private:
	std::vector<float> data;
public:
	STMatrix42f(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	STMatrix42f() : STMatrix42f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 4)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 4)];};
	
	float* getData() {return this->data.data();};
	
	STMatrix42f* copyMatrix();
};

class STMatrix43f {
private:
	std::vector<float> data;
public:
	STMatrix43f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
	STMatrix43f() : STMatrix43f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {};
	
	void set(int row,int col, double val) {this->data[row + (col * 4)] = val;};	
	float get(int row, int col) {return this->data[row + (col * 4)];};
	
	float* getData() {return this->data.data();};
	
	STMatrix43f* copyMatrix();
};

#endif //__ST_MATRIX_H__
