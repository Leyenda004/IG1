#include "GlassParapet.h"

#include "Texture.h"

GlassParapet::GlassParapet(GLdouble length, std::string mTextureOut)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
	mShader = Shader::get("texture");

	mTexture = new Texture();
	mTexture->load(mTextureOut, 255 / 2);
	setTexture(mTexture);
}

void GlassParapet::render(glm::mat4 const& modelViewMat) const
{
	if (mMesh != nullptr && mTexture != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("texture_alpha", aMat);
		upload(aMat);

		mTexture->bind();
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mMesh->render();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		mTexture->unbind();
	}
}
