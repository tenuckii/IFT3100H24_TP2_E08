#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
    cursor.setup();

    drawingTool.setup();
    renderer.setup();
    imageExpImp.setup();
    geometrie3D.setup();


    glm::vec3 screenCenter(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    glm::vec3 cameraPosition = camera.getPosition();
    glm::vec3 upVector(0, -1, 0);
    glm::vec3 cameraDirection = screenCenter - cameraPosition;
    camera.lookAt(cameraDirection, upVector);

    camTop.lookAt(cameraDirection);

    camDroit.lookAt(cameraDirection);

    camGauche.lookAt(cameraDirection);

    rotationPoint[0] = 0;
    rotationPoint[1] = 0;
    rotationPoint[2] = 0;
    // keep last
    interface.setup(&cursor, &drawingTool, &imageExpImp, &geometrie3D);
    renderer.inSelection = false;
}

//--------------------------------------------------------------
void Application::update()
{

}

//--------------------------------------------------------------
void Application::draw()
{
    cursor.draw(drawingTool.getCurrentPrimitiveType());

    switch (mode)
    {
    case Mode::VIEW_2D:
       case 2:
          ofDisableLighting();
        drawingTool.draw();
        renderer.draw(drawingTool.getDrawingToolStatus());
        imageExpImp.draw();
        break;
    case Mode::VIEW_3D:
        if (geometrie3D.nb_cam2 >= 1) {
            camera.begin();
            ofViewport(0, 0, ofGetWindowWidth() / (geometrie3D.nb_cam2 >= 2 ? 2 : 1),  ofGetWindowHeight() / (geometrie3D.nb_cam2 % 2 == 0 ? geometrie3D.nb_cam2 / 2 : (geometrie3D.nb_cam2 + 1) / 2),true);
            mainCam[0] = 0;
            mainCam[1] = ofGetWindowWidth() / (geometrie3D.nb_cam2 >= 2 ? 2 : 1);
            mainCam[2] = 0;
            mainCam[3] = ofGetWindowHeight() / (geometrie3D.nb_cam2 % 2 == 0 ? geometrie3D.nb_cam2 / 2 : (geometrie3D.nb_cam2 + 1) / 2);
            geometrie3D.draw();
            camera.end();
        }

        if (geometrie3D.nb_cam2 >= 2) {
            camTop.begin();
            ofViewport(ofGetWidth() / 2, 0, ofGetWindowWidth(), ofGetWindowHeight() / (geometrie3D.nb_cam2 % 2 == 0 ? geometrie3D.nb_cam2 / 2 : (geometrie3D.nb_cam2 + 1) / 2),true);
            cameraTop[0] = ofGetWindowWidth() / 2;
            cameraTop[1] = ofGetWindowWidth();
            cameraTop[2] = 0;
            cameraTop[3] = ofGetWindowHeight() / (geometrie3D.nb_cam2 % 2 == 0 ? geometrie3D.nb_cam2 / 2 : (geometrie3D.nb_cam2 + 1) / 2);
            geometrie3D.draw();
            camTop.end();
        }

        if (geometrie3D.nb_cam2 >= 3) {
            camDroit.begin();
            ofViewport(0, ofGetHeight() / 2, ofGetWindowWidth() /floor(geometrie3D.nb_cam2 / 2), ofGetWindowHeight(),true);
            cameraDroit[0] = 0;
            cameraDroit[1] = ofGetWindowWidth() / floor(geometrie3D.nb_cam2 / 2);
            cameraDroit[2] = ofGetWindowHeight() / 2;
            cameraDroit[3] = ofGetWindowHeight();
            geometrie3D.draw();
            camDroit.end();
        }

        if (geometrie3D.nb_cam2 >= 4) {
            camGauche.begin();
            ofViewport(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, ofGetWindowWidth(), ofGetWindowHeight(),true);
            cameraGauche[0] = ofGetWindowWidth() / 2;
            cameraGauche[1] = ofGetWindowWidth();
            cameraGauche[2] = ofGetWindowHeight() / 2;
            cameraGauche[3] = ofGetWindowHeight();
            geometrie3D.draw();
            camGauche.end();
        }
         
    }
    interface.draw(mode, mode_change);
}

void Application::exit()
{
    cursor.exit();
    drawingTool.exit();
}

