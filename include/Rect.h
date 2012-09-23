#include "cinder/Color.h"

using namespace ci;

class Rect
{
public:
	Rect(int rectHeight, int rectLength, int startX, int startY, Color8u* c, bool fill);
	void drawRect(uint8_t* dataArray);
	int startX;
	int startY;
private:
	int rectHeight;
	int rectLength;
	//int startX;
	//int startY;
	Color8u* c;
	bool fill;
};

Rect::Rect(int rectHeight, int rectLength, int startX, int startY, Color8u* c, bool fill)
{
	this->rectHeight = rectHeight;
	this->rectLength = rectLength;
	this->startX = startX;
	this->startY = startY;
	this->c = c;
	this->fill = fill;
}

void Rect::drawRect(uint8_t* dataArray)
{
	
	//static variables are required to preserve the original dimensions as we decrement in the for loop
	int staticHeight = rectHeight;
	int staticLength = rectLength;


	for(int i = startY; i <= startY + staticHeight; i++){
		if(rectHeight >= 0){
			for(int j = startX; j <= startX + staticLength; j++){
				if(rectLength >= 0){
					if(fill){
						if(i >= startY || i <= startY + staticHeight || j >= startX || j <= startX + staticLength){
							int offset = 3*(j + i*TEXTURESIZE);
							dataArray[offset] = c->r;
							dataArray[offset+1] = c->b;
							dataArray[offset+2] = c->g;
							rectLength--;
						}
					} else {
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
	rectHeight = staticHeight; //I hate this line of code
	
}