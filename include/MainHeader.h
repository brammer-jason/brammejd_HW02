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
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;




struct node {
	node* next;
	node* prev;
	Rect* rect;
};

class brammejd_HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void reverseList(node* sentinel);
	
	int currentX;
	int currentY;
	int nodeCount;

	gl::Texture texture;

	Color8u BGColor;

  private:
	void insertAfter(node *where, Rect* newRect);
	void Delete(node *deleteMe);

	void refreshBackground(uint8_t* dataArray);

	Surface* mySurface;
	uint8_t* dataArray;
	Rand rand;


	int frameNumber;
	node* sentinel;

};
