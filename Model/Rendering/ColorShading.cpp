#include "ColorShading.hh"

vec3 ColorShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights) {
    return info.mat_ptr->Kd;
}
