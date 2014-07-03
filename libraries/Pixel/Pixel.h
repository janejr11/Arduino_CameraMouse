#ifndef pixelHeader
#define pixelHeader

#include "Arduino.h"

// Pixel class to populate the lines of frames
class Pixel{

	private:
	//RGB and YCbCr values
	uint8_t r,g,b,y,cb,cr;
	
	public:
	// constructors
	Pixel(uint8_t yt,uint8_t cbt,uint8_t crt);
	Pixel();
	
	// methods
	// mutators
	void setData(uint8_t yt, uint8_t cbt, uint8_t crt);
	void sety(uint8_t yt);
	void setcb(uint8_t cbt);
	void setcr(uint8_t crt);
	// accessors
	uint8_t getR();
	uint8_t getG();
	uint8_t getB();
	// convert method to convert from YCbCr to RGB
	void convert();
};
#endif