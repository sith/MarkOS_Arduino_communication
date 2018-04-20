#include <TR433.h>

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


