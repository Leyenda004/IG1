#include "EntityWithTexture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

EntityWithTexture::EntityWithTexture() {
	mShader = Shader::get("texture");
}

void
EntityWithTexture::render() const {
	if (mTexture != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mMesh->render();
		GLuint Name; 
		GLuint Names[3]; 
		glGenTextures(1, &Name); 
		glGenTextures(3, Names);
		glBindTexture(GL_TEXTURE_2D, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}