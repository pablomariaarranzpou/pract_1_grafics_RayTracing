#include <QVector>
#include <QVector3D>

#include "Mesh.hh"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
    this->makeTriangles();
}

Mesh::Mesh(const QString &fileName, float data): Object(data)
{
    nom = fileName;
    load(fileName);
    this->makeTriangles();
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();

}

void Mesh::makeTriangles() {

    for (int i = 0; i < cares.size(); i++){

        vec4 p1 = vertexs[cares[i].idxVertices[0]];
        vec4 p2 = vertexs[cares[i].idxVertices[1]];
        vec4 p3 = vertexs[cares[i].idxVertices[2]];

        vec3 p1_ = vec3(p1[0],p1[1],p1[2]);
        vec3 p2_ = vec3(p2[0],p2[1],p2[2]);
        vec3 p3_ = vec3(p3[0],p3[1],p3[2]);
        Triangle triangle(p1_, p2_, p3_, data);
        triangulos.push_back(triangle);
        }

}


bool Mesh::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {

    bool hit = false;
    float closest_t = tmax;
    // Recorremos todos los triangulos de la escena.
    for (const auto& triangle : triangulos) {
        HitInfo temp_info;
        // Verificamos si el objeto es intersectado por el rayo
        if (triangle.hit(raig, tmin, closest_t, temp_info)) {
            hit = true;
            closest_t = temp_info.t;
            info = temp_info;
        }
     }

    return hit;

}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    for (const auto& triangle : triangulos) {
        ((Triangle)triangle).aplicaTG(t);
    }
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*face);
                    }
                }
            }
            this->makeTriangles();
            file.close();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



