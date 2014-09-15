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
    for(int i=0; i<numClusters; i++) {
        dist = clusters[i].colorDist(c);
        if(dist < minDist) {
            minDist = dist;
            mini = i;
        }
    }
    return mini;
}

//--------------------------------------------------------------
void testApp::setup(){
    
    // Load config
    Json::Value config = read_json(CONF);
    
    
    // Get color config values
    numClusters = config["numClusters"].asInt();
    
    // Allocate clusters
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
    int maxWidth = config["maxWidth"].asInt();
    int totalWidth = video.getWidth() + video.getHeight();
    if(totalWidth > maxWidth) {
        scale = 1. * maxWidth / totalWidth;
    }
    
    vDim = {
        scale * video.getWidth(),
        scale * video.getHeight()
    };
    
    
    vRaster = Raster(vDim.x, vDim.y, config["numPix"].asInt());
    
    
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
        for(int i=vRaster.offset.x; i < vDim.x; i += vRaster.step.x) {
            for(int j=vRaster.offset.y; j < vDim.y; j += vRaster.step.y) {
                pixels.getColor(i, j).getHsb(h, s, b);
                colorHsb c = {h/256, s/256, b/256};
                
                index = closestCluster(c);
                clusters[index].pullColor(c);
            }
        }
        
        for(int i=0; i<numClusters; i++) {
            clusters[i].updateColor();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    ofSetColor(255, 255, 255);
    video.draw(0, 0, vDim.x, vDim.y);
    ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps", 15, 10);

    // Draw the pixels that will be used for clustering, to get an idea
    ofSetColor(255, 255, 255, 20);
    ofColor c;
    for(int i=vRaster.offset.x; i < vDim.x; i += vRaster.step.x) {
        for(int j=vRaster.offset.y; j < vDim.y; j += vRaster.step.y) {
            c = pixels.getColor(i, j);
            ofRect(vDim.x + c.getHue(), vDim.y/2+1 + c.getSaturation(), 1, 1);
            ofRect(vDim.x + c.getHue(), vDim.y/2-1 - (256-c.getBrightness()), 1, 1);
        }
    }
    
    // Draw the cluster positions
    for(int i=0; i<numClusters; i++) {
        ofSetColor(
            ofColor::fromHsb(
                256 * clusters[i].color.h,
                256 * clusters[i].color.s,
                256 * clusters[i].color.b
            ),
            170
        );
        
        ofCircle(vDim.x + 256*clusters[i].color.h, vDim.y/2+1 + 256*clusters[i].color.s, clusters[i].members/50);
        ofCircle(vDim.x + 256*clusters[i].color.h, vDim.y/2-1 - (256-256*clusters[i].color.b), clusters[i].members/50);
    }
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
