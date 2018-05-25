//
// Created by Oleksandra Baukh on 3/21/18.
//

#ifndef MARKOS_ARDUINO_CONTROLLER_TRANSCEIVER430_H
#define MARKOS_ARDUINO_CONTROLLER_TRANSCEIVER430_H


#include <Transceiver.h>
#include <RH_ASK.h>
#include <Receiver.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <types.h>

template<typename Content>
class TR433
        : public mark_os::communication::Transceiver<Content>, public mark_os::communication::Receiver<Content> {
    RH_ASK driver;
public:

    TR433();

    mark_os::commons::Optional<Message<Content>> receive() override;

    void send(Message<Content> &message) override;
};

template<typename Content>
void TR433<Content>::send(Message<Content> &message) {
    driver.send((uint8_t *) &message, sizeof(message));
    driver.waitPacketSent();
}

template<typename Content>
TR433<Content>::TR433() {
    if (!driver.init()) {
        Serial.println("init failed");
    }
}

template<typename Content>
mark_os::commons::Optional<Message<Content>> TR433<Content>::receive() {
    Message<Content> message;

    uint8_t buflen = sizeof(message);

    if (driver.recv((uint8_t *) &message, &buflen)) {
        return mark_os::commons::optional(message);
    }
    return mark_os::commons::none<Message<Content >>();
}

#endif //MARKOS_ARDUINO_CONTROLLER_TRANSCEIVER430_H
