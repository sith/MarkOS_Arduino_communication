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

#endif //MARKOS_ARDUINO_CONTROLLER_TRANSCEIVER430_H
