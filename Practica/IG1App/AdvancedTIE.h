#pragma once
#include "CompoundEntity.h"

#include "Light.h"
#include "Material.h"

class AdvancedTIE : public CompoundEntity
{
public:
	AdvancedTIE();
	~AdvancedTIE() { delete foco; }
	void render(const glm::mat4& modelViewMat) const override;
	
	SpotLight* getFoco() const { return foco; }
	private:
		SpotLight* foco = nullptr;
		Material mMat;
};

