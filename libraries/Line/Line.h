#ifndef lineHeader
#define lineHeader

#include "Arduino.h"
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
	uint8_t getPixelR(int i);
	uint8_t getPixelG(int i);
	uint8_t getPixelB(int i);
	int getWidth();
	
	//mutators
	void setPixelY(int i, uint8_t y);
	void setPixelCb(int i, uint8_t cb);
	void setPixelCr(int i, uint8_t cr);
	void setPixelData(int i, uint8_t r, uint8_t g, uint8_t b);
	
	// methods
	// convert method that iterates along each pixel in the line and
	// converts to RGB from YCbCr
	void convert();
	// sets width and initializes pixel array
	void setWidth(int widtht);
};
#endif