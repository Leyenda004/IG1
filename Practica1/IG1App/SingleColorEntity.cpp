#include "SingleColorEntity.h"
using namespace glm;

SingleColorEntity::SingleColorEntity() {
	glm::dvec4 color(1.0f,1.0f,1.0f,1.0f); //R = 0, G = 0, B = 0, A = 1 Blanco por defecto
	mColor = color;
	mShader = Shader::get("simple");
}
// hay que usar esta!!!
SingleColorEntity::SingleColorEntity(dvec4 color = {0.f, 0.f, 0.f, 1.f}/*?*/) {
	mColor = color;
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("color", (vec4)mColor/*mColor o modelViewMat??*/);
		upload(aMat);
		mMesh->render();
	}
}