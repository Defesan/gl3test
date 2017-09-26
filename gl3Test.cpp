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
    glutKeyboardFunc(keyboardHandler);
    
   	GLenum error = glewInit();
	if (error != GLEW_OK) 
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(error) << std::endl;
		return 1;
	}
	
	//I begin to see why he does it the other way...
	viewFrame = new STFrame();
	viewFrustum = new STFrustum();
	modelViewStack = new STMatrixStack();
	projectionStack = new STMatrixStack();
	pipeline = new STMatrixPipeline(modelViewStack, projectionStack);
	sMan = new STShaderManager();
	timer = new STTimer();
	
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
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	
	circle = new STCircle(0.0f, 0.0f, 0.0f, 3.0f, 24);
	
	runShader();
	circle->render();
}

void render()
{
	GLfloat elapsed = timer->getElapsedSeconds();
	if(elapsed > FRAME_TIME)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		modelViewStack->pushMatrix(viewFrame->getMatrix(false));
			runShader();
			circle->update();
			//Run code here
		modelViewStack->popMatrix();
		glutSwapBuffers();
		timer->reset();
	}
	glutPostRedisplay();
}

void runShader()
{
	std::vector<STUniform*> uniforms;
	
	STMatrix44f* mvMatrix = pipeline->getModelViewMatrix();
	STMatrix44f* pMatrix = pipeline->getProjectionMatrix();
	
	STUniform* mvUniform = new STUniform("mvMatrix", 1, GL_FALSE, mvMatrix, true);
	uniforms.push_back(mvUniform);
	STUniform* pUniform = new STUniform("pMatrix", 1, GL_FALSE, pMatrix, true);
	uniforms.push_back(pUniform);
	
	sMan->runShader(sMan->getStockShader(ST_SHADER_LIGHT), uniforms);

}

void specialKeyHandler(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			viewFrame->rotateWorld(degreesToRadians(-5.0f), 1.0f, 0.0f, 0.0f);
			break;
		case GLUT_KEY_DOWN:
			viewFrame->rotateWorld(degreesToRadians(5.0f), 1.0f, 0.0f, 0.0f);
			break;
		case GLUT_KEY_LEFT:
			viewFrame->rotateWorld(degreesToRadians(-5.0f), 0.0f, 1.0f, 0.0f);
			break;
		case GLUT_KEY_RIGHT:
			viewFrame->rotateWorld(degreesToRadians(5.0f), 0.0f, 1.0f, 0.0f);
			break;
		default:
			break;	
	}

	// Refresh the Window
	glutPostRedisplay();

}

void keyboardHandler(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
			viewFrame->translateLocal(0.0f, 0.0f, -0.05f);
			break;
		case 's':
			viewFrame->translateLocal(0.0f, 0.0f, 0.05f);
			break;
		case 'a':
			viewFrame->translateLocal(-0.05f, 0.0f, 0.0f);
			break;
		case 'd':
			viewFrame->translateLocal(0.05f, 0.0f, 0.0f);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
