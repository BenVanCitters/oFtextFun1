#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(0,0,0);
    ofSetFullscreen(false);
//    ofSetBackgroundAuto(false);
    testFont.loadFont("Papyrus.ttc", 250, true, true, true);
    testFont2.loadFont("cooperBlack.ttf", 160, true, true, true);
    
    letters = "VOXMOD";
    
    int addedPointCounter = 0;
    int countourPoints = 0;
    float currentX = 0;
    for(int lt = 0; lt< letters.length(); lt++)
    {
        letter = letters[lt];
        testChar = testFont2.getCharacterAsPoints(letter);
        
        float maxDist = .1;
        float maxXforLetter = 0;
        for(int k = 0; k <(int)testChar.getOutline().size(); k++)
        {
            vector<ofVec3f>contour;
            ofVec3f last(testChar.getOutline()[k].getVertices()[0].x,
                         testChar.getOutline()[k].getVertices()[0].y);
            last.x += currentX;
            for(int i = 0; i < (int)testChar.getOutline()[k].size(); i++)
            {
                
                float x = testChar.getOutline()[k].getVertices()[i].x;
                maxXforLetter = MAX(x,maxXforLetter);
                x +=currentX;
                float y = testChar.getOutline()[k].getVertices()[i].y;
                ofVec3f v = ofVec3f(x,y);
                float d = ofDist(v.x, v.y, last.x, last.y);
                if(d > maxDist)
                {
                    ofVec3f diff = v-last;
                    int newDivs =(int)(d/maxDist);
                    for(int k = 0; k < newDivs; k++)
                    {
                        ofVec3f newpoint = last + (k*1.f/newDivs)*diff;
                        contour.push_back(newpoint);
                        addedPointCounter++;
                    }
                }
                countourPoints++;
                contour.push_back(v);
                last = v;
            }
            
            ofVec3f first(testChar.getOutline()[k].getVertices()[0].x,
                         testChar.getOutline()[k].getVertices()[0].y);
            first.x+= currentX;
            float d = ofDist(last.x, last.y, first.x, first.y);
            if(d > maxDist)
            {
                ofVec3f diff = first-last;
                int newDivs =(int)(d/maxDist);
                for(int k = 0; k < newDivs; k++)
                {
                    ofVec3f newpoint = last + (k*1.f/newDivs)*diff;
                    contour.push_back(newpoint);
                    addedPointCounter++;
                }
                
            }
            points.push_back(contour);
        }
        currentX+= maxXforLetter + 3;
    }
    
    ofLog(OF_LOG_NOTICE, "normal points: %d addedpoints: %d totalpoints: %d", countourPoints, addedPointCounter, (countourPoints+addedPointCounter));
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw()
{
    ofSetColor(255, 100, 200,190 );
    ofFill();

    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 10);

    float tm = ofGetElapsedTimef();
    
    int amt =(int)(points.size()*ofGetMouseX()/ofGetWindowWidth());
    float ampl = 300;
    int lettersToDraw =points.size();//(int)(points.size()*ofGetMouseX()*1.f/ofGetWindowWidth());
//    lettersToDraw = MIN(lettersToDraw,points.size());
    float xDist = ampl*ofGetMouseX()/ofGetWindowWidth();
    float yDist = ampl*ofGetMouseY()/ofGetWindowHeight();
    ofNoFill();
    ofPushMatrix();
    ofTranslate(100, 450, 0);
    
    
    ofSetLineWidth(3.1);
    ofBeginShape();
    for(int i = 0; i < lettersToDraw; i++)
    {
        for(int j = 0; j < points[i].size(); j++)
        {
            ofVec3f v = points[i][j];
//            ofVertex(v.x + xDist*sin(3*tm+v.y/5.f),
//                     v.y + yDist*sin(3*tm+v.x/50.f));
            float rAngle = tm+j*4*TWO_PI/points[i].size(); //ofRandom(TWO_PI);
//            float rRad = ofRandom(TWO_PI);
            float distortion = sin(tm*5 + (j*yDist/points[i].size()) );
            distortion *= distortion* distortion* distortion;
            distortion *= xDist;
//            ofSetColor(255, 100, 200,80/xDist );
            ofVec3f offs(distortion*cos(rAngle),distortion*sin(rAngle));
            ofVertex(v.x + offs.x,
                     v.y + offs.y);
        }
        ofNextContour(true) ;
    }
    ofEndShape( true );
    ofPopMatrix();
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
    ofBackground(0, 0, 0);
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
