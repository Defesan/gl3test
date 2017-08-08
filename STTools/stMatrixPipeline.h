#ifndef __ST_MATRIX_PIPELINE_H__
#define __ST_MATRIX_PIPELINE_H__

#include "stMatrixStack.h"

class STMatrixPipeline
{
private:
	STMatrixStack* modelView;
	STMatrixStack* projection;
public:
	STMatrixPipeline(STMatrixStack* modelView, STMatrixStack* projection) {this->modelView = modelView; this->projection = projection;};
	void setModelViewStack(STMatrixStack* modelView) {this->modelView = modelView;};
	void setProjectionStack(STMatrixStack* projection) {this->projection = projection;};
	STMatrix44f* getModelViewMatrix() {return this->modelView->getMatrix();};
	STMatrix44f* getProjectionMatrix() {return this->projection->getMatrix();};
	STMatrix44f* getMVPMatrix() {return this->projection->getMatrix()->mul(this->modelView->getMatrix());};
	void printMatrices()
	{
		STMatrix44f* modelView = this->getModelViewMatrix();
		STMatrix44f* projection = this->getProjectionMatrix();
		STMatrix44f* mvpMatrix = this->getMVPMatrix();
		
		std::cout << "ModelView matrix: " << std::endl;
		modelView->print();
		std::cout << "Projection matrix: " << std::endl;
		projection->print();
		std::cout << "MVP matrix: " << std::endl;
		mvpMatrix->print();
		
	}; 
};


#endif //__ST_MATRIX_PIPELINE_H__
