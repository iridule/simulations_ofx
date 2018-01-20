
//
#include "ofApp.h"

//--------------------------------------------------------------
float ofApp::laplaceA(int x, int y, int width, int height, std::vector <std::pair<ChemicalA, ChemicalB>> *chemicals) {
        
    //
    float compute = 0.0;    
    float c = 0.05;
    float a = 0.2;
    float m = -1;

    compute += chemicals->at((x - 1) + ((y - 1) * width)).first.get() * c;
    compute += chemicals->at((x) + ((y - 1) * width)).first.get() * a;
    compute += chemicals->at((x + 1) + ((y - 1) * width)).first.get() * c;            

    compute += chemicals->at((x - 1) + ((y) * width)).first.get() * a;
    compute += chemicals->at((x) + ((y) * width)).first.get() * m;    
    compute += chemicals->at((x + 1) + ((y) * width)).first.get() * a;    

    compute += chemicals->at((x - 1) + ((y + 1) * width)).first.get() * c;
    compute += chemicals->at((x) + ((y + 1) * width)).first.get() * a;    
    compute += chemicals->at((x + 1) + ((y + 1) * width)).first.get() * c;            

    return compute;

}

//--------------------------------------------------------------
float ofApp::laplaceB(int x, int y, int width, int height, std::vector <std::pair<ChemicalA, ChemicalB>> *chemicals) {

    float compute = 0.0;    
    float c = 0.05;
    float a = 0.2;
    float m = -1;

    compute += chemicals->at((x - 1) + ((y - 1) * width)).second.get() * c;
    compute += chemicals->at((x) + ((y - 1) * width)).second.get() * a;
    compute += chemicals->at((x + 1) + ((y - 1) * width)).second.get() * c;            

    compute += chemicals->at((x - 1) + ((y) * width)).second.get() * a;
    compute += chemicals->at((x) + ((y) * width)).second.get() * m;    
    compute += chemicals->at((x + 1) + ((y) * width)).second.get() * a;    

    compute += chemicals->at((x - 1) + ((y + 1) * width)).second.get() * c;
    compute += chemicals->at((x) + ((y + 1) * width)).second.get() * a;    
    compute += chemicals->at((x + 1) + ((y + 1) * width)).second.get() * c;            

    return compute;

}

//--------------------------------------------------------------
void ofApp::setup() {

    //
    width = ofGetWidth();
    height = ofGetHeight();
    output = new unsigned char[width * height];
    texture.allocate(width, height, GL_LUMINANCE);

    // int the grid
    for (int i = 0; i < width * height; i++) {
        std::pair <ChemicalA, ChemicalB> p{ChemicalA{1.0}, ChemicalB{0.0}};
        std::pair <ChemicalA, ChemicalB> p2{ChemicalA{1.0}, ChemicalB{0.0}};        
        chemicals.push_back(p);
        next.push_back(p2);
    }

    // set the pixels
    // setup pixel colors based on the amount of chemicals
    for (int j = 0; j < height; j++) {  
        for (int i = 0; i < height; i++) {
            int index = i + (height * j);
            float value = chemicals.at(index).first.get();
            output[index] = (unsigned char)(255 * value);
        }   
    }

    // set the pixels
    // setup pixel colors based on the amount of chemicals
    for (int j = height / 2  - 10; j < height / 2 + 10 ; j++) {  
        for (int i = width / 2 - 10; i < width / 2 + 10; i++) {
            int index = i + (height * j);
            chemicals.at(index).first.set(0.0);
            chemicals.at(index).second.set(1.0);            
        }   
    }

    // parameters
    dA = 1.0;
    dB = 0.5;
    feed = 0.055;
    k = 0.062;
    t = 1.1;
    
}

//--------------------------------------------------------------
void ofApp::update() {

    // swap

    // update
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            
            // set the value in the next grid to some value based on the chemicals
            int index = i + (height * j);

            //
            float a = chemicals.at(index).first.get();
            float b = chemicals.at(index).second.get();
        
            // a prime and b prime
            float ap = 
                a + 
                ((dA * laplaceA(i, j, width, height, &chemicals)) -
                (a * b * b) + 
                (feed * (1 - a))) * t;

            float bp = 
                b + 
          (      (dB * laplaceB(i, j, width, height, &chemicals)) +
                (a * b * b) -
                ((k + feed) * b)) * t;

            // set the next
            next.at(index).first.set(ofClamp(ap, 0, 1));
            next.at(index).second.set(ofClamp(bp, 0, 1)); 

            //
            float first = next.at(index).first.get();   
            float second = next.at(index).second.get();               
            float color =  (first - second) * 255;
            output[index] = (unsigned char)(ofClamp(color, 0, 255));

        }   
    }

    temp = chemicals;
    chemicals = next;
    next = temp;        

    //
    texture.loadData(output, width, height, GL_LUMINANCE);

}

//--------------------------------------------------------------
void ofApp::draw() {
    texture.draw(0, 0, width, height); 
    ofDrawBitmapString((next.at(200).first.get() - next.at(200).second.get()), 50, 50);
}

