#include "Star3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ, std::string mTexturePar)
{
	mMesh = Mesh::generateStar3DTexCor(re,np,h);
	
	mModelMat = translate(mat4(1.0f), vec3(posX, posY, posZ));
	axeY = translate(mat4(1.0f), vec3(posX, posY, posZ));

	mShader = Shader::get("texture");

	_starTexture = new Texture();
	_starTexture->load(mTexturePar, 255);
}

Star3D::~Star3D()
{
	delete _starTexture;
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && _starTexture != nullptr) {

		_starTexture->bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mat4 aMat = modelViewMat * mModelMat;
		// Cambiar orden?? Duda
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();

		mat4 bMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", bMat);
		bMat = rotate(bMat, radians(180.f), vec3(1.0, 0.0, 0.0));
		upload(bMat);
		mMesh->render();
		//rotate(mat4(1.0f), radians(90.0f), vec3(1, 0, 0));
		//mMesh->render();

		
		_starTexture->unbind();
	}
}

void Star3D::update()
{
	if (mMesh != nullptr) {
		mModelMat = rotate(axeY, _rotY += _rotationSpeed, vec3(0,1,0));
		mModelMat = rotate(mModelMat, _rotZ += _rotationSpeed, vec3(0,0,1));
	}

}
