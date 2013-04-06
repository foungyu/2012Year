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

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    soundBands=1000;
    mySound.loadSound("bgsound.wav");
    mySound.setVolume(0.75f);
    mySound.play();
    mySound.setLoop(true);

    countStop=0;
    addvertex="add";
    rotateAngle=0;
  
    ofEnableAlphaBlending();
    ofEnableSmoothing();
	textureId=0;
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(50, 50, 50, 0);
    
    ofDisableArbTex();
	
	//this makes sure that the back of the model doesn't show through the front
	glEnable(GL_DEPTH_TEST);
    
    model.loadModel("test.obj");
    model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.75, 0);
	
    mesh=model.getMesh(0);
    int n = mesh.getNumVertices();
    
    for(int i = 0; i < n; i++) {
		ofVec3f cur = mesh.getVertex(i);
        allVec[i]=cur;
        allVec_y[i]=cur;
        allVec_z[i]=cur;
    }
    //bubblesort
    for (int i=0;i<n-1;i++)
    {
        for (int j=0;j<n-i-1;j++){
            /////////
            ofVec3f cur_z1 = allVec_z[j];
            ofVec3f cur_z2 =allVec_z[j+1];
            if (cur_z1.z<cur_z2.z) {
                ofVec3f tmpVec= allVec_z[j];
                allVec_z[j]=allVec_z[j+1];
                allVec_z[j+1]=tmpVec;
            }
            
            ofVec3f cur_y1 = allVec_y[j];
            ofVec3f cur_y2 =allVec_y[j+1];
            if (cur_y1.y<cur_y2.y) {
                
                ofVec3f tmpVec= allVec_y[j];
                allVec_y[j]=allVec_y[j+1];
                allVec_y[j+1]=tmpVec;
            }
            
            /////////
            ofVec3f cur = allVec[j];
            ofVec3f cur2 =allVec[j+1];
            if (cur.x<cur2.x) {
                int tmp=regernerateVertexId[j];
                regernerateVertexId[j]=regernerateVertexId[j+1];
                regernerateVertexId[j+1]=tmp;
                
                ofVec3f tmpVec= allVec[j];
                allVec[j]=allVec[j+1];
                allVec[j+1]=tmpVec;
            }
        }
    }
    generateCount=0;
    shootingFace=false;
    image1.loadImage("image/1.jpg"); // 512x512 image
    //cam.disableMouseInput();
}

//--------------------------------------------------------------
void testApp::update(){
    soundUpdate();
}
void testApp::soundUpdate(){
    //ofLogNotice()<<mySound.getPan();
    //ofSoundUpdate();
    fft = ofSoundGetSpectrum(soundBands);
    //ofLogNotice()<<*fft;
}
//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackgroundGradient(ofColor(64), ofColor(0));
    //drawWithModel();
    drawWithMesh();
}

//draw the model manually
void testApp::drawWithMesh(){
    rotateAngle+=0.3f;
    ofVec3f scale = model.getScale();
    ofVec3f position = model.getPosition();
    float normalizedScale = model.getNormalizedScale();
    ofVboMesh mesh = model.getMesh(0);
    ofTexture texture = model.getTextureForMesh(0);
    ofMaterial material = model.getMaterialForMesh(0);
    cam.begin();
    
    ofPushMatrix();
    
    position.x+=-500;
    position.y+=-550;
    //translate and scale based on the positioning.
    ofTranslate(position);
    float rotateAng,val;
    val=int(-ofGetMouseX());
   
    rotateAng=ofClamp(val,-600,-550);
    
    ofRotate(rotateAng, 0, 1, 0);
    
    ofRotate(-180,0,1,0);
    ofScale(*fft*10+1,*fft*10+1,*fft*10+1);
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
   
    
    //////////////////regenerate//////////////
    
    //////////////////////////////////////////
    
    //modify mesh with some noise
    if(Vertexid==4243){
        float liquidness = 5;
        //float amplitude = mouseY/100.0;
        
        float amplitude =1;
        float speedDampen = 5;
        vector<ofVec3f>& verts = mesh.getVertices();
        
        for(int i = 0; i < verts.size(); i++){
            verts[i].x += 0.1f*ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
            verts[i].y += 0.1f*ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
            verts[i].z += 0.1f*ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        }
    }
    if(addvertex=="add"){
    for(int k=0;k<4;k++){
        if(Vertexid<4243-4){
            //int id=regernerateVertexId[Vertexid];
            mesh_y.addVertex(allVec_y[Vertexid]);
            Vertexid++;
            mesh_y.addVertex(allVec_y[Vertexid]);
            Vertexid++;
            mesh_y.addVertex(allVec_y[Vertexid]);
            Vertexid++;
            mesh_y.addVertex(allVec_y[Vertexid]);
            Vertexid++;
            mesh_y.addVertex(allVec_y[Vertexid]);
            Vertexid++;
        }else{
            addvertex="stop";
        }
    }
    }else if(addvertex=="delete"){
        if(Vertexid>5){
            Vertexid--;
            mesh_y.removeVertex(Vertexid);
            Vertexid--;
            mesh_y.removeVertex(Vertexid);
            Vertexid--;
            mesh_y.removeVertex(Vertexid);
            Vertexid--;
            mesh_y.removeVertex(Vertexid);
            Vertexid--;
            mesh_y.removeVertex(Vertexid);
        }else{
            addvertex="add";
        }
    }
    
    
    //draw the model manually
    image1.bind();
    //texture.bind();
    material.begin();
    //ofScale(scale.x*1.01f,scale.y*1.01f,scale.z*1.01f);
    if(shootingFace==true){
        //mesh_y.clear();
        //Vertexid=0;
        shootingFace=false;
        vector<ofVec3f>& verts = mesh.getVertices();
        for(int m = 0; m < verts.size(); m++){
            verts[m]=allVec[m];
        }
    }
    //ofLogNotice()<<Vertexid;
    if(addvertex=="add"||addvertex=="delete"){
        if(generateCount%2==0){
            glPointSize(2);
            mesh_y.drawVertices();
        }else{
            mesh_y.drawWireframe();
        }
    }else{ 
        countStop++;
        if(countStop>5000){
            addvertex="delete";
            countStop=0;
        }else{
            mesh.drawWireframe();
        }
        /*if(generateCount%2==0){
            glPointSize(2);
            mesh_y.drawVertices();
        }else{
            mesh_y.drawWireframe();
        }*/
    }
    //mesh.drawWireframe();

    material.end();
    image1.unbind();
    ofPopMatrix();
    cam.end();
    
    
    string str = "framerate is ";
    str += ofToString(ofGetFrameRate(), 2)+"fps";
    ofSetWindowTitle(str);
    changeTexture();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //changeTexture();
    shootingFace=true;
    generateCount++;
    if(addvertex=="add"){
        addvertex="delete";
    }else if(addvertex=="delete"){
        addvertex="add";
    }else{
        addvertex="delete";
    }
    
}
void testApp::changeTexture(){
    if(textureId<8333){
        textureId++;
    }else{
        textureId=1;
    }
    
    string text = ".jpg";
    string imageName ;
    imageName ="image/"+ofToString(textureId)+text;
    image1.loadImage(imageName); // 512x512 image
    
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}