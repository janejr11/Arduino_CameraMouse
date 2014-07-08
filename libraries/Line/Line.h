#ifndef lineHeader
#define lineHeader

#include "Arduino.h"
#include "Pixel.h"

#ifndef byte
#define byte uint8_t
#endif

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
	// destructor
	~Line();
	
	//accessors
	Pixel *getLine();
	byte getPixelR(int i);
	byte getPixelG(int i);
	byte getPixelB(int i);
	int getWidth();
	
	//mutators
	void setPixelY(int i, byte y);
	void setPixelCb(int i, byte cb);
	void setPixelCr(int i, byte cr);
	void setPixelData(int i, byte r, byte g, byte b);
	
	// methods
	// convert method that iterates along each pixel in the line and
	// converts to RGB from YCbCr
	void convert();
	// sets width and initializes pixel array
	void setWidth(int widtht);
	// tests whether the line is completely filled by testing last pixel
	bool isEdited();
};
#endif