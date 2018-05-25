//
// Created by Oleksandra Baukh on 5/24/18.
//

#ifndef MARKOS_ARDUINO_COMMUNICATION_TR24_H
#define MARKOS_ARDUINO_COMMUNICATION_TR24_H

#include <Transceiver.h>
#include <Receiver.h>

#include <SPI.h>
#include <RH_NRF24.h>

template<typename Content>
class TR24 : public mark_os::communication::Transceiver<Content>, public mark_os::communication::Receiver<Content> {
    RH_NRF24 nrf24;
public:
    TR24() {
        Serial.begin(9600);
        while (!Serial); // wait for serial port to connect. Needed for Leonardo only
        if (!nrf24.init())
            Serial.println("init failed");
        // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
        if (!nrf24.setChannel(1))
            Serial.println("setChannel failed");
        if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
            Serial.println("setRF failed");
    }

    mark_os::commons::Optional<Message<Content>> receive() override {
        if (nrf24.available()) {
            Message<Content> message;
            uint8_t len = sizeof(message);

            if (len > RH_NRF24_MAX_MESSAGE_LEN) {
                warningMessage(len);
                return mark_os::commons::none<Message<Content>>();
            }

            if (nrf24.recv((uint8_t *) &message, &len)) {
                return mark_os::commons::optional<Message<Content>>(message);
            }
        }
        return mark_os::commons::none<Message<Content>>();

    }

    void warningMessage(uint8_t len) const {
        Serial.print("The expected message is too big ");
        Serial.println(len);
    }

    void send(Message<Content> &message) override {

        auto len = sizeof(message);
        if (len > RH_NRF24_MAX_MESSAGE_LEN) {
            warningMessage(len);
            return;
        }
        nrf24.send((uint8_t *) &message, len);

        nrf24.waitPacketSent();
    }
};


#endif //MARKOS_ARDUINO_COMMUNICATION_TR24_H
