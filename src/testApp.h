#pragma once

#include "ofMain.h"
#include <json/json.h>
//#include "raster.h"
#include "cluster.h"
#include "playfield.h"

#define CONF "conf.json"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
    
		Json::Value read_json(string path);
		void write_json(Json::Value root, char* path);
        ofColor getVideoColor(int x, int y);
        void drawPixels();

        int closestCluster(colorHsb c);

		ofVideoPlayer video;
		ofPixels pixels;
        point vSize;
        point vDim;         // dimensions of the video
		float scale = 1;    // scale of the video
		
		int numPixels;
		//Raster vRaster;     // raster that tells which pixels to read
		float rStep, rxOffset, ryOffset;
		PlayField field;
		
		int numClusters;
		Cluster *clusters;
};
