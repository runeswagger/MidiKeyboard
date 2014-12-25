/* Make sure the C side of MidiKeyboard works as expected */
#include "MidiKeyboardC.h"

volatile char noteArray[2][4] = {
	{ 0x09, 0x90, 69, 0x7f }, //note on A
	{ 0x08, 0x80, 69, 0x00 }
};

unsigned char current, last;

int main(){
	usbBegin();
	current = 0;
	last = 0;

	DDRB &= ~(1<<0);
	PORTB |= (1<<0);
	
	while(1){
		usbPollWrapper();

		current = (PINB&1); //grab bit 0 of portb
		
		if(current != last){
			if(!current){ //button is pressed
				usbSend(noteArray[0], 4);
			} else {
				usbSend(noteArray[1], 4);
			}
		}
		
		last = current;
	}
	
	return 0;
}
