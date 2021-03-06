#ifndef __HEADERS_H__
#define __HEADERS_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <typeinfo>

#include "STLinear/stVector.h"
#include "STLinear/stMatrix.h"

#include "STTools/stFrame.h"
#include "STTools/stFrustum.h"
#include "STTools/stPrimitiveBatch.h"
#include "STTools/stTriangleBatch.h"
#include "STTools/stMatrixPipeline.h"
#include "STTools/stMatrixStack.h"
#include "STTools/stShader.h"
#include "STTools/stTimer.h"
#include "STTools/stTriangle.h"
#include "STTools/stUniform.h"
#include "STTools/stUtil.h"

#include "STShape/stRect.h"
#include "STShape/stCircle.h"
#include "STShape/stSphere.h"
#include "STShape/stTorus.h"
#include "STShape/stCylinder.h"

#endif //__HEADERS_H__
