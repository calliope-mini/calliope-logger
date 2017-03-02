/**
 * Calliope Data Logger.
 *
 * This is a simple wireless data logger. It receices datagram packets from in the radio
 * group 0b01100110 and dumps the data as a hex/ascii dump on the serial port.
 * This is useful if you want to test functionality without a cable attached.
 *
 * @copyright (c) Calliope gGmbH.
 *
 * Licensed under the Apache Software License 2.0 (ASL 2.0)
 *
 * @author Matthias L. Jugel <leo@calliope.cc>
 */


#include <MicroBit.h>

MicroBit uBit;

void hexdump(const char *prefix, const uint8_t *b, int size) {
    for (int i = 0; i < size; i += 16) {
        if (prefix && strlen(prefix) > 0) printf("%s %06x: ", prefix, i);
        for (int j = 0; j < 16; j++) {
            if ((i + j) < size) printf("%02x", b[i + j]); else printf("  ");
            if ((j + 1) % 2 == 0) putchar(' ');
        }
        putchar(' ');
        for (int j = 0; j < 16 && (i + j) < size; j++) {
            putchar(b[i + j] >= 0x20 && b[i + j] <= 0x7E ? b[i + j] : '.');
        }
        printf("\r\n");
    }
}

void onData(MicroBitEvent event) {
    (void) event;
    uBit.display.image.setPixelValue(2, 2, 255);
    PacketBuffer packet = uBit.radio.datagram.recv();
    hexdump("DATA", packet.getBytes(), packet.length());
}

int main(void) {
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Calliope Data Logger v1.0\r\n");

    uBit.radio.enable();
    uBit.radio.setGroup(0b01100110);
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

    uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    while(1) {
        uBit.sleep(50);
        int v = uBit.display.image.getPixelValue(2,2);
        if(v > 0) uBit.display.image.setPixelValue(2, 2, max(0, v - 20));
    }
}