#pragma once

#include "Material.hh"

class Transparent:public Material
{
public:
    Transparent();
    Transparent(const vec3& color);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const vec3& t, const float ui, const float o);
    virtual ~Transparent();

    bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& r_out) const;
    virtual vec3 getDiffuse(vec2 uv) const;
};
