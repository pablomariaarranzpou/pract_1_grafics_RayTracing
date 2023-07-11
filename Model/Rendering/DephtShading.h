
#include "ShadingStrategy.hh"

class DephtShading: public ShadingStrategy
{
public:
    DephtShading(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights) override;
    ~DephtShading(){};
};

