#include "NormalShadow.h"

vec3 NormalShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights ) {
    //Se suma 1 a cada componente para asegurar que los valores esten entre 0 y 1.´
    vec3 color = 0.5f * vec3(info.normal.x+1, info.normal.y+1, info.normal.z+1);
    for (auto light : lights) {
     color *= computeShadow(light, info.p, scene);
    }
    return color;
}
