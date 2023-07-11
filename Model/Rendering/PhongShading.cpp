#include "PhongShading.h"

vec3 PhongShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights)
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    vec3 ka = info.mat_ptr->Ka;
    vec3 kd = info.mat_ptr->Kd;
    vec3 ks = info.mat_ptr->Ks;
    float shininess = info.mat_ptr->shininess;

    vec3 p = info.p;
    vec3 normal = normalize(info.normal);

    color += ka * globalLight;

    // Iterate over all lights in the scene
    for (auto light : lights) {
        vec3 Ia = light->getIa();
        vec3 Id = light->getId();
        vec3 Is = light->getIs();
        color += Ia * ka;
        vec3 L = normalize(light->vectorL(p));
        vec3 N = normal;
        vec3 R = reflect(-L, N);

        float attenuation = light->attenuation(p);


        if (dot(L, N) > 0.0f) {
            vec3 diffuse = kd * Id * dot(L, N);
            vec3 specular = ks * Is * pow(dot(N, R), shininess);
            color += (specular + diffuse)*(attenuation);
        }
    }
    color += ka * globalLight;

    return color;
}
