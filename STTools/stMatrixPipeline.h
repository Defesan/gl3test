#ifndef __ST_MATRIX_PIPELINE_H__
#define __ST_MATRIX_PIPELINE_H__

#include "stMatrixStack.h"

class STMatrixPipeline
{
private:
	STMatrixStack* modelView;
	STMatrixStack* projection;
public:
	STMatrixPipeline(STMatrixStack* modelView, STMatrixStack* projection);
	void setModelViewStack(STMatrixStack* modelView) {this->modelView = modelView;};
	void setProjectionStack(STMatrixStack* projection) {this->projection = projection;};
	STMatrix44f* getModelViewMatrix() {return this->modelView->getMatrix();};
	STMatrix44f* getProjectionMatrix() {return this->projection->getMatrix();};
	STMatrix44f* getMVPMatrix() {return this->modelView->getMatrix()->mul(this->projection->getMatrix());}; 
};


#endif //__ST_MATRIX_PIPELINE_H__
