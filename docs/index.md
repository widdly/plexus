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
##### usb midi host
The novation launchpad is a class compliant usb midi device.  The plexus interfaces to the launchpad via a hobbytronics usb host mini ( http://www.hobbytronics.co.uk/usb-host/usb-host-mini ).  This is the blue pcb in the photo above.  It outputs standard serial midi rx/tx directly to the teensy uart.
