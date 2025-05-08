#pragma once
#include "CompoundEntity.h"

class SpotLight;
class Material;

class AdvancedTIE : public CompoundEntity
{
public:
	AdvancedTIE();
	~AdvancedTIE() { delete mMat; delete foco; }
	void render(const glm::mat4& modelViewMat) const override;
	
	SpotLight* getFoco() const { return foco; }
	private:
		SpotLight* foco = nullptr;
		Material* mMat = nullptr;
};

