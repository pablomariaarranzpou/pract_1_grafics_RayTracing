#include "MaterialTextura.h"
#include <iostream>

MaterialTextura::MaterialTextura(const vec3& color): Material()
{
    Kd = color; //coeficient difús
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}
bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    return false;
}

void MaterialTextura::read (const QJsonObject &json)
{
    Material::read(json);
    if (json.contains("textureFile") && json["textureFile"].isString()) {
        textura = new Texture(json["textureFile"].toString());
    }
}

vec3 MaterialTextura::getDiffuse(vec2 uv) const{
    return textura->getColorPixel(uv);
}

MaterialTextura::~MaterialTextura()
{
}
