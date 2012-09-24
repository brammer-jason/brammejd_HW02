#pragma once

using namespace ci;

/*
 *this is the super class for rect and circle
 *the only two variables that Circle and Rect share are their startX and startY
 *the only methods they share are draw() and mouseOverShape()
 *mouseOverShape was to be used as a helper method for single node deletion but a bug in the actual deletion has rendered it useless at the moment
*/
class Shape {
public:
	virtual void draw(uint8_t* dataArray) = 0;
	virtual bool mouseOverShape(int xValue, int yValue) = 0;
	int startX, startY;
};
		