//--------------------------------------------------------------
void Application::keyPressed(int key)
{
    switch (choix_de_cam)
    {
    case 1:
        switch (key)
        {
        case OF_KEY_UP:
            camera.move(0, 10, 0);
            break;
        case OF_KEY_DOWN:
            camera.move(0, -10, 0);
            break;
        case OF_KEY_LEFT:
            camera.move(-10, 0, 0);
            break;
        case OF_KEY_RIGHT:
            camera.move(10, 0, 0);
            break;
        case OF_KEY_PAGE_UP:
            camera.move(0, 0, 10);
            break;
        case OF_KEY_PAGE_DOWN:
            camera.move(0, 0, -10);
            break;
        case 'q':
            camera.rotateAroundDeg(2, glm::vec3(1, 0, 0),rotationPoint);
        case 'e':
            camera.rotateAroundDeg(2, glm::vec3(0, 1, 0), rotationPoint);
        case 'r':
            camera.rotateAroundDeg(2, glm::vec3(0, 0, 1), rotationPoint);
        }
        break;
    case 2:
        switch (key)
        {
        case OF_KEY_UP:
            camTop.move(0, 10, 0);
            break;
        case OF_KEY_DOWN:
            camTop.move(0, -10, 0);
            break;
        case OF_KEY_LEFT:
            camTop.move(-10, 0, 0);
            break;
        case OF_KEY_RIGHT:
            camTop.move(10, 0, 0);
            break;
        case OF_KEY_PAGE_UP:
            camTop.move(0, 0, 10);
            break;
        case OF_KEY_PAGE_DOWN:
            camTop.move(0, 0, -10);
            break;
        }
        break;
    case 3:
        switch (key)
        {
        case OF_KEY_UP:
            camDroit.move(0, 10, 0);
            break;
        case OF_KEY_DOWN:
            camDroit.move(0, -10, 0);
            break;
        case OF_KEY_LEFT:
            camDroit.move(-10, 0, 0);
            break;
        case OF_KEY_RIGHT:
            camDroit.move(10, 0, 0);
            break;
        case OF_KEY_PAGE_UP:
            camDroit.move(0, 0, 10);
            break;
        case OF_KEY_PAGE_DOWN:
            camDroit.move(0, 0, -10);
            break;
        }
        break;
    case 4 :
        switch (key)
        {
        case OF_KEY_UP:
            camGauche.move(0, 10, 0);
            break;
        case OF_KEY_DOWN:
            camGauche.move(0, -10, 0);
            break;
        case OF_KEY_LEFT:
            camGauche.move(-10, 0, 0);
            break;
        case OF_KEY_RIGHT:
            camGauche.move(10, 0, 0);
            break;
        case OF_KEY_PAGE_UP:
            camGauche.move(0, 0, 10);
            break;
        case OF_KEY_PAGE_DOWN:
            camGauche.move(0, 0, -10);
            break;
        }
        break;
    }
}

//--------------------------------------------------------------
void Application::keyReleased(int key)
{
    glm::vec3 upVector(0, -1, 0);
    // exporter/importer
    switch (key)
    {
       
     case 's':
           renderer.inSelection = !renderer.inSelection;
           break;
    case '2':
        mode = VIEW_2D;
        mode_change = true;
        break;
    case '3':
        mode = VIEW_3D;
        mode_change = true;
        break;
    case 'f':
        camera.lookAt(geometrie3D.regarde_un_objet, upVector);
    }
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y)
{
    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);
    imageExpImp.mouse_current_x = x;
    imageExpImp.mouse_current_y = y;
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button)
{
    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);
    imageExpImp.mouse_current_x = x;
    imageExpImp.mouse_current_y = y;
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){


    if (mode == VIEW_3D)
    {

        rotationPoint[0] = x;
        rotationPoint[1] = y;


        choisirCamABouger(ofGetMouseX(), ofGetMouseY());
    }

    cursor.set_position(x,y);
    if(renderer.inSelection)
    {   
        renderer.SelectChecker(x,y);

    }
    else {
        renderer.setMousePressStatus(true);
        renderer.setMousePosition(x, y);
        renderer.setMouseClickPosition(x, y);
        imageExpImp.mouse_press_x = x;
        imageExpImp.mouse_press_y = y;
        imageExpImp.is_mouse_button_pressed = true;

    }
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
    if (!renderer.inSelection)
    {
        cursor.set_position(x, y);
        renderer.setMousePressStatus(false);
        renderer.setMousePosition(x, y);
        if (imageExpImp.is_mouse_button_pressed)
        {
            imageExpImp.mouse_current_x = x;
            imageExpImp.mouse_current_y = y;
            imageExpImp.is_mouse_button_pressed = false;
        }
    }
   
}
//--------------------------------------------------------------
void Application::mouseEntered(int x, int y)
{
    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);
    imageExpImp.mouse_current_x = x;
    imageExpImp.mouse_current_y = y;
}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y)
{
    renderer.setMousePosition(x, y);
    imageExpImp.mouse_current_x = x;
    imageExpImp.mouse_current_y = y;
}

//--------------------------------------------------------------
void Application::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg)
{
}



//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo)
{
}

int Application::choisirCamABouger(int x, int y)
{
    if (x >= mainCam[0] && x < mainCam[1] && y >= mainCam[2] && y < mainCam[3])
    {
        return choix_de_cam = 1;
    }
    else if (x >= cameraTop[0] && x < cameraTop[1] && y >= cameraTop[2] && y < cameraTop[3])
    {
        return choix_de_cam = 2;
    }
    else if (x >= cameraDroit[0] && x < cameraDroit[1] && y >= cameraDroit[2] && y < cameraDroit[3])
    {
        return choix_de_cam = 3;
    }
    else if (x >= cameraGauche[0] && x < cameraGauche[1] && y >= cameraGauche[2] && y < cameraGauche[3])
    {
        return choix_de_cam = 4;
    }
}
