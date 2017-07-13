#ifndef __GL3TEST_H__
#define __GL3TEST_H__

#include "headers.h"


//Working in OpenGL 3, things are... a little different.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60.0f;
const GLfloat PROJECTION_HEIGHT = 100.0f;
const GLfloat PROJECTION_WIDTH = 100.0f;
const GLfloat PROJECTION_DEPTH = 100.0f;
const int MIN_WIDTH = 50;
const int MIN_HEIGHT = 50;
const GLfloat WINDOW_WIDTH = 1.0f;
const GLfloat WINDOW_HEIGHT = 1.0f;

//UGH!!! Globals!
STFrame* viewFrame;
STFrustum* viewFrustum;
STMatrixStack* modelViewStack;
STMatrixStack* projectionStack;
STMatrixPipeline* pipeline;
STShaderManager* sMan;
std::vector<STPrimitiveBatch*> geometry;
STSphere* sphere;
STTimer* timer;


void bounce();
void resize(int w, int h);
void setup();
void render();
void runShader();
void specialKeyHandler(int key, int x, int y);


#endif //__GL3TEST_H__
