#include "stUniform.h"

void STUniform::init()
{
	//Always initialize your variables, kids.
	this->location = 0;
	this->count = 0;
	this->transpose = false;
	
	this->vf1 = 0.0f;
	this->vf2 = 0.0f;
	this->vf3 = 0.0f;
	this->vf4 = 0.0f;
	
	this->vi1 = 0;
	this->vi2 = 0;
	this->vi3 = 0;
	this->vi4 = 0;
	
	this->vui1 = 0;
	this->vui2 = 0;
	this->vui3 = 0;
	this->vui4 = 0;
	
	this->v2fv = nullptr;
	this->v3fv = nullptr;
	this->v4fv = nullptr;
	
	this->v2iv = nullptr;
	this->v3iv = nullptr;
	this->v4iv = nullptr;
	
	this->v2uiv = nullptr;
	this->v3uiv = nullptr;
	this->v4uiv = nullptr;
	
	this->v22m = nullptr;
	this->v23m = nullptr;
	this->v24m = nullptr;
	this->v32m = nullptr;
	this->v33m = nullptr;
	this->v34m = nullptr;
	this->v42m = nullptr;
	this->v43m = nullptr;
	this->v44m = nullptr;
}

STUniform::STUniform(std::string name, GLfloat vf1)
{
	this->init();
	this->type = ST_UNIFORM1F;
	this->name = name;
	this->vf1 = vf1;
}

STUniform::STUniform(std::string name, GLfloat vf1, GLfloat vf2)
{
	this->init();
	this->type = ST_UNIFORM2F;
	this->name = name;
	this->vf1 = vf1;
	this->vf2 = vf2;
}

STUniform::STUniform(std::string name, GLfloat vf1, GLfloat vf2, GLfloat vf3)
{
	this->init();
	this->type = ST_UNIFORM3F;
	this->name = name;
	this->vf1 = vf1;
	this->vf2 = vf2;
	this->vf3 = vf3;
}

STUniform::STUniform(std::string name, GLfloat vf1, GLfloat vf2, GLfloat vf3, GLfloat vf4)
{
	this->init();
	this->type = ST_UNIFORM4F;
	this->name = name;
	this->vf1 = vf1;
	this->vf2 = vf2;
	this->vf3 = vf3;
	this->vf4 = vf4;
}

//Int batches
STUniform::STUniform(std::string name, GLint vi1)
{
	this->init();
	this->type = ST_UNIFORM1I;
	this->name = name;
	this->vi1 = vi1;
}

STUniform::STUniform(std::string name, GLint vi1, GLint vi2)
{
	this->init();
	this->type = ST_UNIFORM2I;
	this->name = name;
	this->vi1 = vi1;
	this->vi2 = vi2;
}

STUniform::STUniform(std::string name, GLint vi1, GLint vi2, GLint vi3)
{
	this->init();
	this->type = ST_UNIFORM3I;
	this->name = name;
	this->vi1 = vi1;
	this->vi2 = vi2;
	this->vi3 = vi3;
}

STUniform::STUniform(std::string name, GLint vi1, GLint vi2, GLint vi3, GLint vi4)
{
	this->init();
	this->type = ST_UNIFORM4I;
	this->name = name;
	this->vi1 = vi1;
	this->vi2 = vi2;
	this->vi3 = vi3;
	this->vi4 = vi4;
}


//Unsigned int batches
STUniform::STUniform(std::string name, GLuint vui1)
{
	this->init();
	this->type = ST_UNIFORM1UI;
	this->name = name;
	this->vui1 = vui1;
}

STUniform::STUniform(std::string name, GLuint vui1, GLuint vui2)
{
	this->init();
	this->type = ST_UNIFORM2UI;
	this->name = name;
	this->vui1 = vui1;
	this->vui2 = vui2;
}

STUniform::STUniform(std::string name, GLuint vui1, GLuint vui2, GLuint vui3)
{
	this->init();
	this->type = ST_UNIFORM3UI;
	this->name = name;
	this->vui1 = vui1;
	this->vui2 = vui2;
	this->vui3 = vui3;
}

STUniform::STUniform(std::string name, GLuint vui1, GLuint vui2, GLuint vui3, GLuint vui4)
{
	this->init();
	this->type = ST_UNIFORM4UI;
	this->name = name;
	this->vui1 = vui1;
	this->vui2 = vui2;
	this->vui3 = vui3;
	this->vui4 = vui4;
}


//Float vectors -- these include counts.
STUniform::STUniform(std::string name, GLsizei count, GLfloat vf1, bool vec)
{
	this->init();
	this->type = ST_UNIFORM1FV;
	this->name = name;
	if(count > 1)
	{
		count = 1;
	}
	this->count = count;
	this->vf1 = vf1;
}

