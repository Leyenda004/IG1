#include "Ground.h"
#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Ground::Ground() {
	mMesh = Mesh::generateRectangleTexCor(100,100,4,4);

	mat4 rot = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	setModelMat(rot * mModelMat);
}

//void Ground::render(const glm::mat4& modelViewMat) const
//{
//	if (mMesh != nullptr) {
//		//!!!!!!!!!!!!!!!!!
//		mat4 aMat = modelViewMat * mModelMat;
//		mShader->use();
//		mShader->setUniform("modelView", aMat);
//		mMesh->render();
//	}
//	
//}
