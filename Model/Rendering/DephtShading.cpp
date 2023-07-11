#include "DephtShading.h"

//dividir entre tres, restar 1,5, sumar 1 por 0.5
vec3 DephtShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights  ){
    float distance = length(info.p - lookFrom);//2.6;
    float min_distance = 0;
    float max_distance = 3;
    float normalized_distance = (distance - min_distance) / (max_distance - min_distance);

    return vec3(normalized_distance, normalized_distance, normalized_distance);
    //return vec3(distance, distance, distance);

}
