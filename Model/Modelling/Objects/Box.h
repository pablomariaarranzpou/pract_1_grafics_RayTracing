
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.h"

class Box: public Object  {
public:
    Box();

    Box(vec3 minP, vec3 maxP, float data);
    //Crea una Box donde el punto minimo estara en (0,0,0) y el punto maximo en (1,1,1)
    Box(float data);

    virtual ~Box() {}
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;


    vec3  getMinPoint() { return minPoint;};
    vec3 getMaxPoint() { return maxPoint;};

private:
    // Punto minimo de la caja
    vec3 minPoint;
    // Punto maximo de la caja
    vec3 maxPoint;
};





