#pragma once
#include "Entity.h"
#include "Material.h"
class EntityWithMaterial :
    public Abs_Entity
{
public:
	EntityWithMaterial(glm::vec3 color = glm::vec3{ 0.0f, 1.0f, 0.0f });
	~EntityWithMaterial() {};
	void setMaterial(const Material& material);
	Material getMaterial() const;
protected:
	Material mMaterial;
};


// Método alterno
 //class EntityWithMaterial :
 //    public Abs_Entity
 //{
 //public:
 //	EntityWithMaterial() { mMaterial->setAmb(colorDefecto); mMaterial->setDiff(colorDefecto); mMaterial->setSpec(colorDefecto); }
 //	EntityWithMaterial(glm::vec3 color) { mMaterial->setAmb(color); mMaterial->setDiff(color); mMaterial->setSpec(color); }
 //	~EntityWithMaterial() { };
 //	void setMaterial(Material* material) {  if (mMaterial != nullptr) delete mMaterial; mMaterial = material; }
 //	Material* getMaterial() const { return mMaterial; }
 //protected:
 //	glm::vec3 colorDefecto = { 0.0f, 1.0f, 0.0f };
 //	Material* mMaterial = Material(colorDefecto);
 //};