#ifndef boxHeader
#define bodHeader

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

};

#endif