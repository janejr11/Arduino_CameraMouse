#ifndef coordinatesHeader
#define coordinatesHeader

#include "Arduino.h"

class Coordinates{
private:
int x;
int y;


public:
// accessors
int getX();
int getY();

// mutators
void setX(int xt);
void setY(int yt);


};

#endif