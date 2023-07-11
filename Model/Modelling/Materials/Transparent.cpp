#include "Transparent.h"
Transparent::Transparent(){}

Transparent::Transparent(const vec3& color): Material()
{
    Kd = color; //coeficient difús
    opacity = 0.0f; //0 és totalment transparent
    Kt = vec3(1.0, 1.0, 1.0) - Ks;
    nut = 1.0f;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const vec3& t, const float ui, const float o):
    Material(a, d, s, k, t, ui, o) {
}
Transparent::~Transparent()
{

}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& r_out) const  {

    vec3 normal = rec.normal;
    //float ut = (1.0f / ui); //index de refracció
    //float nut = 1.0f;
    float ui = 1.0f;
    float ind = (ui/nut);
    //Mirem si el raig incident vé de dins o de fora de la superfície
    //En cas d'estar dins, cal girar la normal
    if((dot(normalize((r_in.getDirection())), normal)) > 0.0f){
        ind = nut/ui;
        normal = -normal;
    }

    //Calculem el vector de transmissió t amb la funció refract

    vec3 t = refract(normalize(r_in.getDirection()), normal, ind);
    //Si retorna un valor igual a 0 vol dir que el raig no esta travessant l'objecte
    //(arrel negativa degut a que es tracta d'un medi incident més dens)
    if (length(t)<DBL_EPSILON) {
        //Reflexió Total Interna (angle reflectat surt de la superfície). Només es té en compte el reflectit.
        t = reflect(normalize(r_in.getDirection()), normal);
        r_out = (Ray(rec.p, t));
        color = Ks;
    } else {
        r_out = (Ray(rec.p, t));
        color = Kt;
    }
    return true;
}

vec3 Transparent::getDiffuse(vec2 uv) const {
    return Kd;

}
