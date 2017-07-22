#include "gl3Test.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("GL3 Test 1");
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    glutSpecialFunc(specialKeyHandler);
    
    GLenum error = glewInit();
	if (error != GLEW_OK) 
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(error) << std::endl;
		return 1;
	}
	
	//I begin to see why he does it the other way...
	viewFrame = new STFrame();
	//viewFrustum = new STFrustum(35.0f, float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 1.0f, 100.0f);
	viewFrustum = new STFrustum(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	modelViewStack = new STMatrixStack();
	projectionStack = new STMatrixStack();
	pipeline = new STMatrixPipeline(modelViewStack, projectionStack);
	sMan = new STShaderManager();
	
	setup();

	glutMainLoop();

	return 0;
}

void resize(int w, int h)
{
	if(w < MIN_WIDTH)
	{
		w = MIN_WIDTH;
	}
	if(h < MIN_HEIGHT)
	{
		h = MIN_HEIGHT;
	}
	
	glViewport(0,0,w,h); 
	//viewFrustum->setPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
	viewFrustum->setOrthographic(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	projectionStack->loadMatrix(viewFrustum->getProjectionMatrix());
	pipeline->setProjectionStack(projectionStack);
}

void setup()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	torus = new STTorus(0.0f, 0.0f, 0.0f, 6.0f, 1.5f, 16, 16);
	//sphere->setVelocity(new STVec3f(0.02f, 0.05f, 0.0f));
	//viewFrame->translateLocal(0.0f, 0.0f, 7.0f);
	timer = new STTimer();
	
	torus->render();
}
/*
void bounce()
{
	bool dirty = false;
	
	GLfloat lXPos = sphere->getOriginX() - sphere->getRadius();
	GLfloat rXPos = sphere->getOriginX() + sphere->getRadius();
	GLfloat bYPos = sphere->getOriginY() - sphere->getRadius();
	GLfloat tYPos = sphere->getOriginY() + sphere->getRadius();
	
	GLfloat velX = sphere->getVelX();
	GLfloat velY = sphere->getVelY();
	
	
	if(lXPos < -10.0f || rXPos > 10.0f)
	{
		velX = -velX;
		dirty = true;
	}
	if(bYPos < -10.0f || tYPos > 10.0f)
	{
		velY = -velY;
		dirty = true;
	}
	
	if(dirty)
	{
		STVec3f* velocity = new STVec3f(velX, velY, 0.0f);
		torus->setVelocity(velocity);
	}
}
*/
void render()
{
	GLfloat elapsed = timer->getElapsedSeconds();
	GLfloat frameTime = 1.0f/SCREEN_FPS;
	if(elapsed > frameTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		//viewFrame->rotateLocal(degreesToRadians(0.5f),0.0f, 1.0f, 1.0f);
		//viewFrame->translateLocal(0.0f, 0.0f, 0.001f);
		
		modelViewStack->pushMatrix(viewFrame->getMatrix(false));
			runShader();
			//bounce();
			torus->update();
		modelViewStack->popMatrix();
		
		glutSwapBuffers();
		timer->reset();
	}
	else
	{
		
	}
	glutPostRedisplay();
}

void runShader()
{
	std::vector<STUniform*> uniforms;
	
	//STVec4f* shaderColor = new STVec4f(0.0f, 0.0f, 0.0f, 1.0f);
	//STUniform* colorUniform = new STUniform("vColor", 1, shaderColor);
	//uniforms.push_back(colorUniform);
	
	STMatrix44f* mvMatrix = pipeline->getModelViewMatrix();
	STMatrix44f* pMatrix = pipeline->getProjectionMatrix();
	//STMatrix44f* mvpMatrix = pipeline->getMVPMatrix();
	
	STUniform* mvUniform = new STUniform("mvMatrix", 1, GL_FALSE, mvMatrix, true);
	uniforms.push_back(mvUniform);
	STUniform* pUniform = new STUniform("pMatrix", 1, GL_FALSE, pMatrix, true);
	uniforms.push_back(pUniform);
	
	//STUniform* mvpUniform = new STUniform("mvpMatrix", 1, GL_FALSE, mvpMatrix, true);
	//uniforms.push_back(mvpUniform);
	
	sMan->runShader(sMan->getStockShader(ST_SHADER_LIGHT), uniforms);

}

void specialKeyHandler(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		viewFrame->rotateLocal(degreesToRadians(-5.0f), 1.0f, 0.0f, 0.0f);

	if(key == GLUT_KEY_DOWN)
		viewFrame->rotateLocal(degreesToRadians(5.0f), 1.0f, 0.0f, 0.0f);
        
	if(key == GLUT_KEY_LEFT)
		viewFrame->rotateLocal(degreesToRadians(-5.0f), 0.0f, 1.0f, 0.0f);
        
	if(key == GLUT_KEY_RIGHT)
		viewFrame->rotateLocal(degreesToRadians(5.0f), 0.0f, 1.0f, 0.0f);

	// Refresh the Window
	glutPostRedisplay();

}
