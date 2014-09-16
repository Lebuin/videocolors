#pragma once

#include "ofMain.h"
#include "structs.h"


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
