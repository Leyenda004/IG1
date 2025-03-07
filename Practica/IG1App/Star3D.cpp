#include "Star3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generateStar3D(re,np,h);
	//mShader = Shader::get("simple");
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {

		//mat4 aMat = modelViewMat * mModelMat;
		//mShader->use();
		//mShader->setUniform("modelView", aMat);
		//upload(aMat);
		//mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//mMesh->render();
		rotate(mat4(1.0f), radians(90.0f), vec3(1, 0, 0));
		mMesh->render();
	}
}

void Star3D::update()
{
	if (mMesh != nullptr) {
		mat4 m1 = rotate(mModelMat, radians(1.0f), vec3(0, 1, 0));
		mModelMat = (mModelMat * m1);
	}

}
