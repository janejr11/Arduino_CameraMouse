#ifndef driverImp
#define driverImp

#include "Arduino.h"
#include "Driver.h"


Driver::Driver(int heightt, int widtht): height (heightt), width (widtht), imageComplete (false), pasth (1), pastv (0), pastp(1)
{

	image = new Frame(heightt,widtht);
	
    int prescale[] = {0,1,8,64,256,1024}; // the range of prescale values
    
    // If you instantiate these incorrectly the program might begin collecting data in the middle of a frame
    //pasth = HIGH; // to test whether you have reached the falling/rising edge
    //pastv = LOW;  // to test whether you have reached the falling/rising edge
    //pastp = LOW;  // to test whether you have reached the falling/rising edge
	
	// digital pinModes
    pinMode(d0,INPUT);
    pinMode(d1,INPUT);
    pinMode(d2,INPUT);
    pinMode(d3,INPUT);
    pinMode(d4,INPUT);
    pinMode(d5,INPUT);
    pinMode(d6,INPUT);
    pinMode(d7,INPUT);
    pinMode(vSync,INPUT);
    pinMode(hSync,INPUT);
    pinMode(pClk,INPUT);
    pinMode(sccbClk,OUTPUT);
    pinMode(sccbD,OUTPUT);
    pinMode(sysClk,OUTPUT);
    

	// supply clock pulse to camera: SCCB and Sys
    Timer1.initialize(period);
    //Timer1.pwm(sccbClk,duty);
    Timer1.pwm(sysClk,duty);
	
}

Frame Driver::getFrame(){
	return *image;
}

void Driver::read(){
	unsigned int data; // used to hold data from pins
	imageComplete = 0; // if end of the frame, this will be updated before function return
	v = digitalRead(vSync);
	//Serial.print("V: ");
	//Serial.println(v);
	if (v == LOW && pastv == HIGH){ // beginning of a new frame (falling edge of vertical sync)
		Serial.println("In new frame");
		Serial.flush();
		while (v==LOW){ // continue reading lines until the frame is fully constructed
			//Serial.println("Continuing to read frame");
			//Serial.flush();
			h = digitalRead(hSync);
			if (h == HIGH && pasth == LOW){ // beginning of a new row
				//Serial.println("Beginning new row");
				//Serial.flush();
				while( h== HIGH ){ // continue reading every pixel until you have constructed the full row
					p = digitalRead(pClk);
					if (p == HIGH && pastp == LOW){ // read a byte of data and add it to the row
						//Serial.println("Reading word");
						//Serial.flush();
						// read in the data from the pins using binary math
						data = readPins(d0,d1,d2,d3,d4,d5,d6,d7);
						(*image).readWord(data);
					}
				pastp = p;
				h = digitalRead(hSync);
				}
			}
			pasth = h;
			v = digitalRead(vSync);
		}
		imageComplete = true;
	}
	pastv = v;
} // end of read

bool Driver::isImageComplete(){
	if (imageComplete == true)
		return true;
	else
		return false;
}

unsigned int Driver::readPins(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7){
    unsigned int data = 0;
    if (digitalRead(d0) == HIGH)
        data = data + 1;
    if (digitalRead(d1) == HIGH)
		data = data + 2;
    if (digitalRead(d2) == HIGH)
		data = data + 4;
    if (digitalRead(d3) == HIGH)
		data = data + 8;
    if (digitalRead(d4) == HIGH)
		data = data + 16;
    if (digitalRead(d5) == HIGH)
		data = data + 32;
    if (digitalRead(d6) == HIGH)
		data = data + 64;
    if (digitalRead(d7) == HIGH)
		data = data + 128;
    return data;
}

#endif