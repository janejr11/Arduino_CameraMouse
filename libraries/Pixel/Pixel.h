#ifndef pixelHeader
#define pixelHeader

#include "Arduino.h"

#ifndef byte
#define byte uint8_t
#endif

// Pixel class to populate the lines of frames
class Pixel{

	private:
	//RGB and YCbCr values
	byte r,g,b,y,cb,cr;
	bool edited;
	
	public:
	// constructors
	Pixel(byte yt, byte cbt, byte crt);
	Pixel();
	
	// mutators
	void setData(byte yt, byte cbt, byte crt);
	void sety(byte yt);
	void setcb(byte cbt);
	void setcr(byte crt);
	
	// accessors
	byte getR();
	byte getG();
	byte getB();
	
	// methods
	// convert method to convert from YCbCr to RGB
	void convert();
	// test method returning whether the pixel was edited or not
	bool isEdited();
};
#endif