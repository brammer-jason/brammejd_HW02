#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;


struct node {
	node* next;
	int x;
};
typedef node *link;

class brammejd_HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);	

  private:
	void insertAfter(node **whereTo, int value);
	void DeleteAfter(node *afterMe);

	Surface* mySurface;
	static const int AppWidth = 800;
	static const int AppHeight = 600;
	static const int TextureSize = 1024;
	int frameNumber;
};

void brammejd_HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(AppWidth, AppHeight);
	(*settings).setResizable(false);
}

void brammejd_HW02App::insertAfter(node *whereTo , int value){
	node* ourNode = new node;
	ourNode ->x = value;
	ourNode ->next = whereTo ->next;
	whereTo ->next = ourNode;
}

void brammejd_HW02App::DeleteAfter(node* afterMe){
	node *temp = NULL;
	temp = afterMe->next;
    afterMe->next = afterMe->next->next;
    delete temp;
    temp=NULL;
}

void brammejd_HW02App::setup()
{
	mySurface = new Surface(TextureSize, TextureSize, false);
	frameNumber = 0;
	

}

void brammejd_HW02App::mouseDown( MouseEvent event )
{
}

void brammejd_HW02App::update()
{
	node *sentinel = NULL;
	insertAfter(sentinel, 4);
}

void brammejd_HW02App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
	gl::draw(*mySurface);
}

CINDER_APP_BASIC( brammejd_HW02App, RendererGl )
