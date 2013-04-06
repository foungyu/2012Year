/**
 *
 * OFDevCon Example Code Sprint
 * Model Distort Example
 *
 * This example loads a model and distorts it using noise
 *
 * The model is the open source and freely licensed balloon dog by Rob Myers, commissioned by furtherfield:
 * http://www.furtherfield.org/projects/balloon-dog-rob-myers
 *
 * Created by James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */


#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	//this is our model we'll draw
    ofxAssimpModelLoader model;
    
	ofLight light;
	
	//we added these functions to make it easier to switch between the two methods of drawing
	//void drawWithModel();
	void drawWithMesh();
    
    ofEasyCam cam;
    ofVec3f allVec[4243];
     ofVec3f allVec_y[4243];
     ofVec3f allVec_z[4243];
    //2371
    //4243
    ofMesh mesh;
    ofMesh mesh2;
    ofMesh mesh_y;
    ofMesh mesh_z;
    ofMesh regenerateMesh;
    int regernerateVertexId[4243];
    int Vertexid;
    bool shootingFace;
    ofImage image1;
    void changeTexture();
    int textureId;
    int generateCount;
    int rotateAngle;
    string addvertex;
    int countStop;
    
    ofSoundPlayer  mySound;
    void soundUpdate();
    
    int soundBands;
    float* fft;
    float soundVol;
};
