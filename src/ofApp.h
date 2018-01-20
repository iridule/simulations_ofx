
//
#pragma once

#include "ofMain.h"
#include "chemicals.hpp"
#include <utility>

//
class ofApp : public ofBaseApp{

	//
	public:

		//
		void setup();
		void update();
		void draw();
		float laplaceA(int x, int y, int width, int height, std::vector <std::pair<ChemicalA, ChemicalB>> *chemicals);
		float laplaceB(int x, int y, int width, int height, std::vector <std::pair<ChemicalA, ChemicalB>> *chemicals);


	//
	private:
		
		//
		int width;
		int height;
		std::vector <std::pair<ChemicalA, ChemicalB>> temp;
		std::vector <std::pair<ChemicalA, ChemicalB>> chemicals;
		std::vector <std::pair<ChemicalA, ChemicalB>> next;
		unsigned char *output;

		//
		float dA;
		float dB;
		float feed;
		float k;
		float t;

		//
		ofTexture texture;

};
