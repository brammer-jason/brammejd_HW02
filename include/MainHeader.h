#pragma once

#define TEXTURESIZE 1024
#define AppWidth 800
#define AppHeight 600

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Rect.h"


using namespace ci;
using namespace ci::app;
using namespace std;




struct node {
	node* next;
	node* prev;
	Rect* rect;
};
typedef node *link;

class brammejd_HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	
	Color8u BGColor;

  private:
	void insertAfter(node *where, Rect* newRect);
	void Delete(node *deleteMe);
	void displayInfo(node *sentinel);

	void refreshBackground(uint8_t* dataArray);

	Surface* mySurface;


	int frameNumber;
	node* sentinel;

	void addRectangle(uint8_t* dataArray, int rectHeight, int rectLength, 
					  int startX, int startY, Color8u c, bool fill);

	void addCircle(uint8_t* dataArray, int radius, int xCenter, int yCenter, Color8u c, bool fill);
};
