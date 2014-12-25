#ifndef _MIDIKEYBOARD_H_
#define _MIDIKEYBOARD_H_

class MidiKeyboard {
	private:
	//a 2 event buffer because a low speed device can send up to 8 bytes in one transaction
	char midiEventBuffer[8];
	
	public:

	void begin();
	void poll();

	char sendMidi(char cableid, char msgtype, char midicmd, char mididata1, char mididata2);
	char sendMidiEventPacket(char event[4]);
};

#endif
