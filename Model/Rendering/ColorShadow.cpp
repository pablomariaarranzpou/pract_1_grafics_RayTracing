#include "ColorShadow.hh"

vec3 ColorShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights ) {
    // TODO: Fase 2: Canviar per a considerar les ombres en aquest shading
    vec3 color = info.mat_ptr->Kd;
    for (auto light : lights) {
     color *= computeShadow(light, info.p, scene);
    }

    return color;
}
