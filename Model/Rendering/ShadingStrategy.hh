#pragma once

#include "Model/Modelling/Scene.hh"
#include "Model/Modelling/Lights/Light.hh"



class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights) {
        return vec3(0.0, 0.0, 0.0);
    };

    // FASE 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    float computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene){


            vec3 L = normalize(light->vectorL(point));
            Ray shadowRay(point,L);
            float t_min = 0.00000001f;
            float t_max = light->distanceToLight(point);

            HitInfo shadowHit;
            if (scene->hit(shadowRay, t_min, t_max, shadowHit)) {
                return 0.0f;
            }

            return 1.0f;

    }

    virtual ~ShadingStrategy() {};
};
