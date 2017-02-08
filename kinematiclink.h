#ifndef KINEMATICLINK_H
#define KINEMATICLINK_H


class KinematicLink
{
public:
    KinematicLink(float theta, float d, float a, float alpha) {
        this->theta = theta;
        this->d = d;
        this->a = a;
        this->alpha = alpha;
    }

private:
    float theta;
    float d;
    float a;
    float alpha;
};

#endif // KINEMATICLINK_H
