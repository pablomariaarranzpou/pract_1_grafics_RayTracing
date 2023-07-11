#include "MaterialTextura.h"
#include <iostream>

MaterialTextura::MaterialTextura(): Material()
{

}

void MaterialTextura::read (const QJsonObject &json)
{
    Material::read(json);
    succes = false;
    if (json.contains("textureFile") && json["textureFile"].isString()) {
        succes = image.load(json["textureFile"].toString());

}
    if(!this->succes) std::cout<< "no existeix la imatge" << endl;
}

vec3 MaterialTextura::getDiffuse(vec2 point) const{
    if (this->succes) {
        QColor c(image.pixel((point.x)*image.width(),(point.y)*image.height()));
        return vec3(c.redF(), c.greenF(), c.blueF());
    }
}

vec3 MaterialTextura::getAttenuation(const Ray& r_in, const HitInfo& rec) const  {
    return Kd;
}

bool MaterialTextura::getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const  {
    return false;
}
bool MaterialTextura::getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec,  std::vector<Ray>& r_out) const  {
    return false;
}

MaterialTextura::~MaterialTextura(){

}
