#pragma once

#include "ofMain.h"

// A HSB representation of color, with all parameters in [0, 1[
typedef struct colorHsb {
    float h;
    float s;
    float b;
} colorHsb;


class Cluster {
    
    public:
        
        Cluster(colorHsb c={0, 0, .5});
        ~Cluster();
        
        float colorDist(colorHsb c);
        void pullColor(colorHsb c);
        void updateColor();
        void resetPulls();
        
        colorHsb color;
        int members;
    
    private:
        
        int numPulls;
        float sumHueCos, sumHueSin, sumSat, sumBri;
};
