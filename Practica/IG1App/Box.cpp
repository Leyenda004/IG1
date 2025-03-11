#include "Box.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Opcional
#include <iostream>

using namespace glm;

Box::Box(GLdouble lenght, GLdouble x, GLdouble y, GLdouble z) {
	l = lenght;
	mShader = Shader::get("texture");

	_mTextureOut = new Texture();
	_mTextureOut->load("../assets/images/container.jpg", 255);

	_mTextureInside = new Texture();
	_mTextureInside->load("../assets/images/papelE.png", 255);


	mMesh = Mesh::generateBoxOutlineTexCor(l);
	mMeshTapa = Mesh::generateRectangleTexCor(l/2, l/2);
	mMeshFondo = Mesh::generateRectangleTexCor(l/2, l/2);

	mat4 trasBox = translate(mat4(1.0f), vec3(x, y, z));
	mat4 trasTapa = translate(mat4(1.0f), vec3(x, y + l/2, z));
	mat4 trasFondo = translate(mat4(1.0f), vec3(x, y - l/2, z));

	mat4 rotTapa = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	mat4 rotFondo = rotate(mat4(1.0f), glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));

	mModelMat = trasBox;
	mModelMatTapa = trasTapa * rotTapa;
	//mModelMatTapaDestino = mModelMatTapa;
	mModelMatFondo = trasFondo * rotFondo;
}

void Box::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && mMeshTapa != nullptr && mMeshFondo != nullptr
		&& _mTextureOut != nullptr && _mTextureInside != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mat4 bMat = modelViewMat * mModelMatTapa;
		mat4 cMat = modelViewMat * mModelMatFondo;

		// LOAD
		mMeshTapa->load();
		mMeshFondo->load();

		glEnable(GL_CULL_FACE);
		
		// BACK
		glCullFace(GL_BACK); // 1. Culling
		_mTextureInside->bind(); // 2. Bind
		// 3. Render caja
		mShader->use();
		mShader->setUniform("Modulate", aMat);
		upload(aMat);
		mMesh->render();
		// 3. Render tapa
		 mShader->use();
		 mShader->setUniform("Modulate", bMat);
		 upload(bMat);
		 mMeshTapa->render();
		// 3. Render fondo
		mShader->use();
		mShader->setUniform("Modulate", cMat);
		upload(cMat);
		mMeshFondo->render();
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
		mShader->use();
		mShader->setUniform("Modulate", bMat);
		upload(bMat);
		mMeshTapa->render();
		// 3. Render fondo
		mShader->use();
		mShader->setUniform("Modulate", cMat);
		upload(cMat);
		mMeshFondo->render();
		_mTextureOut->unbind(); // 4. Unbind

		glDisable(GL_CULL_FACE);


		// UNLOAD
		mMeshTapa->unload();
		mMeshFondo->unload();
	}
}

void Box::update()
{
	//if (mModelMatTapa == mModelMatTapaDestino) {
	//	giroFuera = !giroFuera;

	//	mModelMatTapaDestino = mModelMatTapa *
	//	translate(mat4(1.0f), vec3(-l/2, 0, 0)) *
	//	rotate(mat4(1.0f), glm::radians((giroFuera ? 1 : -1) * 90.f), vec3(0.0f, 1.0f, 0.0f)) *
	//	translate(mat4(1.0f), vec3(l/2, 0, 0));

	//	std::cout << "giroFuera: " << giroFuera << std::endl;
	//}

	// Esto asegura que la rotación sea exacta
	assert(giroTotal % velGiro == 0);
	if (c < (giroTotal / velGiro) ) {
		c++;
		std::cout << "c: " << c << std::endl;
	}
	else
	{
		c = 0;
		giroFuera = !giroFuera;
		std::cout << "giroFuera: " << giroFuera << std::endl;
	}

	mat4 trasTapa1 = translate(mat4(1.0f), vec3(-l/2, 0, 0));
	mat4 rotTapa = rotate(mat4(1.0f), glm::radians((giroFuera ? 1 : -1) * (float)velGiro), vec3(0.0f, 1.0f, 0.0f));
	mat4 trasTapa2 = translate(mat4(1.0f), vec3(l/2, 0, 0));
	mModelMatTapa = mModelMatTapa * trasTapa1 * rotTapa * trasTapa2;
}
