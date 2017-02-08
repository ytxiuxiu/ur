#ifndef KINEMATICCHAIN_H
#define KINEMATICCHAIN_H

#include <vector>

#include "kinematiclink.h"
#include "maths.h"

using namespace std;


class KinematicChain
{
public:
    KinematicChain() {}
    vector<KinematicLink*> getLinks() { return links; }
    void setLinks(vector<KinematicLink*> links) { this->links = links; }
    void addLink(KinematicLink* link) { links.push_back(link); }
    void update() {
        calculate();
        vector<vec3> positions = getPositions();
        vector<vec3> rotations = getRotations();

        for (unsigned long i = 0; i < links.size(); i++)
        {
            Entity* entity = links[i]->getEntity();
            entity->setPosition(positions[i]);
            entity->setRotation(rotations[i]);
        }
    }
    void calculate() {
        matrics.clear();

        for (unsigned long i = 0; i < links.size(); i++)
        {
            qDebug() << "A" << i;
            qDebug() << links[i]->getTheta() << links[i]->getD() << links[i]->getA() << links[i]->getAlpha();
            Maths::print(links[i]->getMatrix());
//            mat4 one = rotate(mat4(1), radians(links[i]->getRotate()), vec3(0, 0, 1));
            mat4 one = mat4(1);
            for (unsigned long j = 0; j <= i; j++)
            {
                one = one * links[j]->getMatrix();
            }
            qDebug() << "to render";
            Maths::print(one);
            qDebug() << "";
            matrics.push_back(one);
        }
    }
    vector<mat4> getMatrics() { return matrics; }
    vector<vec3> getPositions() {
        vector<vec3> positions;

        for (unsigned long i = 0; i < matrics.size(); i++)
        {
            mat4 matrix = matrics[i];
            positions.push_back(vec3(matrix[1][3], matrix[2][3], matrix[0][3]));
        }
        return positions;
    }
    vector<vec3> getRotations() {
        vector<vec3> rotations;

        for (unsigned long i = 0; i < matrics.size(); i++)
        {
            mat4 matrix = matrics[i];

            float yaw, pitch, roll;

            if (matrix[0][0] == 1.0f || matrix[0][0] == -1.0f)
            {
                yaw = std::atan2f(matrix[0][2], matrix[2][3]);
                pitch = 0;
            }
            else
            {
                yaw = std::atan2(-matrix[2][0], matrix[0][0]);
                pitch = std::asin(matrix[1][0]);
            }
            roll = std::atan2(-matrix[1][2], matrix[1][1]);

            rotations.push_back(vec3(Maths::degree(yaw), Maths::degree(pitch), Maths::degree(roll)));
        }
        return rotations;
    }

private:
    vector<KinematicLink*> links;
    vector<mat4> matrics;
};

#endif // KINEMATICCHAIN_H
