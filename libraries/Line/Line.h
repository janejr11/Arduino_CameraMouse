#ifndef lineHeader
#define lineHeader
#include "Pixel.h"

// Line class to serve as the rows of a frame
class Line{
	private:
	int width;
	// dynamic pixel array to hold pixels of the frame
	Pixel *pix;
	
	public:
	// constructors
	Line(int widtht);
	Line();
	
	//accessors
	Pixel *getLine();
	int getPixelR(int i);
	int getPixelG(int i);
	int getPixelB(int i);
	int getWidth();
	
	//mutators
	void setPixelY(int i, int y);
	void setPixelCb(int i, int cb);
	void setPixelCr(int i, int cr);
	void setPixelData(int i, int r, int g, int b);
	
	// methods
	// convert method that iterates along each pixel in the line and
	// converts to RGB from YCbCr
	void convert();
	// sets width and initializes pixel array
	void setWidth(int widtht);
};
#endif