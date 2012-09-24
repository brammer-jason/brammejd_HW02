/*
 *Jason Brammer CSE 273
 *This program is designed around a doubly linked list that can store a circle or a rectangle object inside each node (Objective A: HW02)
 *The user selects whether a circle or a rectangle is stored/drawn by keypresses described in the instructions
 *The user can delete the last node entered with a left mouse click (Objective C: HW02 [kind of])
 *The user can reverse the order of the nodes with a right mouse click (Objective E: HW02)
 *An instructional panel can be show and hidden using the ? key (Objective B: HW02)
 *
 *Note: I made an attempt at (Objective D:HW02) to delete a single node by clicking on the corresponding shape
 *		however there is a bug in deleteShape() method that I cannot put my finger on. Mike/Bo/Peer Reviewer, if you're
 *		reading this, I'd like to implement it even though I wouldn't get points for it. If you can locate the bug
 *		and relay a fix I would appreciate it!!! The code is commented out under the .isLeftDown() mouse event
 */

#pragma once

#include "MainHeader.h"
#include <stdlib.h>
#include <time.h>

using namespace ci;
using namespace ci::app;
using namespace std;

/*
 *initial setup of viewable window
*/
void brammejd_HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(AppWidth, AppHeight);
	(*settings).setResizable(false);
}

/*
 *this method will add a new node to the linked list and also give that node its shape property
*/
void brammejd_HW02App::insertAfter(node* where, Shape* newShape){
	
	node* ourNode = new node;
	where->next->prev = ourNode;
	ourNode ->shape = newShape;
	ourNode ->next = where ->next;
	ourNode ->prev = where;
	where ->next = ourNode;

	//these two lines are for debugging only
	nodeCount++;
	console() << nodeCount << endl;
}

/*
 *this method deletes the last node added to the list unless it is the sentinel node
*/
void brammejd_HW02App::Delete(node* deleteMe){
	if(deleteMe->shape == NULL){
		console() << "At Sentinel Node" << std::endl;
	} else {
		currentX = deleteMe->shape->startX;
		currentY = deleteMe->shape->startY;
		node* tempPrev = deleteMe->prev;
		node* tempNext = deleteMe->next;
		tempPrev->next = tempNext;
		tempNext->prev = tempPrev;
	    delete deleteMe;

		//these two lines are for debugging only
		nodeCount--;
		console() << nodeCount << std::endl;
	}
}

/*
 *@param xValue x value of mouse click
 *@param yValue y value of mouse click
 *deleteShape was an attempt at deleteing a shape that was clicked on.
 *however, it locked up the program everytime and did not complete its task as intended
 *even though I will not get this in before the due date I'd like to work out whatever bug is stopping it from working
 */
void brammejd_HW02App::deleteShape(int xValue, int yValue){
	node* cur = sentinel->next;
	while(cur->shape != NULL){
		bool willDelete = cur->shape->mouseOverShape(xValue, yValue);
		if(willDelete){
			node* prevNode = cur->prev;
			node* nextNode = cur->next;
			delete cur;
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}
	}
}

/*
 *this method resets the background to white
 *without this method any deleted nodes would still show up on the screen even though they are logically deleted
*/
void resetBackground(uint8_t* dataArray, Color8u BGColor){
	for(int i = 0; i < AppHeight; i++){
		for(int j = 0; j < AppWidth; j++){
			int offset = 3*(j + i*TEXTURESIZE);
			dataArray[offset] = BGColor.r;
			dataArray[offset+1] = BGColor.g;
			dataArray[offset+2] = BGColor.b;
	
		}
	}
}

/*
 *this method reverses the order of the doubly linked list
 *even if the list only has the sentinel node it will still swap the logical pointers
*/
void brammejd_HW02App::reverseList(node* reverseMe){
	node* currentNode = reverseMe;
	do{
		node* temp = currentNode->next;
		currentNode->next = currentNode->prev;
		currentNode->prev = temp;
		currentNode = currentNode->prev;
	} while(currentNode != reverseMe);
}

void brammejd_HW02App::mouseDown( MouseEvent event )
{	
	//Delete() method is called if the left mouse button is clicked
	if(event.isLeftDown()){
		Delete(sentinel->next);
		//deleteShape(event.getX(), event.getY());
	}
	//reverseList() method is called if the right mouse button is clicked
	if(event.isRightDown()){
		reverseList(sentinel);
	}
}

