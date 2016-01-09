#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(0,0,0);
    ofSetFullscreen(false);
//    ofSetBackgroundAuto(false);
    testFont.loadFont("Papyrus.ttc", 250, true, true, true);
    testFont2.loadFont("Modern No. 20", 160, true, true, true);
    
    letters = "4096";
    
    int addedPointCounter = 0;
    int countourPoints = 0;
    float currentX = 0;
    for(int lt = 0; lt< letters.length(); lt++)
    {
        letter = letters[lt];
        testChar = testFont2.getCharacterAsPoints(letter);
        
        float maxDist = .005;
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
void testApp::draw1()
{
    
}
void testApp::draw2()
{
    
}
void testApp::draw3()
{

    ofFill();
    ofEnableDepthTest();
//    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 10);
    
    float tm = 0;
    
    float ampl = 3000;
    int lettersToDraw =points.size();//(int)(points.size()*ofGetMouseX()*1.f/ofGetWindowWidth());
    //    lettersToDraw = MIN(lettersToDraw,points.size());
    
    
    ofTranslate(ofGetWindowWidth()/2-180, -25,-200);
    ofRotateX(30);//ofGetElapsedTimef()*50);//
    
//    ofSetLineWidth(3);
    
    int snSteps = (ofGetMouseX()*1000)/ofGetWindowWidth();
    float xpct = max(ofGetMouseX()*1.f/ofGetWindowWidth(), 0.f);
    for(int k = 0; k < snSteps; k++)
    {
//        if(k>1r0)
            ofNoFill();

        ofPushMatrix();
        float kPct = k*1.f/snSteps;
        
        ofTranslate(0, 0, -(pow(kPct, 1.7f))*1500);

        float sn = 1-(1+cosf(pow(kPct, 1.7f)*PI))/2.f;
        float xDist = ampl*sn;
        float yDist = .2*ampl*ofGetMouseY()/ofGetWindowHeight();
        ofSetColor(255*(1+sinf(kPct*125))/2.f,
                   0,
                   0,
                   255 );
        ofBeginShape();
        for(int i = 0; i < lettersToDraw; i++)
        {
            for(int j = 0; j < points[i].size(); j++)
            {
                ofVec3f v = points[i][j];
                float pct = j*1.f/points[i].size();
                float rAngle = tm+pct*4*TWO_PI;
                float distortion = sin(tm*5 + (j*yDist/points[i].size()) );
                distortion *= distortion* distortion* distortion;
                distortion *= xDist;
                
                ofVec3f offs(distortion*cos(rAngle),distortion*sin(rAngle));
                
                float nof = max(0.0001f,(1-kPct)*25);
                float amp = kPct*55;
                ofVec3f nOffs(amp*sn*cos(pct+(v.x + offs.x)/nof),amp*sn*sin(pct+(v.y + offs.y)/nof));
                ofVertex(v.x + offs.x + nOffs.x,
                         v.y + offs.y+nOffs.y);
            }
            ofNextContour(true) ;
        }
        ofEndShape( true );
        ofPopMatrix();
    }

}
void testApp::origDraw()
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
void testApp::draw()
{
//    draw3();
    origDraw();
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofSaveFrame();

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
