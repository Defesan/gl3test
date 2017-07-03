#include "gl3Test.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("GL3 Test 1");
    glutReshapeFunc(resize);
    glutDisplayFunc(render);
    
    GLenum error = glewInit();
	if (error != GLEW_OK) 
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(error) << std::endl;
		return 1;
	}
	
	//I begin to see why he does it the other way...
	viewFrame = new STFrame();
	viewFrustum = new STFrustum(35.0f, float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 1.0f, 100.0f);
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
	viewFrustum->setPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
	
	projectionStack->loadMatrix(viewFrustum->getProjectionMatrix());
	pipeline->setProjectionStack(projectionStack);
}

void setup()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	rect = new Rect(0.0f, 0.0f, 0.0f, 0.05f, 0.05f);
	rect->setVelocity(new STVec3f(0.05f, 0.03f, 0.0f));
	timer = new STTimer();
	
	rect->render();
}

void bounce()
{
	bool dirty = false;
	GLfloat lXPos = rect->getOriginX() - (rect->getWidth() / 2);
	GLfloat rXPos = rect->getOriginX() + (rect->getWidth() / 2);
	GLfloat tYPos = rect->getOriginY() + (rect->getHeight() / 2);
	GLfloat bYPos = rect->getOriginY() - (rect->getHeight() / 2);
	
	GLfloat velX = rect->getVelX();
	GLfloat velY = rect->getVelY();
	
	
	if(lXPos < -1.0f || rXPos > 1.0f)
	{
		velX = -velX;
		dirty = true;
	}
	if(bYPos < -1.0f || tYPos > 1.0f)
	{
		velY = -velY;
		dirty = true;
	}
	
	if(dirty)
	{
		STVec3f* velocity = new STVec3f(velX, velY, 0.0f);
		rect->setVelocity(velocity);
	}
}

void render()
{
	GLfloat elapsed = timer->getElapsedSeconds();
	GLfloat frameTime = 1.0f/SCREEN_FPS;
	if(elapsed > frameTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		modelViewStack->pushMatrix(viewFrame->getMatrix(false));
		
		STVec4f* shaderColor = new STVec4f(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<STUniform*> uniforms;
		STUniform* colorUniform = new STUniform("vColor", 1, shaderColor);//Using the ST toolkit, you have to know the details of the shader you're using. I might be able to fix that for the stock shaders.
		uniforms.push_back(colorUniform);
	
		//Finally we get to the part where we use the shader! I might want to streamline this...
		sMan->runShader(sMan->getStockShader(ST_IDENTITY), uniforms);
		bounce();
		rect->update();
		modelViewStack->popMatrix();
		glutSwapBuffers();
		timer->reset();
	}
	else
	{
		
	}
	glutPostRedisplay();
}
