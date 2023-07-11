#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newBox();
    void newSimulatedScene();
    void newTriangle();
    void newVirtualScene();
    void newDataScene();
    void loadSettings();
    void activaColorShading();
    void activaNormalShader();
    void activaDepthShader();
    void activaBlinn_Phong();
    void activaPhongShader();
    void activaCell_Shading();

signals:
     void settingsChanged();
};

