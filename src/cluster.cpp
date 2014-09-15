#include "cluster.h"

#define PI 3.14159265

Cluster::Cluster(colorHsb c) {
    color.h = c.h;
    color.s = c.s;
    color.b = c.b;
    
    members = 0;
    
    resetPulls();
}

Cluster::~Cluster() {
}

float Cluster::colorDist(colorHsb c) {
    float dHue = .5 - abs(color.h - c.h - .5);
    //dHue = color.h - c.h;
    float dSat = color.s - c.s;
    float dBri = color.b - c.b;
    
    return sqrt(dHue*dHue + dSat*dSat + dBri*dBri);
}

void Cluster::pullColor(colorHsb c) {
    numPulls += 1;
    
    sumHueCos += cos(c.h * 2*PI);
    sumHueSin += sin(c.h * 2*PI);
    sumSat += c.s;
    sumBri += c.b;
}

void Cluster::updateColor() {
    members = numPulls;
    
    // If the cluster is not empty: set the average of the cluster members as the new color
    if(numPulls > 0) {
        color.h = fmod(atan2(sumHueSin, sumHueCos) / (2*PI) + 1, 1);
        color.s = sumSat / numPulls;
        color.b = sumBri / numPulls;
        
        resetPulls();
    }
}

void Cluster::resetPulls() {
    numPulls = 0;
    sumHueCos = 0;
    sumHueSin = 0;
    sumSat = 0;
    sumBri = 0;
}
    
