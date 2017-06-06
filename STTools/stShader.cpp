#include "stShader.h"

STShaderManager::STShaderManager()
{
	//Initialize the shader manager
	//no need to set the entries in the table to 0, since it's a vector. But we will be loading the stock shaders in here.
	
	//Let's start with a basic identity shader. This should just take a color to render, and pass it through to the fragment shader.
	
	std::string vertexShader = "attribute vec4 vVertex;"	//I have to admit, this format is useful for writing code in strings inside a program...
							   "void main()"
							   "{"
							   "	gl_Position = vVertex;"//But where does vVertex come from?
							   "}";
	
	std::string fragShader = "uniform vec4 vColor;"
							 "void main()"
							 "{"
							 "    gl_FragColor = vColor;"
							 "}";
							 
	GLuint shaderHandle = this->loadShaderPairSrcWithAttributes(vertexShader, fragShader, 1, ST_ATTRIBUTE_VERTEX, "vVertex");
	this->activeShaderPointers.push_back(shaderHandle);
	
}

STShaderManager::~STShaderManager()
{
	std::vector<GLuint>::iterator iter = this->activeShaderPointers.begin();
	for(; iter != this->activeShaderPointers.end(); iter++)
	{
		glDeleteProgram(*iter);
	}
}

void STShaderManager::runShader(GLuint shaderHandle, std::vector<STUniform*> uniforms)
{

	glUseProgram(shaderHandle);
	
	//Now, we have to load the uniforms.
	std::vector<STUniform*>::iterator iter = uniforms.begin();
	for(;iter != uniforms.end(); iter++)
	{
		//First, we need a handle for the uniform. This comes from the compiled shader that's been loaded by glUseProgram, and is identified by name.
		GLint location = glGetUniformLocation(shaderHandle, (*iter)->getName().c_str());
		//Then we use the location to apply the uniform.
		(*iter)->apply(location);
	}
}

bool STShaderManager::loadShaderSrc(std::string shaderSrc, GLuint shaderHandle)
{
	GLchar* stringPtr[1];
	GLint lengthPtr[1];
	GLenum error;
	
	stringPtr[0] = (GLchar*)shaderSrc.c_str();
	lengthPtr[0] = (GLint)shaderSrc.size();
	
	glShaderSource(shaderHandle, 1, (const GLchar**)stringPtr, (const GLint*)lengthPtr);
	
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		return false;
	}
	return true;
}

GLuint STShaderManager::loadShaderPairSrc(std::string vertexShaderSrc, std::string fragShaderSrc)
{
	GLuint programHandle = 0;
	GLuint vertShaderHandle;
	GLuint fragShaderHandle;
	GLint fragTest;
	GLint vertTest;
	GLint progTest;
	
	//Create the shaders' handles
	vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	
	if(!this->loadShaderSrc(vertexShaderSrc, vertShaderHandle) || !this->loadShaderSrc(fragShaderSrc, fragShaderHandle))
	{
		std::cerr << "Shaders failed to load." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;
	}
	
	//Okay, so the code is loaded. Next step:compile it.
	glCompileShader(vertShaderHandle);
	glCompileShader(fragShaderHandle);
	
	//Check to make sure it compiled
	glGetShaderiv(vertShaderHandle, GL_COMPILE_STATUS, &vertTest);
	glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &fragTest);
	
	if(vertTest == GL_FALSE || fragTest == GL_FALSE)
	{
		//Compile failed
		std::cerr << "Shaders failed to compile." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;	
	}
	//Looks like the comile was a success. Time to link.
	
	programHandle = glCreateProgram();
	glAttachShader(programHandle, vertShaderHandle);
	glAttachShader(programHandle, fragShaderHandle);
	glLinkProgram(programHandle);
	
	//One way or another, these are superfluous now.
	glDeleteShader(vertShaderHandle);
	glDeleteShader(fragShaderHandle);
	
	glGetProgramiv(programHandle, GL_LINK_STATUS, &progTest);
	if(progTest == GL_FALSE)
	{
		std::cerr << "Program link failed." << std::endl;
		glDeleteProgram(programHandle);
		return SHADER_ERROR;
	}
	this->activeShaderPointers.push_back(programHandle);
	//All is well.
	return programHandle;
}


