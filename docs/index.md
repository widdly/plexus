# plexus
## launchpad cv/gate sequencer/keyboard

plexus is a diy device that interfaces a novation launchpad to a teensy and provides 4 channels of cv/gate output.  

The software running on the teensy provides a 4 channel sequencer inspired by the monome polygome application.

![plexus hardware ](https://cloud.githubusercontent.com/assets/7449649/25432894/ae2e34f8-2ac9-11e7-8fee-1268903c134e.jpg)

### a quick demo

In the video, the plexus hardware is sequencing various cgs and serge modules.  No computer is involved.
<iframe width="560" height="315" src="https://www.youtube.com/embed/QyVMc5N7K9o" frameborder="0" allowfullscreen></iframe>


### hardware 

![plexus internals ](https://cloud.githubusercontent.com/assets/7449649/25435266/cbf03f64-2ad2-11e7-81c3-1e9679fff9b8.jpg)
##### power
A 7805 regulator is used to supply 5v to the device.  In the prototype this is fed from a standard 9v guitar plug pack.  It should be possible to power this from the +12v rail of a eurorack system.
![7805 power](https://cloud.githubusercontent.com/assets/7449649/25435980/389c32f6-2ad5-11e7-95d2-7f6d99634eb5.jpg)

##### usb midi host
The novation launchpad is a class compliant usb midi device.  The plexus interfaces to the launchpad via a [hobbytronics usb host mini](http://www.hobbytronics.co.uk/usb-host/usb-host-mini) (the blue pcb in the photo).  It outputs standard serial midi rx/tx directly to the teensy uart.
##### teensy 3.2
A [teensy 3.2](https://www.pjrc.com/store/teensy32.html) provides the smarts for the plexus.  The source in the github repo can be built and uploaded using the standard (horrible) arduino ide.
##### gate in/out
##### MCP4822 DAC
Schematics coming.
