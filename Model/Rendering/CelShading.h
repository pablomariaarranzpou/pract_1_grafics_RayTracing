#pragma once
#include "ShadingStrategy.hh"

class CelShading : public ShadingStrategy
{
public:
    CelShading(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights) override;
    ~CelShading(){};
};

