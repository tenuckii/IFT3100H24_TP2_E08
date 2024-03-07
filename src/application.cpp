#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
    cursor.setup();

    drawingTool.setup();
    renderer.setup();
    imageExpImp.setup();
    geometrie3D.setup();

}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
    switch (mode)
    {
       case 2:
        drawingTool.draw();
        renderer.draw(drawingTool.getPrimitiveCreationData());
        imageExpImp.draw();
        break;
       case 3:
           geometrie3D.draw();
           break;
    }
    
   
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
       case '2':
           mode = 2;
           drawingTool.showMenu();
           geometrie3D.gui3d_afficher = false;
           break;
       case '3':
           mode = 3;
           drawingTool.hideMenu();
           geometrie3D.gui3d_afficher = !geometrie3D.gui3d_afficher;
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


    // pour exporter une partie 
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;

        imageExpImp.mouse_press_x = x;
        imageExpImp.mouse_press_y= y;
    }

    renderer.setMousePressStatus(true);
    renderer.setMousePosition(x, y);
    renderer.setMouseClickPosition(x, y);
    imageExpImp.mouse_press_y= y;
    


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
