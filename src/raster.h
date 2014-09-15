#pragma once

typedef struct point {
    int x;
    int y;
} point;

class Raster {
    public:
        Raster(int w=100, int h=100, int numPix=100);
        ~Raster();

        void set(int w, int h, int numPix);

        point offset;
        point step;
};
