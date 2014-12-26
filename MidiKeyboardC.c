#include "cmdline_defs.h"
#include "MidiKeyboardC.h"
#include "descriptors_audio.h"
#include <avr/power.h>

#define MAX_TRANSFER_SIZE 8

usbMsgLen_t usbFunctionSetup(uchar data[8]){
	//implement the usb setup function for the driver
	usbRequest_t *rq = (void*)data; //cast data to usb request type for convienience
	//we would handle requests here, but not now, we just want enumeration
	if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {	/* class request type */

		/*  Prepare bulk-in endpoint to respond to early termination   */
		if ((rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_HOST_TO_DEVICE);
	}
	return 0;
}

void usbBegin(){
	//start vusb
	cli(); //disable interrupts

	// run at full speed, because Trinket defaults to 8MHz for low voltage compatibility reasons
	clock_prescale_set(clock_div_1);
	calibrateOscillator();
	
	PORTB &= ~(_BV(USB_CFG_DMINUS_BIT) | _BV(USB_CFG_DPLUS_BIT));
	
	usbInit();
	
	usbDeviceDisconnect();
	_delay_ms(250);
	usbDeviceConnect();

	sei(); //reenable interrupts
}

void usbEventResetReady(void){
	//this calibrates the rc oscillator to +/- 1% which is needed by vusb
	cli();
	calibrateOscillator();
	sei();
}

void usbPollWrapper(){
	//poll in C!!!
	usbPoll();
}

char usbSend(char *data, char len){
	//generically send data out of my interrupt-in endpoint
	
	while(len){
		usbPoll();
		if(usbInterruptIsReady()){
			usbSetInterrupt(data, len);
			//if statement check to allow up to 255 bytes of data to be sent in one call to usbSend
			if(len <= MAX_TRANSFER_SIZE){
				len = 0;
			} else {
				len -= MAX_TRANSFER_SIZE;
			}
		}
	}

	return 0; //placeholder return
}

void usbWait(char ms){
	//since usb requires periodic calls of the usbPoll function
	//split the delay into smaller chunks while polling
	while(ms){
		//polling takes an undetermined amount of time, so this will likely wait a lot longer than specified
		_delay_ms(10);
		ms -= ms>10 ? 10 : 10-ms;
		usbPoll();
	}
}