STUniform::STUniform(std::string name, GLsizei count, STVec2f* v2fv)
{
	this->init();
	this->type = ST_UNIFORM2FV;
	this->name = name;
	if(count > 2)
	{
		count = 2;
	}
	this->count = count;
	this->v2fv = v2fv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec3f* v3fv)
{
	this->init();
	this->type = ST_UNIFORM3FV;
	this->name = name;
	if(count > 3)
	{
		count = 3;
	}
	this->count = count;
	this->v3fv = v3fv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec4f* v4fv)
{
	this->init();
	this->type = ST_UNIFORM4FV;
	this->name = name;
	if(count > 4)
	{
		count = 5;
	}
	this->count = count;
	this->v4fv = v4fv;
}


//Int vectors
STUniform::STUniform(std::string name, GLsizei count, GLint vi1, bool vec)
{
	this->init();
	this->type = ST_UNIFORM1IV;
	this->name = name;
	if(count > 1)
	{
		count = 1;
	}
	this->count = count;
	this->vi1 = vi1;
}

STUniform::STUniform(std::string name, GLsizei count, STVec2i* v2iv)
{
	this->init();
	this->type = ST_UNIFORM2IV;
	this->name = name;
	if(count > 2)
	{
		count = 2;
	}
	this->count = count;
	this->v2iv = v2iv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec3i* v3iv)
{
	this->init();
	this->type = ST_UNIFORM3IV;
	this->name = name;
	if(count > 3)
	{
		count = 3;
	}
	this->count = count;
	this->v3iv = v3iv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec4i* v4iv)
{
	this->init();
	this->type = ST_UNIFORM4IV;
	this->name = name;
	if(count > 4)
	{
		count = 4;
	}
	this->count = count;
	this->v4iv = v4iv;
}

//Unsigned int vectors
STUniform::STUniform(std::string name, GLsizei count, GLuint vui1, bool vec)
{
	this->init();
	this->type = ST_UNIFORM1UIV;
	this->name = name;
	if(count > 1)
	{
		count = 1;
	}
	this->count = count;
	this->vui1 = vui1;
}

STUniform::STUniform(std::string name, GLsizei count, STVec2ui* v2uiv)
{
	this->init();
	this->type = ST_UNIFORM2UIV;
	this->name = name;
	if(count > 2)
	{
		count = 2;
	}
	this->count = count;
	this->v2uiv = v2uiv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec3ui* v3uiv)
{
	this->init();
	this->type = ST_UNIFORM3UIV;
	this->name = name;
	if(count > 3)
	{
		count = 3;
	}
	this->count = count;
	this->v3uiv = v3uiv;
}

STUniform::STUniform(std::string name, GLsizei count, STVec4ui* v4uiv)
{
	this->init();
	this->type = ST_UNIFORM4UIV;
	this->name = name;
	if(count > 4)
	{
		count = 4;
	}
	this->count = count;
	this->v4uiv = v4uiv;
}

//Matrices
STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix22f* v22m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX2FV;
	this->name = name;
	if(count > 4)
	{
		count = 4;
	}
	this->count = count;
	this->transpose = transpose;
	this->v22m = v22m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix23f* v23m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX2X3FV;
	this->name = name;
	if(count > 6)
	{
		count = 6;
	}
	this->count = count;
	this->transpose = transpose;
	this->v23m = v23m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix24f* v24m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX2X4FV;
	this->name = name;
	if(count > 8)
	{
		count = 8;
	}
	this->count = count;
	this->transpose = transpose;
	this->v24m = v24m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix32f* v32m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX3X2FV;
	this->name = name;
	if(count > 6)
	{
		count = 6;
	}
	this->count = count;
	this->transpose = transpose;
	this->v32m = v32m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix33f* v33m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX3FV;
	this->name = name;
	if(count > 9)
	{
		count = 9;
	}
	this->count = count;
	this->transpose = transpose;
	this->v33m = v33m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix34f* v34m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX3X4FV;
	this->name = name;
	if(count > 12)
	{
		count = 12;
	}
	this->count = count;
	this->transpose = transpose;
	this->v34m = v34m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix42f* v42m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX4X2FV;
	this->name = name;
	if(count > 8)
	{
		count = 8;
	}
	this->count = count;
	this->transpose = transpose;
	this->v42m = v42m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix43f* v43m)
{
	this->init();
	this->type = ST_UNIFORMMATRIX4X3FV;
	this->name = name;
	if(count > 12)
	{
		count = 12;
	}
	this->count = count;
	this->transpose = transpose;
	this->v43m = v43m;
}

STUniform::STUniform(std::string name, GLsizei count, GLboolean transpose, STMatrix44f* v44m, bool mat)
{
	this->init();
	this->type = ST_UNIFORMMATRIX4FV;
	this->name = name;
	if(count > 16)
	{
		count = 16;
	}
	this->count = count;
	this->transpose = transpose;
	this->v44m = v44m;
}


