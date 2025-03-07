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

		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);
		upload(aMat);
		mMesh->render();

		mat4 bMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", bMat);
		bMat = rotate(bMat, radians(180.f), vec3(1.0, 0.0, 0.0));
		upload(bMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		//rotate(mat4(1.0f), radians(90.0f), vec3(1, 0, 0));
		//mMesh->render();
	}
}

void Star3D::update()
{
	if (mMesh != nullptr) {
		mat4 rotY = rotate(mat4(1.0f), radians(5.0f), vec3(0, 1, 0));
		mat4 rotZ = rotate(mat4(1.0f), radians(5.0f), vec3(0, 0, 1));
		mat4 rotYNeg = rotate(mat4(1.0f), radians(5.0f), vec3(0, 1, 0));
		//mat4 rotZNeg = rotate(mat4(1.0f), radians(-10.0f), vec3(0, 0, -1));
		//mat4 rotX = rotate(mat4(1.0f), radians(-10.0f), vec3(1, 0, 0));
		mModelMat = (mModelMat * rotZ);

		//GUARDAR LA ROTACION INICIAL DEL MAT4 PARA VOLVER ATRAS A LA HORA DE APLICAR LA ROTACION EN Z Y DESPUES APLICAR DE NUEVO LA Y

		//mModelMat = (mModelMat * rotYNeg);
		//
		//mModelMat = (mModelMat * rotZ);
		//
		//mModelMat = (mModelMat * rotY);
	}

}
