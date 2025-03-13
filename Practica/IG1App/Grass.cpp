#include "Grass.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Grass::Grass(GLdouble width, GLdouble height, GLdouble posX, GLdouble posY, GLdouble posZ, std::string mTexturePar) {
	mMesh = Mesh::generateRectangleTexCor(width, height);

	mShader = Shader::get("texture:texture_alpha");
	mTexture = new Texture();
	mTexture->load(mTexturePar, 255);

	mModelMat = rotate(mModelMat, radians(180.f), vec3(1, 0, 0));
	mModelMat = translate(mModelMat, vec3(0, -posY, 0));
	mModelMat = translate(mModelMat, vec3(posX, -posY, posZ));
}

void Grass::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && mTexture != nullptr) {

		mTexture->bind();

		//Hierba 1
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();

		//Hierba 2
		mat4 bMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", bMat);
		bMat = rotate(bMat, radians(45.f), vec3(0.0, 1.0, 0.0));
		upload(bMat);
		mMesh->render();

		//Hierba 3
		mat4 cMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("Modulate", cMat);
		cMat = rotate(cMat, radians(90.f), vec3(0.0, 1.0, 0.0));
		upload(cMat);
		mMesh->render();


		mTexture->unbind();
	}
}
