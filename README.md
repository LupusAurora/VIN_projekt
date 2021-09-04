# VIN_projekt

A simple project for a suject focused on I/O devices at my University.

I made an Arduino based fan controller, using a ULN2003APG chip as a motor driver.
Speed is controlled by choping up the supply volage to the motor with PWM.
To set the speed you can use a potentiometer or send a desired value over serial port.
Another Arduino is connected via serial communication that can display current motor speed on a 4 digit 7-segment display remotely.
