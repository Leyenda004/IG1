#include "WingAdvancedTIE.h"

#include "Texture.h"
WingAdvancedTIE::WingAdvancedTIE(GLdouble length, std::string mTextureOut)
{
	mMesh = Mesh::generateRectangleTexCor(length, length/3);
	mShader = Shader::get("texture");

	mTexture = new Texture();
	mTexture->load(mTextureOut, 255 / 3);
	setTexture(mTexture);
}

void WingAdvancedTIE::render(glm::mat4 const& modelViewMat) const
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