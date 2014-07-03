#ifndef frameHeader
#define frameHeader

#include "Line.h"
#include "Pixel.h"
#include "Coordinates.h"
#include "Arduino.h"

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
	uint8_t yA; // Y of pixel A
	uint8_t yB; // Y of pixel B
	// cb and cr of both pixel A and B
	uint8_t cb;
	uint8_t cr;
	
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
	void readWord(uint8_t data);
	
	Coordinates locate(uint8_t targetR, uint8_t targetG, uint8_t targetB,
						  uint8_t rTolerance, uint8_t gTolerance, uint8_t bTolerance);
						  
	// tests if the frame is completely constructed, returns true if good frame, false if incomplete
	bool testFrame();
	
	void convert();
};
#endif



