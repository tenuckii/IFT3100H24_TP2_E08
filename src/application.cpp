#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
    cursor.setup();

}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key){

}

//--------------------------------------------------------------
void Application::keyReleased(int key){

}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){
    cursor.set_position(x,y);
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Application::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo){ 

}
