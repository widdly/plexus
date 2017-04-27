 [overview](index.md) | [hardware](hardware.md) | user guide
 
## user guide


#### mode
The right hand side round buttons select and indicate the current mode.


The modes are playback, record, edit and tempo.  The bottom 4 mode buttons are unassigned in current firmware.  Only a single mode can be selected at any time and the currently selected mode will be lit green.

![launchpad_main_layout](https://cloud.githubusercontent.com/assets/7449649/25469055/483136ca-2b5d-11e7-9ef6-2b535ab51923.png)

####  channel  selection and hold 
The top row of round buttons are used to enable/disable hold and to select the current channel.


The top left four buttons are for enabling/disabling hold on each of the four channels.  The buttons will be lit orange when hold is engaged.  Any sequence on a channel will loop while hold is enabled, and stop looping once hold is disengaged.


The top right four buttons select the current channel.  Only one channel can be selected at a time and the current selected channel button will be lit green.  The playback, record and edit modes operate on the currently selected channel.


####  playback
In playback mode, pressing one of the square buttons will start the sequence playing.  The currently playing note will be illuminated in green.   Releasing the button will stop the sequence, unless hold is enabled for the channel.


The sequence’s starting note will depend on the button location according to the following layout.

![launchpad_note_layout](https://cloud.githubusercontent.com/assets/7449649/25468712/0e7cd7ce-2b5b-11e7-8d8c-a19fbfa2f498.png)

The sequence is shifted according to the grid location and diatonically transposed.  If any part of the sequence extends beyond the edge of the grid it will wrap around and be shifted up or down accordingly.  


A future firmware version will implement additional heptatonic scales, besides the major scale.



####  record
Record mode is used to record a new sequence.  The first square button pushed records the starting note of the sequence.  Subsequent notes are recorded relative to the starting note.  The current step and sequence length is indicated by a horizontal red bar along the bottom row of the button matrix.  Sequences can be up to 8 steps long.


####  edit
Using edit mode, the rhythm of the sequence can be edited to include long and short notes, rests and different length repetitions.


The edit screen is divided into three sections.  Each step in the sequence is represented by a column on the button matrix.

![launchpad_edit_mode](https://cloud.githubusercontent.com/assets/7449649/25468713/0e81f1aa-2b5b-11e7-9a73-3ad208977fea.png)

The top 6 rows control the step lengths.  Each step can be from 1 to 6 clock ticks in length. The length will display as 1 to 6 vertical orange lights and pressing the appropriate button will change the steps length.


The 7th row controls whether the step will send a gate out.  If the button is lit green then a gate signal will occur when that step is played.  Pressing the appropriate button will toggle the gate out setting.


The bottom row controls the sequence length.  The current length is indicated by the number of red lit buttons.  Pressing the left most bottom row button sets the length to 1, pressing the right most bottom row button sets the length to 8, and so on.


####  tempo
The tempo mode displays the current tempo in BPM.  The bottom row of buttons can be used to vary the tempo.  The second bottom row provides a clock divider that effects all the channels.  
The right most button on the second bottom row can be used to switch between the internal metronome and an external clock source.  The external clock source is not handled in the current firmware.

