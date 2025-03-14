#include "Star3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ, std::string mTexturePar)
{
	mMesh = Mesh::generateStar3DTexCor(re,np,h);
	
	// Posición inicial deseada
	mModelMat = translate(mat4(1.0f), vec3(posX, posY, posZ));
	// Guardar eje Y
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

		//Estrella 1
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();

		//Estrella 2
		mat4 bMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", bMat);
		bMat = rotate(bMat, radians(180.f), vec3(1.0, 0.0, 0.0)); //Rotacion aplicada
		upload(bMat);
		mMesh->render();

		_starTexture->unbind();
	}
}

void Star3D::update()
{
	if (mMesh != nullptr) {
		//Guardamos la rotacion en variables y vamos incrementandolos en cada iteracion del update
		//AxeY es la modificacion de la matriz identidad adaptada a la posicion de la estrella para que rote en ejeY a partir de esté.
		mModelMat = rotate(axeY, _rotY += _rotationSpeed, vec3(0,1,0));
		mModelMat = rotate(mModelMat, _rotZ += _rotationSpeed, vec3(0,0,1));
	}

}
