#pragma once
//#include "SingleColorEntity.h"
#include "EntityWithMaterial.h"
#include "Shader.h"
class ColorMaterialEntity :
    //public SingleColorEntity
    public EntityWithMaterial
{
public:
    ColorMaterialEntity();
    ~ColorMaterialEntity() {};
    void render(glm::mat4 const& modelViewMat) const override;
    static void toggleShowNormals() { mShowNormals = !mShowNormals; }
private:
    inline static bool mShowNormals = false;
    Shader* mShaderAux; // shader adicional para normales
    glm::vec3 colorDefecto;
};

