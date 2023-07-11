#include "CelShadow.h"

vec3 CelShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights)
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    vec3 ka = info.mat_ptr->Ka;
    vec3 kd = info.mat_ptr->Kd;
    vec3 ks = info.mat_ptr->Ks;
    float shininess = info.mat_ptr->shininess;

    vec3 p = info.p;
    vec3 normal = normalize(info.normal);

    vec3 avgDiffuseColor = vec3(0.0f, 0.0f, 0.0f);
    for (auto light : lights) {
        vec3 Id = light->getId();
        vec3 L = normalize(light->vectorL(p));
        float attenuation = light->attenuation(p);
        float distance = light->distanceToLight(p);

        avgDiffuseColor += Id * dot(normal, L) / (attenuation * distance);

    }
    avgDiffuseColor /= static_cast<float>(lights.size());

    float shadeLevel = dot(avgDiffuseColor, vec3(1.0f, 1.0f, 1.0f)) / 3.0f;
    if (shadeLevel > 0.9f) {
        shadeLevel = 1.0f;
    } else if (shadeLevel > 0.6f) {
        shadeLevel = 0.8f;
    } else if (shadeLevel > 0.35f) {
        shadeLevel = 0.6f;
    } else {
        shadeLevel = 0.35f;
    }

    vec3 diffuse = kd * shadeLevel;
    vec3 specular = ks * shadeLevel;

    color += ka * globalLight;
    for (auto light : lights) {
        vec3 Ia = light->getIa();
        vec3 Id = light->getId();
        vec3 Is = light->getIs();
        color += Ia * ka;
        vec3 L = normalize(light->vectorL(p));
        vec3 N = normal;
        vec3 V = normalize(lookFrom - p);
        vec3 R = reflect(-L, N);

        if (dot(N, L) > 0.0f) {
            float attenuation = light->attenuation(p);
            float distance = light->distanceToLight(p);

            color += diffuse * Id * dot(N, L) / (attenuation * distance);
            color += specular * Is * pow(dot(R, V), shininess) / (attenuation * distance);
        }

    }

    return color;
}
