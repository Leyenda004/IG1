#include "Star3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, std::string mTexturePar)
{
	mMesh = Mesh::generateStar3DTexCor(re,np,h);

	mShader = Shader::get("texture");

	_starTexture = new Texture();
	_starTexture->load(mTexturePar, 255);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && _starTexture != nullptr) {

		_starTexture->bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		mat4 aMat = modelViewMat * mModelMat;
		// Cambiar orden?? Duda
		mShader->use();
		mShader->setUniform("modulate", aMat);
		upload(aMat);
		mMesh->render();

		mat4 bMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modulate", bMat);
		bMat = rotate(bMat, radians(180.f), vec3(1.0, 0.0, 0.0));
		upload(bMat);
		mMesh->render();
		//rotate(mat4(1.0f), radians(90.0f), vec3(1, 0, 0));
		//mMesh->render();

		
		_starTexture->unbind();
	}
}

//APARTADO 27 PENDIENTE

void Star3D::update()
{
	if (mMesh != nullptr) {
		//mat4 modelMatPrev = mModelMat;
		//mat4 rotY = rotate(mModelMaty, radians(5.0f), vec3(0, 1, 0));
		//mat4 rotZ = rotate(mat4(1.0f), radians(5.0f), vec3(0, 0, 1));
		//mat4 rotYNeg = rotate(mat4(1.0f), radians(-5.0f), vec3(0, 1, 0));
		//mat4 rotZNeg = rotate(mat4(1.0f), radians(-5.0f), vec3(0, 0, 1));
		//mat4 rotX = rotate(mat4(1.0f), radians(5.0f), vec3(1, 0, 0));
		//mat4 rotXNeg = rotate(mat4(1.0f), radians(-5.0f), vec3(1, 0, 0));
		//mModelMat = (mModelMat * rotZ * rotY * rotZNeg * rotYNeg);
		//mModelMat = (mModelMat * rotY);

		//mat4 RotY = rotate(mat4(1.0f), radians(1.0f), vec3(0, 1, 0));
		//mat4 RotZ= rotate(mat4(1.0f), radians(1.0f), vec3(0, 0, 1));
		//mat4 RotYNeg = rotate(mat4(1.0f), radians(-1.0f), vec3(0, -1, 0));
		//mat4 RotZNeg = rotate(mat4(1.0f), radians(-1.0f), vec3(0, 0, -1));
		//mat4 RotXNeg2 = rotate(mat4(1.0f), radians(-2.0f), vec3(-1, 0, 0));

		//mModelMat = (mModelMat * RotY * RotZ * RotYNeg * RotZNeg);

		//GUARDAR LA ROTACION INICIAL DEL MAT4 PARA VOLVER ATRAS A LA HORA DE APLICAR LA ROTACION EN Z Y DESPUES APLICAR DE NUEVO LA Y

		//mModelMat = (mModelMat * rotY);
		//
		//mModelMat = (mModelMat * rotZ);
		//
		//mModelMat = (mModelMat * rotY);

		mModelMat = rotate(mat4(1.0f), radians(1.f), vec3(0.f, 1.f, 1.f));
	}

}
