#pragma once

#include "ofMain.h"
#include "ofxGui.h"



class Particle {
    public:
    Particle();         //Class constructor
    void setup();       //Start particle
    void update( float dt ); //Recalculate physics
    void draw();             //Draw particle
    ofPoint pos;             //Position
    ofPoint vel;             //Velocity
    float time;              //Time of living
    float lifeTime;          //Allowed lifetime
    bool live;               //Is particle live
    float color1;
    float color2;

};
extern Particle particle;

class Params {
    public:
    void setup();
    ofPoint eCenter;       //Emitter center
    float eRad;            //Emitter radius
    float velRad;          //Initial velocity limit
    float lifeTime;        //Lifetime in seconds
   float rotate;
    float force;
    float spinning;
    float friction;
    
    
};

extern Params param;  //Declaration of a global variable



class ofApp : public ofBaseApp{
	public:
    
   
    
    
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector<Particle> p;    //Particle
        //Particle p;
        ofFbo fbo;             //on screen buffer for trails
        float history;         //control for trails
        float time0;           //Time value for computing dt
        float bornRate;        //Particles born rate per second
        float bornCount;       //Integrated number of particles to born
    
        ofxPanel gui;
        ofxIntSlider countX;
        ofxIntSlider rotate;
        ofxIntSlider spinning;
        ofxIntSlider friction;
        ofxIntSlider eRad;
        ofxIntSlider color1;
        ofxIntSlider color2;
        
        


    
    };
extern ofBaseApp baseApp;
