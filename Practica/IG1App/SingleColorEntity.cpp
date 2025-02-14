#include "SingleColorEntity.h"
using namespace glm;

SingleColorEntity::SingleColorEntity(dvec4 color = {0.f, 0.f, 0.f, 1.f}) {
	mColor = color;
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("color", (vec4)mColor);
		upload(aMat);
		mMesh->render();
	}
}