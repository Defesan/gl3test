#ifndef __GL3TEST_H__
#define __GL3TEST_H__

#include "headers.h"


//Working in OpenGL 3, things are... a little different.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const GLfloat PROJECTION_HEIGHT = 100.0f;
const GLfloat PROJECTION_WIDTH = 100.0f;
const GLfloat PROJECTION_DEPTH = 100.0f;
const int MIN_WIDTH = 50;
const int MIN_HEIGHT = 50;

//UGH!!! Globals!
STShaderManager* sMan;
std::vector<STPrimitiveBatch*> geometry;

void resize(int w, int h);
void setup();
void render();


#endif //__GL3TEST_H__
