#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
    cursor.setup();
    drawingTool.setup();
    renderer.setup();
}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
    drawingTool.draw();
    renderer.draw(drawingTool.getPrimitiveCreationData());
}

void Application::exit()
{
    drawingTool.exit();
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
    renderer.setMousePosition(x, y);
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y);
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
    cursor.set_position(x,y);

    renderer.setMousePressStatus(true);
    renderer.setMousePosition(x, y);
    renderer.setMouseClickPosition(x, y);
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
    cursor.set_position(x,y);
    renderer.setMousePressStatus(false);
    renderer.setMousePosition(x, y);
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y);
}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y){
    renderer.setMousePosition(x, y);
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
