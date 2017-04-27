 [overview](index.md) | hardware | [user guide](userguide.md)
 
## hardware 

A prototype version of the plexus hardware has been built in order to test and refine the concept.  The prototype was built on perfboard and housed in a guitar pedal enclosure.  Future work will include a pcb and panel layout according to the eurorack modular standard.

The hardware consists of a usb midi host, a teensy 3.2 microcontroller, 4 channels of 12 bit DAC, 5 transistor driven gate outputs and 1 gate input.  

![plexus internals ](https://cloud.githubusercontent.com/assets/7449649/25435266/cbf03f64-2ad2-11e7-81c3-1e9679fff9b8.jpg)
##### power
A 7805 regulator is used to supply 5v to the device.  In the prototype this is fed from a standard 9v guitar plug pack.  It should be possible to power this from the +12v rail of a eurorack system.  The regulator should probably include a heat sink given that the launchpad can draw 500mA via the USB port.
![7805 power](https://cloud.githubusercontent.com/assets/7449649/25435980/389c32f6-2ad5-11e7-95d2-7f6d99634eb5.jpg)

##### usb midi host
The novation launchpad is a class compliant usb midi device.  The plexus interfaces to the launchpad via a [hobbytronics usb host mini](http://www.hobbytronics.co.uk/usb-host/usb-host-mini) (the blue pcb in the photo).  It outputs standard serial midi rx/tx directly to the teensy uart.  The usb host mini is powered by 5v from the 7805 and feeds 5v at up to 500mA to the novation launchpad via USB.
##### teensy 3.2
A [teensy 3.2](https://www.pjrc.com/store/teensy32.html) provides the smarts for the plexus.  The source in the github repo can be built and uploaded using the standard (horrible) arduino ide.
##### gate in/out
The gate outputs are driven from the teensy output pins via a transistor to give standard 5v gate signals.

##### MCP4822 DAC
A pair of MCP4822 are driven via SPI by the teensy.  [datasheet](https://www.abelectronics.co.uk/docs/stock/raspberrypi/adcdac/mcp4822.pdf)

A MCP6004 quad opamp scales the analog output to give the correct 1v/oct.  Trimmers are provided to calibrate the outputs.


Schematics coming shortly.
