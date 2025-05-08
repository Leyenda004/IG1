#include "AdvancedTIE.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"
#include "WingAdvancedTIE.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

AdvancedTIE::AdvancedTIE()
{
	// Material del TIE
	mMat = Material({ 0.0f,0.25f,0.41f }); //(0,65,106)

	// Esfera central
	//Radio, paralelos, meridianos
	Sphere* sphere = new Sphere(100.0f);
	//sphere->setColor({ 0.0f,0.25f,0.41f,1.0f });
	sphere->setMaterial(mMat);
	addEntity(sphere);
	
	// Cilindro eje central
	//Altura / Radio inferior / Radio superior
	Cone* coneA = new Cone(300.0f, 20.0f, 20.0f);
	//coneA->setColor({ 0.0f,0.25f,0.41f,1.0f });
	coneA->setMaterial(mMat);
	coneA->setModelMat(rotate(mat4(1.0f), radians(90.0f), vec3(0.0f, 0.0f, 1.0f)));
	coneA->setModelMat(translate(coneA->modelMat(), vec3(0.0f, -5.0f, 0.0f)));
	addEntity(coneA);

	// Torreta disparo
	Cone* coneB = new Cone(100.0f, 25.0f, 25.0f);
	//coneB->setColor({ 0.0f,0.25f,0.41f,1.0f });
	coneB->setMaterial(mMat);
	mat4 trasconeB = translate(coneB->modelMat(), vec3(0.0f, 100.0f, 0.0f));
	mat4 rotconeB = rotate(coneB->modelMat(), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	coneB->setModelMat(coneB->modelMat() * rotconeB * trasconeB);
	addEntity(coneB);

	// Tapa torreta disparo
	//Radio exterior / Radio interior / nRings / nSamples
	Disk* disk = new Disk(27.0f, 0.0f, 20, 20);
	//disk->setColor({ 0.0f,0.25f,0.41f,1.0f });
	disk->setMaterial(mMat);
	mat4 trasDisk = translate(disk->modelMat(), vec3(0.0f, 150.0f, 0.0f));
	mat4 rotDisk = rotate(disk->modelMat(), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	disk->setModelMat(disk->modelMat() * rotDisk * trasDisk);
	addEntity(disk);
	
	// Ala izquierda
	WingAdvancedTIE* wingA = new WingAdvancedTIE(300.0f, "../assets/images/noche.jpg");
	mat4 traswingA = translate(wingA->modelMat(), vec3(-135.0f, 0.0f, 0.0f));
	mat4 rotwingA = rotate(wingA->modelMat(), radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
	wingA->setModelMat(traswingA * rotwingA * wingA->modelMat());
	addEntity(wingA);

	// Ala derecha
	WingAdvancedTIE* wingB = new WingAdvancedTIE(300.0f, "../assets/images/noche.jpg");
	mat4 traswingB = translate(wingB->modelMat(), vec3(135.0f, 0.0f, 0.0f));
	mat4 rotwingB = rotate(wingB->modelMat(), radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	wingB->setModelMat(traswingB * rotwingB * wingB->modelMat());
	addEntity(wingB);

	// Foco
	foco = new SpotLight({ 0, 0, 0 }, 1); 
	foco->setEnabled(true);
	// Componentes
	foco->setAmb({ 0.25f, 0.25f, 0.25f });
	foco->setDiff({ 0.6f, 0.6f, 0.6f });
	foco->setSpec({ 0.0f, 0.2f, 0.0f });
	// Transformaciones
	foco->setDirection({ 0, 0, 1 });
	//foco->setCutoff(10.0f, 30.0f); // Angulo interno y externo
	foco->setAttenuation(0.6f, 0.003f, 0.0f);

	mShader = Shader::get("light");
}

void AdvancedTIE::render(glm::mat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
	foco->upload(*mShader, modelViewMat * mModelMat);
}