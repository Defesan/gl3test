#include "stMatrixStack.h"

STMatrixStack::STMatrixStack(int stackDepth)
{
	this->lastError = ST_NO_ERROR;
	this->stackPointer = 0;
	this->stackDepth = stackDepth;

	STMatrix44f* top = new STMatrix44f();
	top->loadIdentity();
	this->matrices.push_back(top);
}

int STMatrixStack::pushMatrix(STMatrix44f* matrix)
{
	if(this->stackPointer < this->stackDepth)
	{
		this->matrices.push_back(matrix);
		this->stackPointer += 1;
	}
	else
	{
		this->lastError = ST_STACK_OVERFLOW;
	}
	return (int)this->lastError;
}

int STMatrixStack::pushMatrix()
{
	if(this->stackPointer < this->stackDepth)
	{
		this->matrices.push_back(this->matrices[stackPointer]->copyMatrix());
		this->stackPointer += 1;
	}
	else
	{
		this->lastError = ST_STACK_OVERFLOW;
	}
	return (int)this->lastError;
}

int STMatrixStack::popMatrix()
{
	if(this->stackPointer > 0)
	{
		this->matrices.pop_back();
		this->stackPointer -= 1;
	}
	else
	{
		this->lastError = ST_STACK_UNDERFLOW;
	}
	return (int)this->lastError;
}

void STMatrixStack::scale(float x, float y, float z)
{
	STMatrix44f* scaleMatrix = new STMatrix44f();
	scaleMatrix->loadScaleMatrix(x,y,z);
	this->mulMatrix(scaleMatrix);
}

void STMatrixStack::translate(float x, float y, float z)
{
	STMatrix44f* translationMatrix = new STMatrix44f();
	translationMatrix->loadTranslationMatrix(x,y,z);
	this->mulMatrix(translationMatrix);
}

void STMatrixStack::rotate(float angle, float x, float y, float z)
{
	STMatrix44f* rotationMatrix = new STMatrix44f();
	rotationMatrix->loadRotationMatrix(angle, x, y, z);
	this->mulMatrix(rotationMatrix);
}