/*
 *the arrow keys will call insertAfter making a new node and putting a new rectangle inside that node with random properties
 *but the direction in which they are made will move the direction pressed with some variation
 *
 *the w,a,s,d keys will call insertAfter making a new node and putting a new circle inside that node with random properties
 *but the direction in which they are made will move in the direction pressed (same format as the arrow keys) with variation
 *
 *the ? key will show or hide the instruction menu
*/
void brammejd_HW02App::keyDown( KeyEvent event ){
	if(event.getCode() == KeyEvent::KEY_RIGHT){
		if(currentX <= 770 && currentY <= 570){
			currentX += rand.nextInt(19)+1;
			currentY += rand.nextInt(20)-10;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_LEFT){
		if(currentX > 20 && currentY > 10){
			currentX -= rand.nextInt(19)+1;
			currentY -= rand.nextInt(20)-10;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_UP){
		if(currentX > 10 && currentY > 20){
			currentX -= rand.nextInt(20)-10;
			currentY -= rand.nextInt(19)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_DOWN){
		if(currentX < 760 && currentY < 550){
			currentX += rand.nextInt(20)-10;
			currentY += rand.nextInt(19)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getChar() == '?'){
		if(showInstructions){
			showInstructions = false;
		} else {
			showInstructions = true;
		}
	} else if(event.getChar() == 'w'){
		if(currentX < 760 && currentY < 550){
			currentX -= rand.nextInt(20)-10;
			currentY -= rand.nextInt(19)+1;
			insertAfter(sentinel, new Circle(rand.nextInt(14)+1, currentX, currentY, new Color8u(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getChar() == 'a'){
		if(currentX > 15 && currentY > 15){
			currentX -= rand.nextInt(19)+1;
			currentY -= rand.nextInt(20)-10;
			insertAfter(sentinel, new Circle(rand.nextInt(14)+1, currentX, currentY, new Color8u(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getChar() == 'd'){
		if(currentX < 750 && currentY < 560){
			currentX += rand.nextInt(19)+1;
			currentY += rand.nextInt(20)-10;
			insertAfter(sentinel, new Circle(rand.nextInt(14)+1, currentX, currentY, new Color8u(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getChar() == 's'){
		if(currentX < 760 && currentY < 550){
			currentX += rand.nextInt(20)-10;
			currentY += rand.nextInt(19)+1;
			insertAfter(sentinel, new Circle(rand.nextInt(14)+1, currentX, currentY, new Color8u(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255)), rand.nextBool()));
		}
	}
}

void brammejd_HW02App::setup()
{
	//here is our texture that holds our instruction image
	texture = loadImage( "instruction_image.jpg" );
	
	//our background color is defined here
	BGColor = Color8u(255,255,255);

	//the initial state of showInstructions means the menu will be shown at least once
	showInstructions = true;

	//the current values of x and y will determine where a shape is drawn, we start in the middle
	currentX = AppWidth/2;
	currentY = AppHeight/2;

	//this is the setup for our sentinel node; we have a doubly linked list so the initial next and prev points point to the sentinel node
	sentinel = new node;
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	//for looping purposes the sentinel's shape must always be NULL so loops know where to stop
	sentinel->shape = NULL;

	//these two lines of code initialize our modifiable surface and instantiate dataArray to contain the pixel information in surface
	mySurface = new Surface(TEXTURESIZE, TEXTURESIZE, false);
	dataArray = mySurface->getData();
	
	//nodeCount is for debugging only
	nodeCount = 0;
}

void brammejd_HW02App::update()
{
	//Must continuously reset entire background to black to avoid possibly logically deleted shapes from appearing
	resetBackground(dataArray, BGColor);

	//this loop goes through all the nodes and calls the draw function of each shape
	//this is probably the most important loop in the entire program as it actually draws how the linked list is organized logically
	//cur must initially be set to sentinel->next to make sure the loop executes at all
	node* cur = sentinel->next;
	while(cur->shape != NULL){
		cur->shape->draw(dataArray);
		cur = cur->next;
	}
}

void brammejd_HW02App::draw()
{
	gl::draw(*mySurface);
	//this if statement determines if the user wants to see the instructions
	if(showInstructions){
		gl::draw( texture );
	}
}

CINDER_APP_BASIC( brammejd_HW02App, RendererGl )
