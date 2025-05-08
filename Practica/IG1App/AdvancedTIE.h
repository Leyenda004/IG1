#pragma once
#include "CompoundEntity.h"

class SpotLight;

class AdvancedTIE :
    public CompoundEntity
{
public:
	AdvancedTIE();
	~AdvancedTIE() { delete foco; };
	void render(const glm::mat4& modelViewMat) const override;

	SpotLight* getFoco() const { return foco; }
private:
	SpotLight* foco = nullptr;
};

