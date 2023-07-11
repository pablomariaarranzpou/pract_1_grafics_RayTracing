#include "CelShading.h"

vec3 CelShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 globalLight, vector<shared_ptr<Light>> lights)
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f);


       vec3 ka = info.mat_ptr->Ka;
       vec3 kd = info.mat_ptr->Kd;
       vec3 ks = info.mat_ptr->Ks;
       float shininess = info.mat_ptr->shininess;


       vec3 p = info.p;
       vec3 normal = normalize(info.normal);


       // Iterate over all lights in the sce
       for (const auto& light : lights) {


           vec3 Ia = light->getIa();
           vec3 Id = light->getId();
           vec3 Is = light->getIs();


           vec3 L = normalize(light->vectorL(p));
           vec3 N = normal;
           vec3 V = normalize(lookFrom - p);
           vec3 H = normalize(L + V);


           float attenuation = light->attenuation(p);


           if (dot(L, N) > 0.0f) {
               vec3 diffuse = kd * Id * dot(L, N);
               vec3 specular = ks * Is * pow(dot(N, H), shininess);
               color += (specular + diffuse)*(attenuation);

               float brightness = dot(info.normal, L);
               if (brightness > 0.98f) {
                   color = vec3(1.0f, 1.0f, 1.0f);
               } else if (brightness > 0.5f) {
                   color *= vec3(0.8f, 0.8f, 0.8f);
               } else if (brightness > 0.2f) {
                   color *= vec3(0.6f, 0.6f, 0.6f);
               } else {
                   color *= vec3(0.3f, 0.3f, 0.3f);
               }
           }
           color += Ia * ka;



       }


       color += ka * globalLight;


       return color;
}
