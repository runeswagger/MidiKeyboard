MidiKeyboard
============

A usb midi library designed for the Adafruit Trinket

This library turns your Trinket (or any avr compatible with V-USB) into a musical instrument.
I've configured V-USB to match the USB pins on the Trinket. If your using something other than a trinket
you will need to edit usbconfig.h to match your setup.

A word of warning, V-USB is only capable of emulating a low speed usb device, so certain applications are
technically beyond its capabilities. Unfortunately, usb midi devices fall under this category because
of the use of bulk endpoints which are forbidden on low speed devices. However, up until recently most OS would not
enforce this restriction and devices like USB Serial and USB Midi would work. So, use at your own risk.
I have tested this library on the latest Arch Linux (kernel, 3.17.6-1-ARCH x86_64) and it works.

You'll probably need a midi synthesizer to enjoy this library.
I'm using timidity++ available in the Arch repository and the GeneralUser GS soundfont
available here <http://www.schristiancollins.com/soundfonts/GeneralUser_GS_1.44-FluidSynth.zip>.
add this line to your timidity.cfg and you should be good to go.

soundfont /path/to/soundfont.sf2
