#include "ImageExpImp.h"

void ImageExpImp::setup()
{
    GUI_image_setup();
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
    if (gui_image)
    {
        importeGui.draw();
    }

    if (is_mouse_button_pressed)
    {
        // dessiner la zone de s�lection
        draw_zone(
            mouse_press_x,
            mouse_press_y,
            mouse_current_x,
            mouse_current_y);
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

    // extraire des donn�es temporelles format�es
    string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

    string file_name = fileName;
    string file = file_name + "_" + time_stamp;
    if (is_mouse_button_pressed)
    {
        image.grabScreen(mouse_press_x, mouse_press_y, mouse_current_x, mouse_current_y);
    }
    else
    {
        image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    // capturer le contenu du framebuffer actif

    ofFileDialogResult direct = ofSystemLoadDialog("Enregistrer dans...", true);
    if (direct.bSuccess)
    {
        string ext = ofSystemTextBoxDialog("Format fichier (jpg, png, ...)", "png");

        if (ext == "jpg" || ext == "png")
        {
            file_name = direct.getPath() + "/" + file + "." + ext;
            image.save(file_name);
        }
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
    importeGui.setup("Image Importer/Exporter");

    importeGui.setDefaultWidth(270);
    importeGui.setDefaultHeight(20);
    importeGui.setSize(270, 200);
    importeGui.setPosition(750, 10);

    import_img.setup("Import d'image");
    // position image
    img_start_x.set("x start position", 150, 0, ofGetWindowWidth());
    img_start_y.set("y start position", 150, 0, ofGetWindowHeight());
    img_end_x.set("x end position", 600, 0, ofGetWindowWidth());
    img_end_y.set("y end position", 600, 0, ofGetWindowHeight());
    // boutton import
    import.setup("importe");
    import.addListener(this, &ImageExpImp::import_button_pressed);

    import_img.add(img_start_x);
    import_img.add(img_start_y);
    import_img.add(img_end_x);
    import_img.add(img_end_y);
    import_img.add(&import);

    // export
    export_img.setup("Export d'image");
    // boutton export1
    exporte.setup("Exporter");
    exporte.addListener(this, &ImageExpImp::exporte_button_pressed);
    // boutton export2
    exportPartie.setup("Exporter Partie");
    exportPartie.addListener(this, &ImageExpImp::exportPartie_button_pressed);

    fileName.set("Entre le nom du fichier");

    export_img.add(fileName);
    export_img.add(&exporte);
    export_img.add(&exportPartie);
    // gui add
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
    is_mouse_button_pressed = true;
}

void ImageExpImp::show_hide_ui()
{
    gui_image = !gui_image;
}

ofxBaseGui * ImageExpImp::getUi(){
    return &importeGui;
}