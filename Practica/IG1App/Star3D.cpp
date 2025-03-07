#include "Star3D.h"

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generateStar3D(re,np,h);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
	}
}
