#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Plane.hh"

class Triangle : public Object{

    public:
        Triangle();
        Triangle(vec3 p_1, vec3 p_2, vec3 p_3, float data);
        Triangle(float data);
        virtual ~Triangle(){}
        void aplicaTG(shared_ptr<TG>) override;
        bool hit(Ray &r, float tmin, float tmax, HitInfo &info) const override;

        virtual void read (const QJsonObject &json) override;
        //virtual void write(QJsonObject &json) const override;
        //virtual void print(int indentation) const override;

    private:
        vec3 p1;
        vec3 p2;
        vec3 p3;
        vec3 normal = cross(p2 - p1, p3- p1);
};


