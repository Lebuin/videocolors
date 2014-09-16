#include "playfield.h"

PlayField::PlayField(point pos, point size, int numClusters, Cluster *clusters, float scale, float updateAlpha) {
    this->pos = pos;
    this->size = size;
    this->numClusters = numClusters;
    this->clusters = clusters;
    this->scale = scale;
    this->updateAlpha = updateAlpha;
    
    colors = (colorHsb*) calloc(numClusters, sizeof(colorHsb));
    members = (float*) calloc(numClusters, sizeof(float));
}

PlayField::~PlayField() {
}

float PlayField::updateValue(float from, float to) {
    return to + updateAlpha * (from - to);
}

void PlayField::update() {
    for(int i=0; i<numClusters; i++) {
        if(clusters[i].color.h - colors[i].h > .5) {
            colors[i].h = fmod(updateValue(clusters[i].color.h-1, colors[i].h) + 1, 1);
        } else {
            colors[i].h = updateValue(clusters[i].color.h, colors[i].h);
        }
        
        colors[i].s = updateValue(clusters[i].color.s, colors[i].s);
        colors[i].b = updateValue(clusters[i].color.b, colors[i].b);
        
        members[i] = updateValue(clusters[i].members, members[i]);
    }
}
        

void PlayField::drawClustersHsb(int alpha) {
    for(int i=0; i<numClusters; i++) {
        ofSetColor(colorFromHsb(colors[i]), alpha);
        ofCircle(
            pos.x + colors[i].h * size.x,
            pos.y + colors[i].s * size.y,
            members[i] * scale
        );
    }
}

void PlayField::drawClusters() {
    for(int i=0; i<numClusters; i++) {
        float k = (i+.5) * size.x / numClusters;
        ofSetColor(colorFromHsb(clusters[i].color));
        ofCircle(
            pos.x + k,
            pos.y + k,
            clusters[i].members * scale
        );
    }
}
