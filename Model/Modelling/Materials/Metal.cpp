#include "Metal.h"



Metal::Metal(const vec3& color): Material()
{
    Ks = color;
}
Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}
Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}
Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 v= reflect(normalize(rec.p - r_in.getOrigin()), rec.normal);
    vec3 p0 = rec.p + vec3(DBL_EPSILON)*v; // Solucion de surface acne
    float fuzzy=0.02; //0.2   --> En la realidad no es un reflejo perfecto sino que tiene cierta rogosidad
    v=v+fuzzy*Hitable::RandomInSphere();
    r_out =  Ray(p0,v);
    color = Ks;
    return true;
    //return false;
}

vec3 Metal::getSpeculate(vec2 uv) const {
    return Ks;

}
