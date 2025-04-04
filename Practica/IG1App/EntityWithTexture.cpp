#include "EntityWithTexture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

EntityWithTexture::EntityWithTexture() {
	mShader = Shader::get("texture");
}

EntityWithTexture::~EntityWithTexture()
{
	delete mTexture;
}

void EntityWithTexture::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr && mTexture != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("Modulate",aMat);
		upload(aMat);
		mTexture->bind();
		mMesh->render();
		mTexture->unbind();
	}
}