#pragma once

#include "MainHeader.h"


using namespace ci;
using namespace ci::app;
using namespace std;

void brammejd_HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(AppWidth, AppHeight);
	(*settings).setResizable(false);
}

void brammejd_HW02App::insertAfter(node* where, Rect* newRect){
	
	node* ourNode = new node;
	where->next->prev = ourNode;
	ourNode ->rect = newRect;
	ourNode ->next = where ->next;
	ourNode ->prev = where;
	where ->next = ourNode;
}

void brammejd_HW02App::Delete(node* deleteMe){
	node* tempPrev = deleteMe->prev;
	node* tempNext = deleteMe->next;
	tempPrev->next = tempNext;
	tempNext->prev = tempPrev;
    delete deleteMe;
}

void brammejd_HW02App::displayInfo(node *sentinel){
	/*
	//step into the first node after sentinel or loop will not execute
	sentinel = sentinel->next;
	while(sentinel->x != NULL){
		console() << sentinel->x << std::endl;
		sentinel = sentinel->next;
	}
	*/
}

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

void brammejd_HW02App::setup()
{
	BGColor = Color8u(255,255,255);

	sentinel = new node;
	sentinel->next = sentinel;
	sentinel->rect = NULL;
	sentinel->prev = sentinel;

	mySurface = new Surface(TEXTURESIZE, TEXTURESIZE, false);
	frameNumber = 0;
	
	insertAfter(sentinel, new Rect(20, 20,  0,  0, new Color8u(0,0,0), true));
	insertAfter(sentinel, new Rect(20, 20, 10, 10, new Color8u(0,0,0), true));
	insertAfter(sentinel, new Rect(20, 20, 20, 20, new Color8u(0,0,0), true));
	insertAfter(sentinel, new Rect(20, 20, 30, 30, new Color8u(0,0,0), true));
}

void brammejd_HW02App::mouseDown( MouseEvent event )
{

}

void brammejd_HW02App::update()
{
	uint8_t* dataArray = mySurface->getData();
	//Must continuously reset entire background to black to avoid possibly logically deleted shapes from appearing
	resetBackground(dataArray, BGColor);

	for(node* currentNode = sentinel->next; currentNode->rect != NULL; currentNode = currentNode->next){
		currentNode->rect->drawRect(dataArray);
	}
}

void brammejd_HW02App::draw()
{
	gl::draw(*mySurface);
}

CINDER_APP_BASIC( brammejd_HW02App, RendererGl )
