#pragma once

#include "Material.hh"
#include "Texture.hh"


class MaterialTextura : public Material
{
public:

   MaterialTextura() {};
   MaterialTextura(const vec3& color);
   MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
   MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);

   void read (const QJsonObject &json) override;
   virtual vec3 getDiffuse(vec2 uv) const override;
   virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
   virtual ~MaterialTextura();

private:
   Texture *textura;
};
