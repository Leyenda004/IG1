#include "CompoundEntity.h"

using namespace glm;

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* obj : gObjects) {
		delete obj;	//delete a los objetos del compound
	}
	gObjects.clear(); //Vaciando el vector de objetos del compounds
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae); //Añadimos entidad al vector de objetos
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const
{
	for (Abs_Entity* obj : gObjects) { //render a los objetos del compound a partir de modelViewMat
		mat4 aMat = modelViewMat * mModelMat;
		Shader* normal = Shader::get("normals");
		normal->use();
		obj->render(aMat);
	}
}

void CompoundEntity::update()
{
	for (Abs_Entity* obj : gObjects) //upload a los objetos del compound
		obj->update();
}

void CompoundEntity::load()
{
	for (Abs_Entity* obj : gObjects) //load a los objetos del compound
		obj->load();
}

void CompoundEntity::unload()
{
	for (Abs_Entity* obj : gObjects) //unload a los objetos del compound
		obj->unload();
}
