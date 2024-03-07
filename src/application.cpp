#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
    cursor.setup();
    drawingTool.setup();
    renderer.setup();
    imageExpImp.setup();
    selectionMode = false;
}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
    drawingTool.draw();
    renderer.draw(drawingTool.getPrimitiveCreationData());
    imageExpImp.draw();
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

    //exporter/importer
    switch (key)
    {
       case 'i':
           imageExpImp.gui_image = !imageExpImp.gui_image;
               break;
       case 's':
           selectionMode = true;
           break;
    }
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y); 
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
    }

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y);

 if (imageExpImp.is_mouse_button_pressed) {
     imageExpImp.mouse_current_x = x;
     imageExpImp.mouse_current_y = y;
 }

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){

    cursor.set_position(x,y);
    if(selectionMode)
    {   
        renderer.SelectChecker(x,y);

    }
    else { 
        renderer.setMousePressStatus(true);
    renderer.setMousePosition(x, y);
    renderer.setMouseClickPosition(x, y);
    imageExpImp.mouse_press_y= y;

    }
 
    

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
    cursor.set_position(x,y);
    renderer.setMousePressStatus(false);
    renderer.setMousePosition(x, y);
    if (imageExpImp.is_mouse_button_pressed) {
      imageExpImp.mouse_current_x = x;
      imageExpImp.mouse_current_y = y;
      imageExpImp.export_image();
      imageExpImp.is_mouse_button_pressed = false;
  }
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
