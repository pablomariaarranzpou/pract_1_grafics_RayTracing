#include "Scene.hh"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

Scene::Scene(shared_ptr<Object> basePlane){
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
    if(basePlane!= nullptr){
        objects.push_back(basePlane);
    }
}


bool Scene::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const{
    // TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.

    bool hit = false;
    float closest_t = tmax;

    // Recorremos todos los objetos de la escena
    for (const auto& object : objects) {
        HitInfo temp_info;
        // Verificamos si el objeto es intersectado por el rayo
        if (object->hit(raig, tmin, closest_t, temp_info)) {
            hit = true;
            closest_t = temp_info.t;
            info = temp_info;
        }
     }

    return hit;
}


void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::setBasePlane(shared_ptr<FittedPlane> plane){
    this->plane = plane;
}

