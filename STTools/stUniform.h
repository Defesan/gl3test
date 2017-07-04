#ifndef __ST_UNIFORM_H__
#define __ST_UNIFORM_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../STLinear/stMatrix.h"
#include "../STLinear/stVector.h"

enum ST_UNIFORM_TYPE {ST_UNIFORM1F = 0, ST_UNIFORM2F, ST_UNIFORM3F, ST_UNIFORM4F, ST_UNIFORM1I, ST_UNIFORM2I, ST_UNIFORM3I, ST_UNIFORM4I,
                      ST_UNIFORM1UI, ST_UNIFORM2UI, ST_UNIFORM3UI, ST_UNIFORM4UI, ST_UNIFORM1FV, ST_UNIFORM2FV, ST_UNIFORM3FV, ST_UNIFORM4FV,
                      ST_UNIFORM1IV, ST_UNIFORM2IV, ST_UNIFORM3IV, ST_UNIFORM4IV, ST_UNIFORM1UIV, ST_UNIFORM2UIV, ST_UNIFORM3UIV, ST_UNIFORM4UIV,
                      ST_UNIFORMMATRIX2FV, ST_UNIFORMMATRIX3FV, ST_UNIFORMMATRIX4FV, ST_UNIFORMMATRIX2X3FV, ST_UNIFORMMATRIX3X2FV, ST_UNIFORMMATRIX2X4FV,
                      ST_UNIFORMMATRIX3X4FV, ST_UNIFORMMATRIX4X2FV, ST_UNIFORMMATRIX4X3FV};

class STUniform
{
private:
	ST_UNIFORM_TYPE type;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	std::string name;
	
	GLint vi1;
	GLint vi2;
	GLint vi3;
	GLint vi4;
	
	GLuint vui1;
	GLuint vui2;
	GLuint vui3;
	GLuint vui4;
	
	GLfloat vf1;
	GLfloat vf2;
	GLfloat vf3;
	GLfloat vf4;
	
	STVec2f* v2fv;
	STVec3f* v3fv;
	STVec4f* v4fv;
	
	STVec2i* v2iv;
	STVec3i* v3iv;
	STVec4i* v4iv;
	
	STVec2ui* v2uiv;
	STVec3ui* v3uiv;
	STVec4ui* v4uiv;
	
	STMatrix22f* v22m;
	STMatrix23f* v23m;
	STMatrix24f* v24m;
	
	STMatrix32f* v32m;
	STMatrix33f* v33m;
	STMatrix34f* v34m;
	
	STMatrix42f* v42m;
	STMatrix43f* v43m;
	STMatrix44f* v44m;
//Phew! I think that's all the uniforms, minus the one-dimensional vectors -- who the actual f uses *one dimensional vectors*? -- that openGL supports.

	void init();
public:
//now to create the many, many constructors I need.
	//float batches first.
	STUniform(std::string name, GLfloat vf1);
	STUniform(std::string name, GLfloat vf1, GLfloat vf2);
	STUniform(std::string name, GLfloat vf1, GLfloat vf2, GLfloat vf3);
	STUniform(std::string name, GLfloat vf1, GLfloat vf2, GLfloat vf3, GLfloat vf4);
	
	//Int batches
	STUniform(std::string name, GLint vi1);
	STUniform(std::string name, GLint vi1, GLint vi2);
	STUniform(std::string name, GLint vi1, GLint vi2, GLint vi3);
	STUniform(std::string name, GLint vi1, GLint vi2, GLint vi3, GLint vi4);
	
	//Unsigned int batches
	STUniform(std::string name, GLuint vui1);
	STUniform(std::string name, GLuint vui1, GLuint vui2);
	STUniform(std::string name, GLuint vui1, GLuint vui2, GLuint vui3);
	STUniform(std::string name, GLuint vui1, GLuint vui2, GLuint vui3, GLuint vui4);
	
	//Float vectors -- these include counts.
	STUniform(std::string name, GLsizei count, GLfloat vf1, bool vec);	//This one's special. vec should = true, but...honestly, it's a hack for now. You can say false.
	STUniform(std::string name, GLsizei count, STVec2f* v2fv);
	STUniform(std::string name, GLsizei count, STVec3f* v3fv);
	STUniform(std::string name, GLsizei count, STVec4f* v4fv);
	
	//Int vectors
	STUniform(std::string name, GLsizei count, GLint vi1, bool vec);
	STUniform(std::string name, GLsizei count, STVec2i* v2iv);
	STUniform(std::string name, GLsizei count, STVec3i* v3iv);
	STUniform(std::string name, GLsizei count, STVec4i* v4iv);
	
	//Unsigned int vectors
	STUniform(std::string name, GLsizei count, GLuint vui1, bool vec);
	STUniform(std::string name, GLsizei count, STVec2ui* v2uiv);
	STUniform(std::string name, GLsizei count, STVec3ui* v3uiv);
	STUniform(std::string name, GLsizei count, STVec4ui* v4uiv);
	
	//Matrices
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix22f* v22m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix23f* v23m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix24f* v24m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix32f* v32m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix33f* v33m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix34f* v34m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix42f* v42m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix43f* v43m);
	STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix44f* v44m, bool mat);
	
	//Now, I know there are plenty of things I could do to trim that list.
	//Specifically, the lowest-hanging fruit here is to add a base class to stMatrix and stVector, and give each a type enum, then switch on that.
	//In fact, I could trim *eighteen* of those down to *two*. But... Really, this is mostly going to be copy-paste time. I'll do that later, this now.
	
	//But for now, the meat.
	void apply(GLint location);	//If that seems anticlimactic, head over to the .cpp file.
	
	//Also, we need some getters.
	std::string getName() {return this->name;};
};


#endif //__ST_UNIFORM_H__
