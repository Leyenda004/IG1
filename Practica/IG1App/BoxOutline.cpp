#include "BoxOutline.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BoxOutline::BoxOutline(GLdouble length) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

//RENDER DE SINGLECOLORENTITY
//void BoxOutline::render(const glm::mat4& modelViewMat) const
//{
//	if (mMesh != nullptr) {
//		glm::mat4 aMat = modelViewMat * mModelMat;
//		mShader->use();
//		mShader->setUniform("modelView", aMat);
//		upload(aMat);
//
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		mMesh->render();
//	}
//}
