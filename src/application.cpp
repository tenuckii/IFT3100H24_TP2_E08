#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
<<<<<<< HEAD
   cursor.setup();
   imageExpImp.setup();

=======
    cursor.setup();
    drawingTool.setup();
    renderer.setup();
    imageExpImp.setup();
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
}

//--------------------------------------------------------------
void Application::update(){

}

//--------------------------------------------------------------
void Application::draw(){
    cursor.draw();
<<<<<<< HEAD
    imageExpImp.draw();
=======
    drawingTool.draw();
    renderer.draw(drawingTool.getPrimitiveCreationData());
    imageExpImp.draw();
}

void Application::exit()
{
    drawingTool.exit();
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
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
<<<<<<< HEAD

    // pour exporter une partie 
=======
    renderer.setMousePosition(x, y); 
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
    }

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
<<<<<<< HEAD
 cursor.set_position(x,y);

 // pour exporter une partie 
=======
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y);

>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
 if (imageExpImp.is_mouse_button_pressed) {
     imageExpImp.mouse_current_x = x;
     imageExpImp.mouse_current_y = y;
 }

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
    cursor.set_position(x,y);

<<<<<<< HEAD

    // pour exporter une partie 
    if (imageExpImp.is_mouse_button_pressed) {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;

        imageExpImp.mouse_press_x = x;
        imageExpImp.mouse_press_y= y;
    }
=======
    renderer.setMousePressStatus(true);
    renderer.setMousePosition(x, y);
    renderer.setMouseClickPosition(x, y);
    imageExpImp.mouse_press_y= y;
    
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
<<<<<<< HEAD
  cursor.set_position(x,y);


  // pour exporter une partie 
  if (imageExpImp.is_mouse_button_pressed) {
=======
    cursor.set_position(x,y);
    renderer.setMousePressStatus(false);
    renderer.setMousePosition(x, y);
    if (imageExpImp.is_mouse_button_pressed) {
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
      imageExpImp.mouse_current_x = x;
      imageExpImp.mouse_current_y = y;
      imageExpImp.export_image();
      imageExpImp.is_mouse_button_pressed = false;
  }
<<<<<<< HEAD
  //
=======
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){
<<<<<<< HEAD
  cursor.set_position(x,y);

=======
    cursor.set_position(x,y);
    renderer.setMousePosition(x, y);
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
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
