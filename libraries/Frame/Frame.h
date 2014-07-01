#ifndef frameHeader
#define frameHeader
#include "Line.h"
#include "Coordinates.h"

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
	int yA; // Y of pixel A
	int yB; // Y of pixel B
	// cb and cr of both pixel A and B
	int cb;
	int cr;
	
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
	void readWord(unsigned int data);
	
	Coordinates locate(int targetR, int targetG, int targetB,
						  int rTolerance, int gTolerance, int bTolerance);
};
#endif



