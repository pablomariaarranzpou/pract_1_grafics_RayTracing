#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H

#include "Plane.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "glm/gtx/constants.hpp"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.h"


class FittedPlane: public Plane
{
public:
      FittedPlane();
    //FittedPlane(float arg);
    FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d);
    virtual ~FittedPlane(){}
    virtual bool hit(Ray &r, float t_min, float t_max, HitInfo &info) const;


    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;


private:
    vec3 normal;
    vec3 point;
    vec2 pmin;
    vec2 pmax;
};

#endif
