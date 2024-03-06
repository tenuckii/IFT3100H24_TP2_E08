#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
   cursor.setup();
   imageExpImp.setup();

}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
    imageExpImp.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key){

}

//--------------------------------------------------------------
void Application::keyReleased(int key){

    //exporter/importer
    switch (key)
    {
       case 'i':
           imageExpImp.gui_image = !imageExpImp.gui_image;
               break;
    }
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){
    cursor.set_position(x,y);

    // pour exporter une partie 
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
    }

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
 cursor.set_position(x,y);

 // pour exporter une partie 
 if (imageExpImp.is_mouse_button_pressed) {
     imageExpImp.mouse_current_x = x;
     imageExpImp.mouse_current_y = y;
 }

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
    cursor.set_position(x,y);


    // pour exporter une partie 
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;

        imageExpImp.mouse_press_x = x;
        imageExpImp.mouse_press_y= y;
    }

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
  cursor.set_position(x,y);


  // pour exporter une partie 
  if (imageExpImp.is_mouse_button_pressed) {
      imageExpImp.mouse_current_x = x;
      imageExpImp.mouse_current_y = y;
      imageExpImp.export_image();
      imageExpImp.is_mouse_button_pressed = false;
  }
  //
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){
  cursor.set_position(x,y);

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
