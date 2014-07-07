#ifndef frameHeader
#define frameHeader

#include "Line.h"
#include "Pixel.h"
#include "Coordinates.h"
#include "Arduino.h"

#ifndef byte
#define byte uint8_t
#endif

class Frame{

	private:
	int height;
	int width;
	// dynamic array to hold the 'spine' (left column of the image)
	Line *spine;
	// dynamic array that holds a partially constructed array,
	// it is moved to the 'spine' whenever the frame is completed
	Line *build;
	
	// iterators for parsing the data received as words
	int lineNum;
	int pixNum;
	int byteNum;
	
	// data holders for constructing pixels
	byte yA; // Y of pixel A
	byte yB; // Y of pixel B
	// cb and cr of both pixel A and B
	byte cb;
	byte cr;
	
	public:
	// constructors
	Frame(int heightt, int widtht);
	Frame();
	
	//accessors
	Line *getSpine(); // used to extract the image
	int getHeight();
	int getWidth();
	
	// methods
	// keystone method that parses and interprets data passed from the driver
	void readWord(byte data);
	
	Coordinates locate(byte targetR, byte targetG, byte targetB,
						  byte rTolerance, byte gTolerance, byte bTolerance);
						  
	// tests if the frame is completely constructed, returns true if good frame, false if incomplete
	bool testFrame();
	
	void convert();
};
#endif



