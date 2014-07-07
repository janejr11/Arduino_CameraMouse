Arduino_CameraMouse
===================

Arduino Leonardo + Sunkee VGA OV7670 based mouse movement through color tracking

Arduino IDE file and accompanying classes used to capture images, track a coloured object,
and move the mouse around a computer screen according to the position of the tracked
object.

__________________________________________________________________________________________
Update history:

6/23/14:
	First commit of all .ino .h and .cpp files to Github. 
	Waiting on hardware to fully debug.
	
6/24/14:
	Edited Calibrate method in Mouse_Controller.ino to use floats for higher precision
	in tracking. 

6/27/14:
	Debugged most of the driver.read() method. Errors present in the frame.readWord() method.

7/3/14:
	Need to test incoming frames for completion, Arduino crash on initialization of pixel 
	objects when the driver is declared (look within pixel.cpp)
	
7/7/14:
	Edited testing method to check boolean "edited" private member variable of pixel. Untested
	on Arduino, (may not provide solution). Redefined the byte class and replaced all 'uint8_t'
	with 'byte' for clarity .No problems compiling, untested on device. edited testing method 
	in frame. Added testing method to line (method cascade)
	
	
	
	
	
	
	
	
	