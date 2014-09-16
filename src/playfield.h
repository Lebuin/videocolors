#pragma once

#include "ofMain.h"
#include "structs.h"
#include "cluster.h"

class PlayField {
    
    public:
        
        PlayField(
            point pos={0, 0},
            point size={0, 0},
            int numClusters=0,
            Cluster *clusters=NULL,
            float scale=0,
            float updateAlpha=0
        );
        ~PlayField();
        
        void update();
        void drawClustersHsb(int alpha);
        void drawClusters();
        
    private:
        
        float updateValue(float from, float to);
        
        point pos, size;
        int numClusters;
        float scale;
        float updateAlpha;
        
        float *members;
        colorHsb *colors;
        Cluster *clusters;
};
