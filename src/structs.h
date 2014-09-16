#pragma once

#include "ofMain.h"

typedef struct point {
    int x;
    int y;
} point;

// A HSB representation of color, with all parameters in [0, 1[
typedef struct colorHsb {
    float h;
    float s;
    float b;
} colorHsb;

ofColor colorFromHsb(colorHsb c);
