#include "ofApp.h"

 Params param;
 ofBaseApp baseApp;
 Particle particle;
//--------------------------------------------------------------

void Params::setup() {
    
    
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = 300;
    velRad = 0;
    lifeTime = 3.0;
    rotate = 0;
    force = -1000;
    spinning = 1000;
    friction = 0.05;
    
}

//--------------------------------------------------------------


Particle::Particle() {
    live = false;
}
//--------------------------------------------------------------

ofPoint randomPointInCircle( float maxRad ){
    ofPoint pnt;
    float rad = ofRandom( 0, maxRad );
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    return pnt;
    
}
//--------------------------------------------------------------

void Particle::setup() {
    
    pos = param.eCenter + randomPointInCircle( param.eRad );
    vel = randomPointInCircle( param.velRad );
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
    
    
}
//--------------------------------------------------------------

void Particle::update( float dt ){
    if ( live ) {
        //Rotate vel
        vel.rotate( 0, 0, param.rotate * dt );
        
        ofPoint acc;         //Acceleration
        ofPoint delta = pos - param.eCenter;
        float len = delta.length();
        if ( ofInRange( len, 0, param.eRad ) ) {
            delta.normalize();
            //Attraction/repulsion force
            acc += delta * param.force;
            //Spinning force
            acc.x += -delta.y * param.spinning;
            acc.y += delta.x * param.spinning;
        }
        
        vel += acc * dt;            //Euler method
        vel *= ( 1 - param.friction );  //Friction
        //Update pos
        pos += vel * dt;    //Euler method
        //Update time and check if particle should die
        time += dt;
        if ( time >= lifeTime ) {
            live = false;   //Particle is now considered as died
        }
    }
}
//--------------------------------------------------------------

void Particle::draw(){
    if ( live ) {
        color1 = 240;
        color2 = 120;
        //Compute size
        float size = ofMap(fabs(time - lifeTime/2), 0, lifeTime/2, 3, 1 );
        //Compute color
        ofColor color = ofColor::red;
        float hue = ofMap( time, 0, lifeTime, color1 , color2 );
        color.setHue( hue );
        ofSetColor( color );
        ofCircle( pos, size );  //Draw particle
        
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );    //Set screen frame rate
    ofToggleFullscreen();
    //GUI
    gui.setup( "Parameters", "settings.xml" );
    gui.add( countX.setup( "countX", 50, -1000, 1000 ) );
    gui.add( rotate.setup( "rotate", 50, 0, 720 ) );
    gui.add( spinning.setup( "spinning", 50, -1000, 1000 ) );
    gui.add( eRad.setup( "eRad", 50, -100, 1000 ) );
    gui.add( color1.setup( "color1", 50, 0, 255 ) );
    
    
    
    history = 0.9;
    bornRate = 200;
    bornCount = 0;
    
    
    //Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate( w, h, GL_RGB32F_ARB );
    //Fill buffer with white color
    fbo.begin();
    ofBackground(color1);
    fbo.end();
    //Set up parameters
    param.setup();          //Global parameters
    history = 0.995;
    time0 = ofGetElapsedTimef();
}

void ofApp::update(){
    //Compute dt
    float f = countX;
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    
    //Delete inactive particles
    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
        }else {
            i++;
       }
        
    }
    //Born new particles
    bornCount += dt * bornRate;
    if ( bornCount >= 1 ) {
        //Update bornCount value
        //It's time to born particle(s)
        int bornN = int( bornCount );//How many born
        bornCount -= bornN;          //Correct bornCount value
        for (int i=0; i<bornN; i++) {
            Particle newP;
            newP.setup();            //Start a new particle
            p.push_back( newP );     //Add this particle to array
            
            //Update the particles
            for (int i=0; i<p.size(); i++) {
                p[i].update( dt );
            }
            
            
        }
        
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    param.force = countX;
    param.rotate = rotate;
    param.rotate = spinning;
    param.eRad = eRad;
    
    
    

    
    ofBackground( 0,0,0 );  //Set white background
    //1. Drawing to buffer
    fbo.begin();
    //Draw semi-transparent white rectangle
    //to slightly clearing a buffer (depends on history value)
    ofEnableAlphaBlending();         //Enable transparency
    float alpha = (1-history) * 255;
    ofSetColor( 0, 0, 0, alpha*5 );
    ofFill();
    ofRect( 0, 0, ofGetWidth(), ofGetHeight() );
    ofDisableAlphaBlending();
    //Draw the particles
    ofFill();
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
        
    }
    
    fbo.end();
    //2. Draw buffer on the screen
    ofSetColor( 255, 255, 255 );
    fbo.draw( 0, 0 );
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
