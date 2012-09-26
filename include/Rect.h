#include "cinder/Color.h"
#include "Shape.h"

using namespace ci;

/*
 *the rectangle class holds everything needed for rectangle parameters and its ability to draw itself
 */
class Rect : public Shape
{
public:
	Rect(int rectHeight, int rectLength, int startX, int startY, Color8u* c, bool fill);
	void draw(uint8_t* dataArray);
	bool mouseOverShape(int xValue, int yValue);
	int startX;
	int startY;
private:
	int rectHeight;
	int rectLength;
	Color8u* c;
	bool fill;
};

/*
 *@param rectHeight rectangle height
 *@param rectLength rectangle length
 *@param startX top left X value
 *@param startY top left Y value
 *@param c Color8u color representation for the rectangle
 *@param fill boolean value that determines if the rectangle is filled or not
 */
Rect::Rect(int rectHeight, int rectLength, int startX, int startY, Color8u* c, bool fill)
{
	this->rectHeight = rectHeight;
	this->rectLength = rectLength;
	this->startX = startX;
	this->startY = startY;
	this->c = c;
	this->fill = fill;
}

/*
 *@param dataArray the array of pixels that need to be modified by the method in order to draw the rectanlge
 */
void Rect::draw(uint8_t* dataArray)
{
	//static variables are required to preserve the original dimensions as we decrement in the for loop
	int staticHeight = rectHeight;
	int staticLength = rectLength;

	for(int i = startY; i <= startY + staticHeight; i++){
		if(rectHeight >= 0){
			for(int j = startX; j <= startX + staticLength; j++){
				if(rectLength >= 0){
					if(fill){ //Will draw a solid rectangle
						if(i >= startY || i <= startY + staticHeight || j >= startX || j <= startX + staticLength){
							int offset = 3*(j + i*TEXTURESIZE);
							dataArray[offset] = c->r;
							dataArray[offset+1] = c->b;
							dataArray[offset+2] = c->g;
							rectLength--;
						}
					} else { //Will draw the perimeter of a rectangle
						if(i == startY || i == startY + staticHeight || j == startX || j == startX + staticLength){
							int offset = 3*(j + i*TEXTURESIZE);
							dataArray[offset] = c->r;
							dataArray[offset+1] = c->b;
							dataArray[offset+2] = c->g;
							rectLength--;
						}
					}
				}
			}
			rectLength = staticLength;
			rectHeight--;
		}
	}
	//I hate this next line of code
	//The reason is that it wasn't in my HW01 because I didn't need to reset the rectHeight variable because it wasn't needed after the rectangle was drawn
	//Basically, I wasted 2+ hours of coding time because rectHeight was negative by the time it got through this. that meant that it wouldn't draw again
	//because the first if statement asks if(rectHeight >=0) which would be negative at the second passthrough
	//Mike, if you're reading this, thank you for bringing up the debugger and showing me that rectHeight was going negative. It's the only reason I figured it out.
	rectHeight = staticHeight;
}

/*
 *@param xValue x value to be tested
 *@param yValue y value to be tested
 *A helper method that returned a boolean value that would tell if a given x and y value were contained in the shape
 *its name was derived on the intended use but I couldn't work the bugs out in time
 */
bool Rect::mouseOverShape(int xValue, int yValue){
	if(xValue >= startX && xValue <= startX + rectLength &&
	   yValue >= startY && yValue <= startY + rectHeight){
		return true;
	} else {
		return false;
	}
}