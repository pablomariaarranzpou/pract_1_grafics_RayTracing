#include "Box.h"

Box::Box() {
    minPoint = vec3(0.0, 0.0, 0.0);
    maxPoint = vec3(1.0, 1.0, 1.0);
}

Box::Box(vec3 minP, vec3 maxP, float data) : Object(data) {
    minPoint = minP;
    maxPoint = maxP;
}


Box::Box(float data) : Object(data) {
    minPoint = vec3(0.0, 0.0, 0.0);
    maxPoint = vec3(1.0, 1.0, 1.0);
}

bool Box::hit(Ray& ray, float tmin, float tmax, HitInfo& info) const {
    //Calculamos la direccion del rayo en sentido inverso.
    vec3 invDir = vec3(1.0f) / ray.getDirection();
    // Ecuaciòn parametrica P(t) = origen + t * dirección--- axis-aligned bounding box (AABB)
    vec3 vt0 = (minPoint - ray.getOrigin()) * invDir;
    vec3 vt1 = (maxPoint - ray.getOrigin()) * invDir;
    //Puntos de interseccion mas cercano y mas lejano del rayo con la caja.
    vec3 ptmin = min(vt0, vt1);
    vec3 ptmax = max(vt0, vt1);
    //Menor tiempo de intersección
    float tminbox = glm::max(glm::max(ptmin[0], ptmin[1]), ptmin[2]);
    float tmaxbox = glm::min(glm::min(ptmax[0], ptmax[1]), ptmax[2]);
    //El rayo no intersecta la caja, Si el rayo entra a la caja despues de salir de ella.
    if (tmaxbox < tminbox) {
        return false;
    }
    // El rayo intersecta con la caja
    float t = tminbox;
    if (t < tmin) { // verifica si es la intersecciòn mas cercana hasta ahora.
        t = tmaxbox;
        if (t > tmax) {
            return false;
        }
    }
    //Actualiza el hitInfo
    info.t = t;
    //punto a lo largo de una línea en el espacio.(punto del rayo donde esta la interseccion.
    info.p = ray.pointAtParameter(t);
    //La siguiente comprobacion se realiza con cada una de las componentes y para los dos extremosde la caja. (Para cada cara)
    //Si es menor que 0.001, el punto de interseccion esta cerca del limite minimo de la caja en direcciòn x.
    if (abs(info.p.x - minPoint.x) < 0.001f) {
        info.normal = vec3(-1.0f, 0.0f, 0.0f);
    }
    else if (abs(info.p.x - maxPoint.x) < 0.001f) {
        info.normal = vec3(1.0f, 0.0f, 0.0f); //la superficie de intersección es perpendicular al eje x negativo
    }
    else if (abs(info.p.y - minPoint.y) < 0.001f) {
        info.normal = vec3(0.0f, -1.0f, 0.0f);
    }
    else if (abs(info.p.y - maxPoint.y) < 0.001f) {
        info.normal = vec3(0.0f, 1.0f, 0.0f);
    }
    else if (abs(info.p.z - minPoint.z) < 0.001f) {
        info.normal = vec3(0.0f, 0.0f, -1.0f);
    }
    else if (abs(info.p.z - maxPoint.z) < 0.001f) {
        info.normal = vec3(0.0f, 0.0f, 1.0f);
    }

    info.mat_ptr = material.get();

    return true;
}

//El método comprueba si la transformación es de tipo TranslateTG (una subclase de TG que representa una transformación de traslación),
//y si es así, modifica los puntos mínimo y máximo de la caja (almacenados en las variables minPoint y maxPoint, respectivamente)
//para tener en cuenta la traslación.
void Box::aplicaTG(shared_ptr<TG> t) {

    if (dynamic_pointer_cast<TranslateTG>(t)) {
        vec4 minP(minPoint, 1.0);
        minP = t->getTG() * minP;
        vec4 maxP(maxPoint, 1.0);
        maxP = t->getTG() * maxP;
        minPoint.x = minP.x; minPoint.y = minP.y; minPoint.z = minP.z;
        maxPoint.x = maxP.x; maxPoint.y = maxP.y; maxPoint.z = maxP.z;
    }
    else if (dynamic_pointer_cast<ScaleTG>(t)) {
        vec4 minP(minPoint, 1.0);
        minP = t->getTG() * minP;
        vec4 maxP(maxPoint, 1.0);
        maxP = t->getTG() * maxP;
        minPoint.y = minP.y;
        maxPoint.y = maxP.y;

     }

}

void Box::read(const QJsonObject &json) {
    Object::read(json);

    if (json.contains("minPoint") && json["minPoint"].isArray()) {
        QJsonArray auxVec = json["minPoint"].toArray();
        minPoint[0] = auxVec[0].toDouble();
        minPoint[1] = auxVec[1].toDouble();
        minPoint[2] = auxVec[2].toDouble();
    }
    if (json.contains("maxPoint") && json["maxPoint"].isArray()) {
        QJsonArray auxVec = json["maxPoint"].toArray();
        maxPoint[0] = auxVec[0].toDouble();
        maxPoint[1] = auxVec[1].toDouble();
        maxPoint[2] = auxVec[2].toDouble();
    }
}

void Box::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArrayMin;
    auxArrayMin.append(minPoint[0]); auxArrayMin.append(minPoint[1]); auxArrayMin.append(minPoint[2]);
    json["minPoint"] = auxArrayMin;

    QJsonArray auxArrayMax;
    auxArrayMax.append(maxPoint[0]); auxArrayMax.append(maxPoint[1]); auxArrayMax.append(maxPoint[2]);
    json["maxPoint"] = auxArrayMax;
}

void Box::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "minPoint:\t" << minPoint[0] << ", "<< minPoint[1] << ", "<< minPoint[2] << "\n";
    QTextStream(stdout) << indent << "maxPoint:\t" << maxPoint[0] << ", "<< maxPoint[1] << ", "<< maxPoint[2] << "\n";
}
