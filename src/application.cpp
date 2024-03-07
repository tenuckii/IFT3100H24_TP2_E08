#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
    mode = Mode::VIEW_2D;
    mode_change = false;
    
    cursor.setup();

    drawingTool.setup();
    renderer.setup();
    imageExpImp.setup();
    geometrie3D.setup();

    // keep last
    interface.setup(&cursor, &drawingTool, &imageExpImp, &geometrie3D);
}

//--------------------------------------------------------------
void Application::update()
{
}

//--------------------------------------------------------------
void Application::draw()
{
    cursor.draw();
    interface.draw(mode, mode_change);
    switch (mode)
    {
    case Mode::VIEW_2D:
        drawingTool.draw();
        renderer.draw(drawingTool.getPrimitiveCreationData());
        imageExpImp.draw();
        break;
    case Mode::VIEW_3D:
        geometrie3D.draw();
        break;
    }
}

void Application::exit()
{
    cursor.exit();
    drawingTool.exit();
}

//--------------------------------------------------------------
void Application::keyPressed(int key)
{
}

//--------------------------------------------------------------
void Application::keyReleased(int key)
{

    // exporter/importer
    switch (key)
    {
    case 'i':
        imageExpImp.show_hide_ui();
        break;
    case 'c':
        cursor.open_close_ui();
        break;
    case '2':
        mode = Mode::VIEW_2D;
        drawingTool.showHideMenu();
        geometrie3D.gui3d_afficher = false;
        mode_change = true;
        break;
    case '3':
        mode = Mode::VIEW_3D;
        drawingTool.showHideMenu();
        geometrie3D.gui3d_afficher = !geometrie3D.gui3d_afficher;
        mode_change = true;
        break;
    }
}

void Application::mouseMoved(int x, int y)
{
    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);
    if (imageExpImp.is_mouse_button_pressed)
    {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
    }
}

//--------------------------------------------------------------

void Application::mouseDragged(int x, int y, int button)
{
    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);

    if (imageExpImp.is_mouse_button_pressed)
    {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
    }
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button)
{
    cursor.set_position(x, y);

    // pour exporter une partie
    if (imageExpImp.is_mouse_button_pressed)
    {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;

        imageExpImp.mouse_press_x = x;
        imageExpImp.mouse_press_y = y;
    }

    renderer.setMousePressStatus(true);
    renderer.setMousePosition(x, y);
    renderer.setMouseClickPosition(x, y);
    imageExpImp.mouse_press_y = y;
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y)
{

    cursor.set_position(x, y);
    renderer.setMousePosition(x, y);

    imageExpImp.mouse_press_y = y;
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
    cursor.set_position(x, y);
    renderer.setMousePressStatus(false);
    renderer.setMousePosition(x, y);
    if (imageExpImp.is_mouse_button_pressed)
    {
        imageExpImp.mouse_current_x = x;
        imageExpImp.mouse_current_y = y;
        imageExpImp.export_image();
        imageExpImp.is_mouse_button_pressed = false;
    }
}
//--------------------------------------------------------------
void Application::mouseExited(int x, int y)
{
    renderer.setMousePosition(x, y);
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
