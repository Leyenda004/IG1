#pragma once
#include "Entity.h"
class CompoundEntity :
    public Abs_Entity
{
protected:
    std::vector<Abs_Entity*> gObjects;
public:
    CompoundEntity() {};
    ~CompoundEntity();
    void addEntity(Abs_Entity* ae); //Añadir entidad al compound

    //Metodos sobreescritos
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
    void load() override;
    void unload() override;
    //render, update, load y unload
};

