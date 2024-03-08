#include "ImageExpImp.h"

void ImageExpImp::setup()
{
    GUI_image_setup();
    zoneExportingInProgress = exportOnMouseRelease = false;
}

void ImageExpImp::update()
{
}

void ImageExpImp::draw()
{
    for (int i = 0; i < vecImage.size(); i++)
    {
        ofSetColor(255, 255, 255, 255);
        vecImage[i].image.draw(
            vecImage[i].x1,
            vecImage[i].y1,
            vecImage[i].x2,
            vecImage[i].y2);
    }

    if (zoneExportingInProgress) {

        if (exportOnMouseRelease && !is_mouse_button_pressed) {

            // exporter l'image dans la zone selectionne
            export_image();
            exportOnMouseRelease = false;
            zoneExportingInProgress = false;
        }
        else if (is_mouse_button_pressed) {
            exportOnMouseRelease = true;

            // dessiner la zone de selection
            draw_zone(
                mouse_press_x,
                mouse_press_y,
                mouse_current_x,
                mouse_current_y);
        }
    }
}

void ImageExpImp::draw_zone(float x1, float y1, float x2, float y2) const
{
    float x2_clamp = min(max(0.0f, x2), (float)ofGetWidth());
    float y2_clamp = min(max(0.0f, y2), (float)ofGetHeight());

    ofSetLineWidth(radius);
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
    ofFill();
    ofDrawEllipse(x1, y1, radius, radius);
    ofDrawEllipse(x1, y2_clamp, radius, radius);
    ofDrawEllipse(x2_clamp, y1, radius, radius);
    ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

void ImageExpImp::export_image()
{
    ofImage image;

    // capturer le contenu du framebuffer actif
    if (zoneExportingInProgress) {
        float xStart = mouse_current_x < mouse_press_x ? mouse_current_x : mouse_press_x;
        float yStart = mouse_current_y < mouse_press_y ? mouse_current_y : mouse_press_y;
        float width = abs(mouse_current_x - mouse_press_x);
        float height = abs(mouse_current_y - mouse_press_y);
        image.grabScreen(xStart, yStart, width, height);
    }
    
    else
        image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    ofFileDialogResult directory = ofSystemLoadDialog("Enregistrer dans...", true);
    if (directory.bSuccess)
    {
        string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
        string fileName = ofSystemTextBoxDialog("Nom du fichier", "Screenshot" + time_stamp);
        string filePath = directory.getPath() + "/" + fileName + ".png";
        image.save(filePath);
    }
}

void ImageExpImp::image_import()
{

    ofFileDialogResult result = ofSystemLoadDialog("Choisissez une image");
    if (result.bSuccess)
    {
        image_struct img;
        img.image.load(result.filePath);
        img.x1 = img_start_x;
        img.y1 = img_start_y;
        img.x2 = img_end_x;
        img.y2 = img_end_y;
        vecImage.push_back(img);
    }
}

void ImageExpImp::GUI_image_setup()
{
    importeGui.setup("Images");

    importeGui.setDefaultWidth(270);
    importeGui.setDefaultHeight(20);
    importeGui.setSize(270, 200);
    importeGui.setPosition(750, 10);

    import_img.setup("Importation");
    // position image
    img_start_x.set("Position de debut en x", 150, 0, ofGetWindowWidth());
    img_start_y.set("Position de debut en y", 150, 0, ofGetWindowHeight());
    img_end_x.set("Position de fin en x", 600, 0, ofGetWindowWidth());
    img_end_y.set("Position de fin en y", 600, 0, ofGetWindowHeight());
    // boutton import
    import.setup("Importer");
    import.addListener(this, &ImageExpImp::import_button_pressed);

    import_img.add(img_start_x);
    import_img.add(img_start_y);
    import_img.add(img_end_x);
    import_img.add(img_end_y);
    import_img.add(&import);

    // export
    export_img.setup("Exportation");
    // boutton export1
    exporte.setup("Exporter l'ecran");
    exporte.addListener(this, &ImageExpImp::exporte_button_pressed);
    // boutton export2
    exportPartie.setup("Exporter une zone de l'ecran");
    exportPartie.addListener(this, &ImageExpImp::exportPartie_button_pressed);

    export_img.add(&exporte);
    export_img.add(&exportPartie);
    importeGui.add(&import_img);
    importeGui.add(&export_img);
}

void ImageExpImp::import_button_pressed()
{
    image_import();
}

void ImageExpImp::exporte_button_pressed()
{
    export_image();
}

void ImageExpImp::exportPartie_button_pressed()
{
    zoneExportingInProgress = true;
}

ofxBaseGui * ImageExpImp::getUi(){
    return &importeGui;
}