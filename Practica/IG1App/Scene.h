#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include "Texture.h"
#include "Light.h"
#include "Material.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init() = 0;

	void render(Camera const& cam) const;

	// load or unload scene data into the GPU
	void load();
	void unload();

	// EDITABLE
	virtual void update();

	void takePhoto();

	virtual bool handleKey(unsigned int key) { return false; };

	void uploadLights(Camera const& cam) const;
	virtual void addLights();

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gObjectsTranslucid; // Translucid Entities (graphic objects) of the scene

	//EDITABLE

	// std::vector<Texture*> gTextures; // No se usa
	std::vector<Light*> gLights;
	std::vector<Material> gMaterials;
};

#endif //_H_Scene_H_
