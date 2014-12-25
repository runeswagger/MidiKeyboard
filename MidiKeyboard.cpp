#include "MidiKeyboard.h"
#include "MidiKeyboardC.h"

//create and instance for the user to use
Midi_Keyboard MidiKeyboard;

void Midi_Keyboard::begin(){
	//start the usb driver
	usbBegin();
}

void Midi_Keyboard::poll(){
	//make sure you poll every 50ms or faster to avoid timeouts
	usbPollWrapper();
}

char Midi_Keyboard::sendMidiEventPacket(char event[4]){
	//send 1 packet of midi
	usbSend(event, 4);
	return 0;
}

char Midi_Keyboard::sendMidi(char cableid, char msgtype, char midicmd, char mididata1, char mididata2){
	char buffer[4] = {
		((cableid<<4)|(msgtype)),
		midicmd,
		mididata1,
		mididata2,
	};

	return sendMidiEventPacket(buffer);
}
