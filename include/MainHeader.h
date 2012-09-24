#pragma once

#define TEXTURESIZE 1024
#define AppWidth 800
#define AppHeight 600

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Shape.h"
#include "Rect.h"
#include "Circle.h"
#include "cinder/Rand.h"


using namespace ci;
using namespace ci::app;
using namespace std;

/*
 *node structure is the heart of this double linked structure
 *next and prev will contain the previous node and the next node
 *each node contains its own shape object
 *Satisfies goal A in HW02
 */
struct node {
	node* next;
	node* prev;
	Shape* shape;
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
	void deleteShape(int xValue, int yValue);
	
	int currentX;
	int currentY;
	int nodeCount;
	bool showInstructions;

	gl::Texture texture;

	Color8u BGColor;

  private:
	void insertAfter(node *where, Shape* newShape);
	void Delete(node *deleteMe);

	void refreshBackground(uint8_t* dataArray);

	Surface* mySurface;
	uint8_t* dataArray;
	Rand rand;


	int frameNumber;
	node* sentinel;

};
