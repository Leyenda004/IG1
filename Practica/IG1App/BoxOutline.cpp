#include "BoxOutline.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

BoxOutline::BoxOutline(GLdouble length, std::string mTextureOut, std::string mTextureInside) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
	mShader = Shader::get("texture");
	
	_mTextureOut = new Texture();
	_mTextureOut->load(mTextureOut, 255);

	_mTextureInside = new Texture();
	_mTextureInside->load(mTextureInside, 255);
}

void BoxOutline::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && _mTextureOut != nullptr && _mTextureInside != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", aMat);
		upload(aMat);
		
		glEnable(GL_CULL_FACE);

		// Back
		glCullFace(GL_BACK);
		_mTextureInside->bind();
		mMesh->render();
		_mTextureInside->unbind();

		// Front
		glCullFace(GL_FRONT);
		_mTextureOut->bind();
		mMesh->render();
		_mTextureOut->unbind();

		glDisable(GL_CULL_FACE);

	}
}

//RENDER DE SINGLECOLORENTITY
//void BoxOutline::render(const glm::mat4& modelViewMat) const
//{
//	if (mMesh != nullptr) {
//		//glm::mat4 aMat = modelViewMat * mModelMat;
//		//mShader->use();
//		//mShader->setUniform("modelView", aMat);
//		//upload(aMat);
//
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		//mMesh->render();
//	}
//}


