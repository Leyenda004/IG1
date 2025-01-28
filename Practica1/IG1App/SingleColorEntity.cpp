#include "SingleColorEntity.h"

SingleColorEntity::SingleColorEntity(glm::dvec4 color = glm::dvec4(1)/*?*/) {
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mShader->setUniform("color", modelViewMat/*mColor o modelViewMat??*/);
		mShader->use();
		mMesh->render();
	}
}