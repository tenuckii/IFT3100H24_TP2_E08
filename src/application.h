#pragma once

#include "ofMain.h"
#include "cursor.h"
<<<<<<< HEAD
=======
#include "ofxGui.h"
#include "drawingTool.h"
>>>>>>> fff29631ede41043027c57210c1be77d900d13b9
#include "ImageExpImp.h"

class Application : public ofBaseApp{

	public:
		ImageExpImp imageExpImp;
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        Cursor cursor;
		DrawingTool drawingTool;
		Renderer renderer;
		
};
