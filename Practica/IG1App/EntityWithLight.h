#pragma once
#include "Entity.h"
#include "Light.h"
class EntityWithLight : public Abs_Entity
{
public:
	EntityWithLight(SpotLight* light);
	virtual ~EntityWithLight() {}
	
	virtual void render(const glm::mat4& modelViewMat) const override {}
	virtual void update() override;
	Light* getLight() const { return mLight; }
	
	void setLight(SpotLight* light) { mLight = light; }

protected:
	SpotLight* mLight; 
};

