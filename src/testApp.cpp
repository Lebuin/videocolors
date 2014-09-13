#include "testApp.h"
#include <fstream>

Json::Value testApp::read_json(char* path) {
    ifstream ifs(path);
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


//--------------------------------------------------------------
void testApp::setup(){

    Json::Value config = read_json(CONF);

    string video = config["video"].asString();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

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