void STUniform::apply(GLint location)
{
	this->location = location;
	switch(this->type)
	{
	case ST_UNIFORM1F:
		glUniform1f(this->location, this->vf1);
		break;	//Yeah, that's the stuff.
	case ST_UNIFORM2F:
		glUniform2f(this->location, this->vf1, this->vf2);
		break;	
	case ST_UNIFORM3F:
		glUniform3f(this->location, this->vf1, this->vf2, this->vf3);
		break;	
	case ST_UNIFORM4F:
		glUniform4f(this->location, this->vf1, this->vf2, this->vf3, this->vf4);
		break;	//Getting tedious yet?
	case ST_UNIFORM1I:
		glUniform1i(this->location, this->vi1);
		break;
	case ST_UNIFORM2I:
		glUniform2i(this->location, this->vi1, this->vi2);
		break;
	case ST_UNIFORM3I:
		glUniform3i(this->location, this->vi1, this->vi2, this->vi3);
		break;
	case ST_UNIFORM4I:
		glUniform4i(this->location, this->vi1, this->vi2, this->vi3, this->vi4);
		break;	//Yeah!
	case ST_UNIFORM1UI:
		glUniform1ui(this->location, this->vui1);
		break;
	case ST_UNIFORM2UI:
		glUniform2ui(this->location, this->vui1, this->vui2);
		break;
	case ST_UNIFORM3UI:
		glUniform3ui(this->location, this->vui1, this->vui2, this->vui3);
		break;
	case ST_UNIFORM4UI:
		glUniform4ui(this->location, this->vui1, this->vui2, this->vui3, this->vui4);
		break;  //MORE!
	case ST_UNIFORM1FV:
		glUniform1fv(this->location, this->count, (const GLfloat*)&this->vf1);
		break;
	case ST_UNIFORM1IV:
		glUniform1iv(this->location, this->count, (const GLint*)&this->vi1);
		break;
	case ST_UNIFORM1UIV:
		glUniform1uiv(this->location, this->count, (const GLuint*)&this->vui1);
		break; //These guys were special.
	case ST_UNIFORM2FV:
		glUniform2fv(this->location, this->count, (const GLfloat*)this->v2fv->getDataArray());
		break;
	case ST_UNIFORM3FV:
		glUniform3fv(this->location, this->count, (const GLfloat*)this->v3fv->getDataArray());
		break;
	case ST_UNIFORM4FV:
		glUniform4fv(this->location, this->count, (const GLfloat*)this->v4fv->getDataArray());
		break;
	case ST_UNIFORM2IV:
		glUniform2iv(this->location, this->count, (const GLint*)this->v2iv->getDataArray());
		break;
	case ST_UNIFORM3IV:
		glUniform3iv(this->location, this->count, (const GLint*)this->v3iv->getDataArray());
		break;
	case ST_UNIFORM4IV:
		glUniform4iv(this->location, this->count, (const GLint*)this->v4iv->getDataArray());
		break;
	case ST_UNIFORM2UIV:
		glUniform2uiv(this->location, this->count, (const GLuint*)this->v2uiv->getDataArray());
		break;
	case ST_UNIFORM3UIV:
		glUniform3uiv(this->location, this->count, (const GLuint*)this->v3uiv->getDataArray());
		break;
	case ST_UNIFORM4UIV:
		glUniform4uiv(this->location, this->count, (const GLuint*)this->v4uiv->getDataArray());
		break;	//I mean, these guys were special, too. No disrespect.
	case ST_UNIFORMMATRIX2FV:
		glUniformMatrix2fv(this->location, this->count, this->transpose, (const GLfloat*)this->v22m->getData());
		break;
	case ST_UNIFORMMATRIX2X3FV:
		glUniformMatrix2x3fv(this->location, this->count, this->transpose, (const GLfloat*)this->v23m->getData());
		break;
	case ST_UNIFORMMATRIX2X4FV:
		glUniformMatrix2x4fv(this->location, this->count, this->transpose, (const GLfloat*)this->v24m->getData());
		break;
	case ST_UNIFORMMATRIX3X2FV:
		glUniformMatrix3x2fv(this->location, this->count, this->transpose, (const GLfloat*)this->v32m->getData());
		break;
	case ST_UNIFORMMATRIX3FV:
		glUniformMatrix3fv(this->location, this->count, this->transpose, (const GLfloat*)this->v33m->getData());
		break;
	case ST_UNIFORMMATRIX3X4FV:
		glUniformMatrix3x4fv(this->location, this->count, this->transpose, (const GLfloat*)this->v34m->getData());
		break;
	case ST_UNIFORMMATRIX4X2FV:
		glUniformMatrix4x2fv(this->location, this->count, this->transpose, (const GLfloat*)this->v42m->getData());
		break;
	case ST_UNIFORMMATRIX4X3FV:
		glUniformMatrix4x3fv(this->location, this->count, this->transpose, (const GLfloat*)this->v43m->getData());
		break;
	case ST_UNIFORMMATRIX4FV:
		glUniformMatrix4fv(this->location, this->count, this->transpose, (const GLfloat*)this->v44m->getData());
		break;	//And that's the last of them. Rather boring function for being such a lynchpin. Probably take a day to get working properly.
	default:
		std::cerr << "Unknown uniform type" << std::endl;
		break;
	}
	//Hey, I think that's the bottom of the rabbithole!

}
