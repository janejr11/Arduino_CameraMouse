#ifndef driverHeader
#define driverHeader

#include "Arduino.h"
#include "Pixel.h"
#include "Line.h"
#include "Frame.h"
#include "TimerOne.h"


class Driver{
	private:
    // pin descriptions
    // DIGITAL
    // 0 - d0
    // 1 - d1
    // 2 - d2
    // 3 - d3
    // 4 - d4
    // 5 - d5
    // 6 - d6
    // 7 - d7
    // 8 - sccbData
    // 9 - verticalSync
    // 10 - systemClock
    // 11 - sccbClock
    // 12 - horizontalSync
    // 13 - pixelClock
    
    // ANALOG
    // 0 - powerDown // active high
    // 1 - reset // active low
    
    // pin declarations
    static const int d0 = 0;
    static const int d1 = 1;
    static const int d2 = 2;
    static const int d3 = 3;
    static const int d4 = 4;
    static const int d5 = 5;
    static const int d6 = 6;
    static const int d7 = 7;
    static const int sccbD = 8;
    static const int vSync = 9;
    static const int sysClk = 10;
    static const int sccbClk = 11;
    static const int hSync = 12;
    static const int pClk = 13;
    

    // Clock Pulse (TimerOne) Driver necessities
    static const char SET_PERIOD_HEADER      = 'p';
    static const char SET_FREQUENCY_HEADER   = 'f';
    static const char SET_PULSE_WIDTH_HEADER = 'w';
    static const char SET_DUTY_CYCLE_HEADER  = 'c';
    
    // I dont understand this next line so I'm commenting it out for now
    #define pwmRegister OCR1A      // the logical pin, can be set to OCR1B
    static const int   outPin =  sysClk;     // the physical pin
    static const int   outPin2 =  sccbClk;     // the physical pin
    
    static const long period = 1;        // the period in microseconds
    static const int duty = 512;         // duty as a range from 0 to 1024, 512 is 50% duty cycle
    // end Clock section
    
    
    // Frame that will be edited and output
    Frame *image;
    
    // frame data (dynamically allocated in the constructor)
    int height;
    int width;
    
    // defines the previous states of the hSync, vSync, pClk (used to collect data)
    int pasth;
    int pastv;
    int pastp;
    
    
    int imageComplete; // active at 1, inactive at 0

    
    // timing variables for collecting data
    int h; // Horizontal Sync (one HIGH state signifies each line)
    int v; // Vertical Sync (one LOW state signifies each frame)
    int p; // Pixel Clock (read one byte of info on rising edge)
    
    
    
    public:
    // constructors
    Driver();
    Driver(int heightt, int widtht);
    
    //accessors
    Frame getFrame();
    
    // methods
    bool isImageComplete();
    // Keystone method, reads data from the camera by reading the pin status
    void read();
    // simplifies the read() function by delegating binary math to separate function
    uint8_t readPins(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);

};

#endif