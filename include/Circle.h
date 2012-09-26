#include "cinder/Color.h"
#include "Shape.h"
using namespace ci;

/*
 *the circle class holds everything needed for the rectangle parameters and its ability to draw itself
 */
class Circle : public Shape 
{
public:
	Circle(int radius, int startX, int startY, Color8u* c, bool fill);
	void draw(uint8_t* dataArray);
	bool mouseOverShape(int xValue, int yValue);
	int startX;
	int startY;
private:
	int radius;
	Color8u* c;
	bool fill;
};

/*
 *@param radius the radius of the circle
 *@param startX x coordinage for the middle of the circle
 *@param startY y coordinate for the middle of the circle
 *@param c Color8u color representation for the circle
 *@param fill boolean value that determines if the circle is filled or not
 */
Circle::Circle(int radius, int startX, int startY, Color8u* c, bool fill){
	this->radius = radius;
	this->startX = startX;
	this->startY = startY;
	this->c = c;
	this->fill = fill;
}

/*
 *@param dataArray the array of pixels that need to be modified by the method in order to draw the circle
 */
void Circle::draw(uint8_t* dataArray){
	if(fill){ //Will fill the circle
		for(int i = startY-radius; i<=startY+radius; i++){
			for(int j = startX-radius; j <= startX+radius; j++){
				int distance = (int)sqrt((double)((j - startX)*(j-startX) + (i - startY)*(i - startY)));
				if(distance <= radius){
					int offset = 3*(j + i*TEXTURESIZE);
					dataArray[offset] = c->r;
					dataArray[offset+1] = c->g;
					dataArray[offset+2] = c->b;
					
				}
			}
		}
	} else { //Will draw only the circumference of the circle
		for(int i = startY-radius; i<=startY+radius; i++){
			for(int j = startX-radius; j <= startX+radius; j++){
				int distance = (int)sqrt((double)((j - startX)*(j-startX) + (i - startY)*(i - startY)));
				if(distance <= radius){
					if(distance%radius < 1 && distance > 9){
						int offset = 3*(j + i*TEXTURESIZE);
						dataArray[offset] = c->r;
						dataArray[offset+1] = c->g;
						dataArray[offset+2] = c->b;
					}
				}
			}
		}
	}
}

/*
 *@param xValue x value to be tested
 *@param yValue y value to be tested
 *A helper method that returned a boolean value that would tell if a given x and y value were contained in the shape
 *its name was derived on the intended use but I couldn't work the bugs out in time
 */
// **Changed to limit its bounds to the circle itself, rather than a square around the circle
bool Circle::mouseOverShape(int xValue, int yValue){
	//if(xValue < startX + radius && xValue > startX - radius && 
	//   yValue < startY + radius && yValue > startY - radius){
	//	return true;
	//} else {
	//	return false;
	//}

	//**Copied from my code
	int dist = math<double>().sqrt((startX - xValue) * (startX - xValue) + (startY - yValue) * (startY - yValue));
	if(dist <= radius)
		return true;
	else
		return false;
}