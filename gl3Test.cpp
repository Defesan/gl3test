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

	sMan = new STShaderManager();
	
	setup();

	glutMainLoop();

	return 0;
}

void resize(int w, int h)
{
	glViewport(0,0,w,h); //Is it just me or is this a little easier than how it was before?
}

void setup()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	rect = new Rect(0.5f, 0.5f, 0.0f, 0.4f, 0.4f);
	rect->setVelocity(new STVec3f(-0.005f, -0.005f, 0.0f));
	rect->render();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	STVec4f* shaderColor = new STVec4f(1.0f, 1.0f, 1.0f, 1.0f);
	std::vector<STUniform*> uniforms;
	STUniform* colorUniform = new STUniform("vColor", 1, shaderColor);//Using the ST toolkit, you have to know the details of the shader you're using. I might be able to fix that for the stock shaders.
	uniforms.push_back(colorUniform);
	
	//Finally we get to the part where we use the shader! I might want to streamline this...
	sMan->runShader(sMan->getStockShader(ST_IDENTITY), uniforms);
	//geometry[0]->draw();
	
	rect->update();
	glutSwapBuffers();
	glutPostRedisplay();
}
