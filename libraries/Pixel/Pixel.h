#ifndef pixelHeader
#define pixelHeader

// Pixel class to populate the lines of frames
class Pixel{

	private:
	//RGB and YCbCr values
	int r,g,b,y,cb,cr;
	
	public:
	// constructors
	Pixel(int yt,int cbt,int crt);
	Pixel();
	
	// methods
	// mutators
	void setData(int yt, int cbt, int crt);
	void sety(int yt);
	void setcb(int cbt);
	void setcr(int crt);
	// accessors
	int getR();
	int getG();
	int getB();
	// convert method to convert from YCbCr to RGB
	void convert();
};
#endif