#include "raster.h"
#include <cmath>

Raster::Raster(int w, int h, int numPix) {
    set(w, h, numPix);
}

Raster::~Raster() {
}

void Raster::set(int w, int h, int numPix) {
    int xPix = sqrt(1. * w/h * numPix);
    int yPix = 1. * h/w * xPix;

    this->step = {
        (w-1) / xPix,
        (h-1) / yPix
    };

    this->offset = {
        (w % xPix) / 2,
        (h % yPix) / 2
    };
}
