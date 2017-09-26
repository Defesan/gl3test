#ifndef __GL3TEST_H__
#define __GL3TEST_H__

#include "headers.h"


//Working in OpenGL 3, things are... a little different.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const GLfloat SCREEN_FPS = 60.0f;
const GLfloat FRAME_TIME = 1.0f/SCREEN_FPS;
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
STTimer* timer;

STCircle* circle;

void resize(int w, int h);
void setup();
void render();
void runShader();
void specialKeyHandler(int key, int x, int y);
void keyboardHandler(unsigned char key, int x, int y);


#endif //__GL3TEST_H__
