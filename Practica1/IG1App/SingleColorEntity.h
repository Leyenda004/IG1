#pragma once
#include "Entity.h"
class SingleColorEntity :
    public Abs_Entity
{
public:
    glm::dvec4 mColor;

    SingleColorEntity();

    SingleColorEntity(glm::dvec4);

    inline glm::dvec4 color() const { return mColor; }
    inline void setColor(glm::dvec4 color) { mColor = color; }

    void render(const glm::mat4&) const override;
};

