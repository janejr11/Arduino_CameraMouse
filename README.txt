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
	Debugged most of the driver.read() method. Errors present in the frame.readWord() 		method.