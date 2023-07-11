#include "RayTracer.hh"
#include "glm/gtc/random.hpp"


RayTracer::RayTracer(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
}


void RayTracer::run() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;


    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {
            vec3 color(0, 0, 0);
            //TODO FASE 2: mostrejar més rajos per pixel segons el valor de "samples"
            for(int i = 0; i < this->setup.get()->getSamples(); i++){

                float u = (float(x)) / float(width);
                u = linearRand(u, u + 0.0011f);
                float v = (float(height -y)) / float(height);
                v = linearRand(v, v + 0.0011f);

                Ray r = camera->getRay(u, v);

                color += this->RayPixel(r,0);

            // TODO FASE 2: Gamma correction
            }

            color/=  this->setup.get()->getSamples();
            color = sqrt(color);
            color *= 255;
            color = clamp(color,vec3(0,0,0),  vec3(255,2555, 255));

            setPixel(x, y, color);
        }
    }
}


void RayTracer::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** FASE 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** FASE 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** FASE 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracer::RayPixel(Ray &ray, int depth) {
    vec3 color = vec3(0);

    vec3 colorTop = setup->getTopBackground();
    vec3 colorBotton = setup->getDownBackground();
    vec3 unit_direction;
    HitInfo info;

    if (depth <= setup->getMAXDEPTH()) { // Evitamos el nùmero de rebotes infinitos
            vec3 ray2 = normalize(ray.getDirection());
            //Calcula la intersecciòn entre un rayo y los objectos de la escena.(permite identificar que objetos se encuentran
            //en la linea de visiòn del observador.).
             scene->hit(ray, 0.0001, 10000, info);

             // Si encuentra alguna intercepciòn, le asigna el color del material

             if(info.p != vec3(0.f, 0.f, 0.f)){
                 //-->Apartado g (Prueba antes de hacerlo por la UI)
                //color = info.mat_ptr->Kd; // coeficiente de reflexión difusa de un material
                 //Toma el tipo de sombreado seleccionado desde la UI
                color =  setup->getShadingStrategy()->shading(scene, info, ray.getOrigin(), setup->getGlobalLight(), setup->getLights());

                 //Calcula el color resultante de los rayos secundarios.
                 Ray r_out;
                 vec3 k = vec3(0.0f, 0.0f, 0.0f); // color de salida del rayo reflectivo

                if (info.mat_ptr->scatter(ray, info, k, r_out)) {
                    //float op = info.mat_ptr->opacity;
                    if (info.mat_ptr->Kt!=vec3(0)){
                        color = (vec3(1.0f)-info.mat_ptr->Kt)*color + k * RayPixel(r_out, depth + 1);
                    }else{
                        color+=k*RayPixel(r_out, depth + 1);
                    }

                }
                //color += info.mat_ptr->Ka * setup->getGlobalLight();

             }else {

                 if ( setup->getBackground() ) {
                     float x= 0.5f*(ray2.y + 1.0f); // obtiene el factor de degradat segons la posició Y del píxel
                     //(1.0f - x)*colorBotton ->>>A medida que x aumenta el colorBotton disminuye.
                     //t*colorTop --->>> A medida que x aumenta, colorTop es mas intens.
                     color =  (1.0f - x)*colorBotton + x*colorTop ; // calcular el color degradat
                 }else{
                     color = vec3(0,0,0);

                 }
             }


    }

    return color;
}


void RayTracer::init() {
    auto s = setup->getShadingStrategy();
    auto s_out = ShadingFactory::getInstance().switchShading(s, setup->getShadows());
    if (s_out!=nullptr) setup->setShadingStrategy(s_out);
}