GLuint STShaderManager::loadShaderPairWithAttributes(std::string vertexShaderFile, std::string fragShaderFile, ...)
{
	//Whee! Varargs!
	GLuint programHandle = 0;
	GLuint vertShaderHandle;
	GLuint fragShaderHandle;
	GLint fragTest;
	GLint vertTest;
	GLint progTest;
	
	//One of the most self-explanatory lines of code I think I've ever written.
	std::string vertexShaderSrc = fileToString(vertexShaderFile);
	
	std::string fragShaderSrc = fileToString(fragShaderFile);
	
	//Create the shaders' handles
	vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	
	if(!this->loadShaderSrc(vertexShaderSrc, vertShaderHandle) || !this->loadShaderSrc(fragShaderSrc, fragShaderHandle))
	{
		std::cerr << "Shaders failed to load." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;
	}
	
	//Okay, so the code is loaded. Next step:compile it.
	glCompileShader(vertShaderHandle);
	glCompileShader(fragShaderHandle);
	
	//Check to make sure it compiled
	glGetShaderiv(vertShaderHandle, GL_COMPILE_STATUS, &vertTest);
	glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &fragTest);
	
	if(vertTest == GL_FALSE || fragTest == GL_FALSE)
	{
		//Compile failed
		std::cerr << "Shaders failed to compile." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;	
	}
	//Looks like the comile was a success. Time to link.
	
	programHandle = glCreateProgram();
	glAttachShader(programHandle, vertShaderHandle);
	glAttachShader(programHandle, fragShaderHandle);
	
	
	//First, we need a va_list.
	va_list argumentList;
	//Now we start it, passing the list we just created and the point to start from.
	va_start(argumentList, fragShaderFile);
	
	std::string argName;	//Each argument is paired with a name.
	int argCount = va_arg(argumentList, int);	//This looks for the next int after the start point(fragShaderFile)
	for(int i = 0; i < argCount; i++)			//I'll probably be testing this out off-site, as well. I DO NOT like writing so much code without a compile... Gonna take a day to get it working.
	{
		int index = va_arg(argumentList, int);
		argName = va_arg(argumentList, std::string);
		glBindAttribLocation(programHandle, index, argName.c_str());
	}
	va_end(argumentList);	//There...not too painful.

	glLinkProgram(programHandle);
	
	glDeleteShader(vertShaderHandle);
	glDeleteShader(fragShaderHandle);
	
	glGetProgramiv(programHandle, GL_LINK_STATUS, &progTest);
	if(progTest == GL_FALSE)
	{
		std::cerr << "Program link failed." << std::endl;
		glDeleteProgram(programHandle);
		return SHADER_ERROR;	
	}
	//this->activeShaderPointers.push_back(programHandle);
	return programHandle;
}

GLuint STShaderManager::loadShaderPairSrcWithAttributes(std::string vertexShaderSrc, std::string fragShaderSrc, ...)
{
	GLuint programHandle = 0;
	GLuint vertShaderHandle = 0;
	GLuint fragShaderHandle = 0;
	GLint fragTest = 0;
	GLint vertTest = 0;
	GLint progTest = 0;
	
	
	
	//Create the shaders' handles
	vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	
	if(!this->loadShaderSrc(vertexShaderSrc, vertShaderHandle) || !this->loadShaderSrc(fragShaderSrc, fragShaderHandle))
	{
		std::cerr << "Shaders failed to load." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;
	}
	
	//Okay, so the code is loaded. Next step:compile it.
	glCompileShader(vertShaderHandle);
	glCompileShader(fragShaderHandle);
	
	//Check to make sure it compiled
	glGetShaderiv(vertShaderHandle, GL_COMPILE_STATUS, &vertTest);
	glGetShaderiv(fragShaderHandle, GL_COMPILE_STATUS, &fragTest);
	
	if(vertTest == GL_FALSE || fragTest == GL_FALSE)
	{
		//Compile failed
		std::cerr << "Shaders failed to compile." << std::endl;
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		return SHADER_ERROR;	
	}
	//Looks like the comile was a success. Time to link.
	
	programHandle = glCreateProgram();
	glAttachShader(programHandle, vertShaderHandle);
	glAttachShader(programHandle, fragShaderHandle);
	
	
	//First, we need a va_list.
	va_list argumentList;
	//Now we start it, passing the list we just created and the point to start from.
	va_start(argumentList, fragShaderSrc);
	
	char* argName;	//Each argument is paired with a name.
	int argCount = va_arg(argumentList, int);	

	for(int i = 0; i < argCount; i++)			
	{
		int index = va_arg(argumentList, int);
		argName = va_arg(argumentList, char*);
		glBindAttribLocation(programHandle, index, argName);
	}
	va_end(argumentList);	//There...not too painful.

	glLinkProgram(programHandle);
	
	glDeleteShader(vertShaderHandle);
	glDeleteShader(fragShaderHandle);
	
	glGetProgramiv(programHandle, GL_LINK_STATUS, &progTest);
	if(progTest == GL_FALSE)
	{
		std::cerr << "Program link failed." << std::endl;
		glDeleteProgram(programHandle);
		return SHADER_ERROR;
	}
	//this->activeShaderPointers.push_back(programHandle);
	return programHandle;
}
