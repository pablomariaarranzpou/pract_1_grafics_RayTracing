#include "FittedPlane.h"

FittedPlane::FittedPlane():Plane(){
}

FittedPlane::FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d) : Plane(normal, pass_point, d){
    this->pmin = pass_min;
    this->pmax = pass_max;
}

bool FittedPlane::hit(Ray &ray, float tmin, float tmax, HitInfo &info) const{

    // Encuentra el punto de intersección entre el rayo y el plano
    if (!Plane::hit(ray, tmin, tmax, info)) {
           return false;
    }
    // Verifica si el punto de intersección está dentro de los límites del mundo virtual
    vec3 intersection_point = info.p;
    if (intersection_point.x < pmin.x || intersection_point.x > pmax.x || intersection_point.z < pmin.y || intersection_point.z > pmax.y) {
               return false;
    }

    //Llena la información del HitInfo
//    info.normal = normal;
//    info.mat_ptr = material.get();
      return true;

}

void FittedPlane::read (const QJsonObject &json)
{
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
            QJsonArray auxVec = json["pmin"].toArray();
            pmin[0] = auxVec[0].toDouble();
            pmin[1] = auxVec[1].toDouble();
        }
        if (json.contains("pmax") && json["pmax"].isArray()) {
            QJsonArray auxVec = json["pmax"].toArray();
            pmax[0] = auxVec[0].toDouble();
            pmax[1] = auxVec[1].toDouble();
        }
}

void FittedPlane::write(QJsonObject &json) const
{
    Plane::write(json);

    QJsonArray auxArray;
    auxArray.append(pmin[0]);auxArray.append(pmin[1]);
    json["pmin"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(pmax[0]);auxArray2.append(pmax[1]);
    json["pmax"] = auxArray2;
}

void FittedPlane::print(int indentation) const
{
    Plane::print(indentation);
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "point:\t" << point[0] << ", "<< point[1] << ", "<< point[2] << "\n";
    QTextStream(stdout) << indent << "normal:\t" << normal[0] << ", "<< normal[1] << ", "<< normal[2] << "\n";
    QTextStream(stdout) << indent << "min point:\t" << pmin[0] << ", "<< pmin[1] << "\n";
    QTextStream(stdout) << indent << "max point:\t" << pmax[0] << ", "<< pmax[1] << "\n";


}

void FittedPlane::aplicaTG(shared_ptr<TG> t) {

      if (dynamic_pointer_cast<TranslateTG>(t)) {
            vec4 c(point, 1.0);
            c = t->getTG() * c;
            point.x = c.x; point.y = c.y; point.z = c.z;
        }

        if (dynamic_pointer_cast<ScaleTG>(t)){
            vec4 cmin(pmin.x, 1.0, pmin.y, 1.0);
            vec4 cmax(pmax.x, 1.0, pmax.y, 1.0);
            cmin = t->getTG() * cmin;
            cmax = t->getTG() * cmax;
            pmin.x = cmin.x; pmin.y = cmin.z;
            pmax.x = cmax.x; pmax.y = cmax.z;
        }
}
