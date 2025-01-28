#include "SingleColorEntity.h"

SingleColorEntity::SingleColorEntity() {
	glm::dvec4 color(0.0f,0.0f,0.0f,1.0f); //R = 0, G = 0, B = 0, A = 1 Blanco por defecto
	mColor = color;
	mShader = Shader::get("simple");
}
// hay que usar esta!!!
SingleColorEntity::SingleColorEntity(glm::dvec4 color /*= glm::dvec4(1)*//*?*/) {
	mColor = color;
	mShader = Shader::get("simple");
}



void SingleColorEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mShader->setUniform("color", modelViewMat/*mColor o modelViewMat??*/);
		mShader->use();
		mMesh->render();
	}
}