#include "MidiKeyboard.h"
#include "MidiKeyboardC.h"

void _MidiKeyboard::begin(){
	//start the usb driver
	usbBegin();
}

void _MidiKeyboard::poll(){
	//make sure you poll every 50ms or faster to avoid timeouts
	usbPollWrapper();
}

char _MidiKeyboard::sendMidiEventPacket(char event[4]){
	//send 1 packet of midi
	usbSend(event, 4);
	return 0;
}

char _MidiKeyboard::sendMidi(char cableid, char msgtype, char midicmd, char mididata1, char mididata2){
	char buffer[4] = {
		((cableid<<4)|(msgtype)),
		midicmd,
		mididata1,
		mididata2,
	};

	return sendMidiEventPacket(buffer);
}
