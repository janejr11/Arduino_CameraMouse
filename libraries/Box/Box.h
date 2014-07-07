#ifndef boxHeader
#define boxHeader

#include "Coordinates.h"
#include "Driver.h"
#include "Frame.h"
#include "Arduino.h"

#ifndef byte
#define byte uint8_t
#endif

class Box{

	private:
	int xCenter;
	int yCenter;
	int xMax;
	int yMax;
	int xMin;
	int yMin;
	public:
	// constructors
	Box();
	Box(int xCentert, int yCentert, int xMaxt, int xMint, int Ymaxt,int yMint);

	// mutators
	void setXCenter(int xCentert);
	void setYCenter(int yCentert);
	void setXMax (int xMaxt);
	void setYMax (int yMaxt);
	void setXMin (int xMint);
	void setYMin (int yMint);

	//accessors
	int getXCenter();
	int getYCenter();
	int getXMax();
	int getXMin();
	int getYMax();
	int getYMin();

	// methods
	
	// calibrates the central location of the point and the maximum and minimum values
	// used to determine the magnitude of mouse movement
	void calibrate(Driver dr,byte targetR, byte targetG, byte targetB,
				   byte rTolerance, byte gTolerance, byte bTolerance);
	void moveMouse(Coordinates point);
	
};

#endif