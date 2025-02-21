#include "EntityWithTexture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

EntityWithTexture::EntityWithTexture() {
	mShader = Shader::get("texture");
}

void EntityWithTexture::render(mat4 const& modelViewMat) const
{
	if (mTexture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, 1);
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mMesh->render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}