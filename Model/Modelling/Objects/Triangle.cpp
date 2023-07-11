#include "Triangle.hh"


Triangle::Triangle() {
    this->p1 = vec3(0,0,0);
    this->p2 = vec3(1,0,0);
    this->p3 = vec3(0.5,1,0);
}

Triangle::Triangle(vec3 p_1, vec3 p_2, vec3 p_3, float data) :Object(data) {
    this->p1 = p_1;
    this->p2 = p_2;
    this->p3 = p_3;
    this->data = data;

}

Triangle::Triangle(float data) {
    this->p1 = vec3(0,0,0);
    this->p2 = vec3(1,0,0);
    this->p3 = vec3(0.5,1,0);
    this->data = data;
}

bool Triangle::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {

    // Dot: Producto Escalar
    // Cross: Producto vectorial

    vec3 A = this->p2 - this->p1;
    vec3 B = this->p3 - this->p1;

    vec3 normal = normalize(cross(A,B));

    // Si es paralelo
    if(dot(raig.getDirection(), normal) == 0){
        return false;
    }

    float d = -normal[0]*this->p1[0] - normal[1]*this->p1[1] - normal[2]*this->p1[2];

    vec3 rp = raig.getOrigin();
    vec3 vp = raig.getDirection();

    // Calculamos la distancia de la intersección del rayo con el plano.

    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;
    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    // Este es el punto de intersección del rayo con el plano.
    vec3 punt = raig.pointAtParameter(temp);

    // HA de estar dentro del varemo minimo y maximo que hayamos configurado
    if (temp > tmax || temp < tmin) {
        return false;
    }

    //Comprobamos que el punto esté dentro del triangulo. Calculamos si el punto está al mismo al lado respecto a todas las aristas.

    float s1 = dot(cross((this->p2 - this->p1), punt - this->p1), normal);
    float s2 = dot(cross((this->p3 - this->p2), punt - this->p2), normal);
    float s3 = dot(cross((this->p1 - this->p3), punt - this->p3), normal);

     // Miramos que los tres puntos sean positivos o negativos y entonces hay intersección
     if((s1>=0 && s2>=0 && s3>=0) || (s1<=0 && s2<=0 && s3<=0)){
         info.t = temp;
         info.p = raig.pointAtParameter(info.t);
         info.mat_ptr = material.get();
         return true;
     } else {
         return false;
     }
}

void Triangle::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        vec4 cA(this->p1, 1.0);
        vec4 cB(this->p2, 1.0);
        vec4 cC(this->p3, 1.0);


        cA = t->getTG() * cA;
        cB = t->getTG() * cB;
        cC = t->getTG() * cC;


        p1.x = cA.x; p1.y = cA.y; p1.z = cA.z;
        p2.x = cB.x; p2.y = cB.y; p2.z = cB.z;
        p3.x = cC.x; p3.y = cC.y; p3.z = cC.z;
    }
}


void Triangle::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("p1") && json["p1"].isArray()) {
            QJsonArray auxVec = json["p1"].toArray();
            p1[0] = auxVec[0].toDouble();
            p1[1] = auxVec[1].toDouble();
            p1[2] = auxVec[2].toDouble();
        }


    if (json.contains("p2") && json["p2"].isArray()) {
            QJsonArray auxVec = json["p2"].toArray();
            p2[0] = auxVec[0].toDouble();
            p2[1] = auxVec[1].toDouble();
            p2[2] = auxVec[2].toDouble();
        }


    if (json.contains("p3") && json["p3"].isArray()) {
            QJsonArray auxVec = json["p3"].toArray();
            p3[0] = auxVec[0].toDouble();
            p3[1] = auxVec[1].toDouble();
            p3[2] = auxVec[2].toDouble();
        }

}


