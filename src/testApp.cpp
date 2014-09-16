#include "testApp.h"
#include <cmath>

Json::Value testApp::read_json(string path) {
    ifstream ifs(path.c_str());
    string json(istreambuf_iterator<char>(ifs), (istreambuf_iterator<char>()));

    Json::Value root;
    Json::Reader reader;
    reader.parse(json, root);

    return root;
}

void testApp::write_json(Json::Value root, char* path) {
    Json::StyledWriter writer;
    string json = writer.write(root);
    ofstream ofs(path);
    ofs << json;
    ofs.close();
}

ofColor testApp::getVideoColor(int x, int y) {
    int r = pixels[3 * (y * vDim.x + x)];
    int g = pixels[3 * (y * vDim.x + x) + 1];
    int b = pixels[3 * (y * vDim.x + x) + 2];
    return ofColor(r, g, b);
}

int testApp::closestCluster(colorHsb c) {
    float dist, minDist = 200000000;
    int mini;
    
    // Loop through all the clusters
    for(int i=0; i<numClusters; i++) {
        
        // Calculate the distance from this color to the current cluster color
        dist = clusters[i].colorDist(c);
        
        if(dist < minDist) {
            minDist = dist;
            mini = i;
        }
    }
    return mini;
}

void testApp::drawPixels() {
    // Draw the pixels that were used for clustering
    ofSetColor(255, 255, 255, 20);
    ofColor c;
    for(float i=rxOffset; i < vDim.x; i += rStep) {
        for(float j=ryOffset; j < vDim.y; j += rStep) {
            c = pixels.getColor(i, j);
            ofRect(vDim.x + (c.getHue()/256*vDim.y), c.getSaturation()/256*vDim.y, vDim.y/256., vDim.y/256.);
        }
    }
}

//--------------------------------------------------------------
void testApp::setup(){
    
    // Load config
    Json::Value config = read_json(CONF);
    
    
    // Allocate clusters
    numClusters = config["numClusters"].asInt();
    clusters = (Cluster*) malloc(numClusters * sizeof(Cluster));
    
    // Set default colors
    float val;
    for(int i=0; i<numClusters; i++) {
        clusters[i] = Cluster({(i+.5) / numClusters, .5, .5});
    }
    
    
    // Load video
    const char *video_path = config["video"].asCString();
    video.loadMovie(video_path);
    
    
    // Set dimensions
    vSize = {video.getWidth(), video.getHeight()};
    int maxWidth = config["maxWidth"].asInt();
    int totalWidth = vSize.x + vSize.y;
    if(totalWidth > maxWidth) {
        scale = 1. * maxWidth / totalWidth;
    }
    
    vDim = {
        scale * vSize.x,
        scale * vSize.y
    };
    
    
    // Calculate the step and offset for the pixels that will be read from the video
    numPixels = config["numPixels"].asInt();
    rStep = sqrt(1. * vSize.x * vSize.y / numPixels);
    rxOffset = fmod(vSize.x, rStep) / 2;
    ryOffset = fmod(vSize.y, rStep) / 2;
    
    // Initialize the playfield where the clusters will be drawn
    float updateAlpha = config["updateAlpha"].asFloat();
    field = PlayField(
        {vDim.x, 0},
        {vDim.y, vDim.y},
        numClusters,
        clusters,
        10.*numClusters/numPixels,
        updateAlpha
    );
    
    // Setup screen
    ofBackground(0, 0, 0);
    ofSetWindowShape(vDim.x + vDim.y, vDim.y);
    
    // Start video
    video.play();
}

//--------------------------------------------------------------
void testApp::update() {
    video.update();
    pixels = video.getPixelsRef();
    
    if(video.isFrameNew()) {
        float h, s, b;
        int index;
        
        // Loop through all the pixels in the raster (approx. numPixels)
        for(float i=rxOffset; i < vSize.x; i += rStep) {
            for(float j=ryOffset; j < vSize.y; j += rStep) {
                // Get the color in HSB
                pixels.getColor((int) i, (int) j).getHsb(h, s, b);
                colorHsb c = {h/256, s/256, b/256};
                
                // Find the closest cluster
                index = closestCluster(c);
                
                // Add this color to the cluster pull-list
                clusters[index].pullColor(c);
            }
        }
        
        for(int i=0; i<numClusters; i++) {
            clusters[i].updateColor();
        }
        
        field.update();
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    
    // Draw the video
    ofSetColor(255, 255, 255);
    video.draw(0, 0, vDim.x, vDim.y);
    
    // Write the framerate
    ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps", 15, 10);
    
    // Draw the pixels
    //drawPixels();
    
    // Draw the playfield
    field.drawClustersHsb(170);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
