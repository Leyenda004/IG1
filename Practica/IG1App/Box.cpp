#include "Box.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Box::Box(GLdouble l) {
	mShader = Shader::get("texture");

	_mTextureOut = new Texture();
	_mTextureOut->load("../assets/images/container.jpg", 255);

	_mTextureInside = new Texture();
	_mTextureInside->load("../assets/images/papelE.png", 255);


	mMesh = Mesh::generateBoxOutlineTexCor(l);
	mMeshTapa = Mesh::generateRectangleTexCor(l, l);
	mMeshFondo = Mesh::generateRectangleTexCor(l, l);

	mat4 rotTapa = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	mat4 rotFondo = rotate(mat4(1.0f), glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));

	mModelMatTapa = rotTapa;
	mModelMatFondo = rotFondo;

	mat4 trasTapa = translate(mat4(1.0f), vec3(0.0f, l/2, 0.0f));
	mat4 trasFondo = translate(mat4(1.0f), vec3(0.0f, -l/2, 0.0f));

	mModelMatTapa = trasTapa * mModelMatTapa;
	mModelMatFondo = trasFondo * mModelMatFondo;
}

void Box::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && mMeshTapa != nullptr && mMeshFondo != nullptr
		&& _mTextureOut != nullptr && _mTextureInside != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mat4 bMat = modelViewMat * mModelMatTapa;
		mat4 cMat = modelViewMat * mModelMatFondo;

		glEnable(GL_CULL_FACE);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		// BACK
		glCullFace(GL_BACK); // 1. Culling
		_mTextureInside->bind(); // 2. Bind
		// 3. Render caja
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();
		// 3. Render tapa
		// mShader->use();
		// mShader->setUniform("Modulate", bMat);
		// upload(bMat);
		// mMeshTapa->render();
		// 3. Render fondo
		//mShader->use();
		//mShader->setUniform("modulate", cMat);
		//upload(cMat);
		//mMeshFondo->render();
		_mTextureInside->unbind(); // 4. Unbind

		// FRONT
		glCullFace(GL_FRONT); // 1. Culling
		_mTextureOut->bind(); // 2. Bind
		// 3. Render caja
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();
		// 3. Render tapa
		// mShader->use();
		// mShader->setUniform("Modulate", bMat);
		// upload(bMat);
		// mMeshTapa->render();
		// 3. Render fondo
		//mShader->use();
		//mShader->setUniform("modulate", cMat);
		//upload(cMat);
		//mMeshFondo->render();
		_mTextureOut->unbind(); // 4. Unbind

		glDisable(GL_CULL_FACE);
	}
}