#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;


struct node {
	node* next;
	node* prev;
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
	void insertAfter(node *where, int value);
	void DeleteAfter(node *afterMe);
	void displayInfo(node *sentinel);

	Surface* mySurface;
	static const int AppWidth = 800;
	static const int AppHeight = 600;
	static const int TextureSize = 1024;
	int frameNumber;
	node* sentinel;
};

void brammejd_HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(AppWidth, AppHeight);
	(*settings).setResizable(false);
}

void brammejd_HW02App::insertAfter(node* where , int value){
	
	node* ourNode = new node;
	where->next->prev = ourNode;
	ourNode ->x = value;
	ourNode ->next = where ->next;
	ourNode ->prev = where;
	where ->next = ourNode;
}

void brammejd_HW02App::DeleteAfter(node* afterMe){
	node *temp = NULL;
	temp = afterMe->next;
    afterMe->next = afterMe->next->next;
    delete temp;
    temp=NULL;
}

void brammejd_HW02App::displayInfo(node *sentinel){
	sentinel = sentinel->next;
	while(sentinel->x != NULL){
		console() << sentinel->x << std::endl;
		sentinel = sentinel->next;
	}
	
}

void brammejd_HW02App::setup()
{
	sentinel = new node;
	sentinel->next = sentinel;
	sentinel->x = NULL;
	sentinel->prev = sentinel;

	mySurface = new Surface(TextureSize, TextureSize, false);
	frameNumber = 0;
	
	insertAfter(sentinel, 10);
	insertAfter(sentinel, 20);
	insertAfter(sentinel, 30);
	displayInfo(sentinel);
}

void brammejd_HW02App::mouseDown( MouseEvent event )
{
}

void brammejd_HW02App::update()
{

}

void brammejd_HW02App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
	gl::draw(*mySurface);
}

CINDER_APP_BASIC( brammejd_HW02App, RendererGl )
