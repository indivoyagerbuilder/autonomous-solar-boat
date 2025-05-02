#include "RockblockComm.h"
#include <HardwareSerial.h>
#include <IridiumSBD.h>
#include <queue>

// === Rockblock Configuration ===
#define ROCKBLOCK_BAUD        19200
#define ROCKBLOCK_SLEEP_PIN   5
#define ROCKBLOCK_RX_PIN      4
#define ROCKBLOCK_TX_PIN      5

HardwareSerial RockSerial(1);
IridiumSBD modem(RockSerial, ROCKBLOCK_SLEEP_PIN);

// === Message Queue ===
static std::queue<std::string> messageQueue;
const size_t MAX_QUEUE_SIZE = 3;

void setupRockblock() {
    RockSerial.begin(ROCKBLOCK_BAUD, SERIAL_8N1, ROCKBLOCK_RX_PIN, ROCKBLOCK_TX_PIN);
    if (modem.begin() != ISBD_SUCCESS) {
        Serial.println("Rockblock modem init failed.");
    } else {
        Serial.println("Rockblock modem ready.");
    }
}

void queueRockblockMessage(const std::string& message) {
    if (messageQueue.size() >= MAX_QUEUE_SIZE) {
        Serial.println("Rockblock queue full — dropping oldest message.");
        messageQueue.pop();
    }
    messageQueue.push(message);
}

bool sendWithTimeout(const char* message, unsigned long timeoutMillis) {
    unsigned long startTime = millis();
    int err;

    while ((millis() - startTime) < timeoutMillis) {
        err = modem.sendSBDText(message);
        if (err == ISBD_SUCCESS) {
            return true;
        } else if (err == ISBD_SENDRECEIVE_TIMEOUT) {
            Serial.println("Rockblock timeout — will retry later.");
            return false;
        } else {
            Serial.print("Rockblock error: "); Serial.println(err);
            return false;
        }
    }

    Serial.println("Rockblock send hung — timed out.");
    return false;
}

void processRockblockQueue() {
    if (messageQueue.empty()) return;

    std::string msg = messageQueue.front();
    bool success = sendWithTimeout(msg.c_str(), 10000); // 10-second timeout

    if (success) {
        Serial.println("Rockblock message sent.");
        messageQueue.pop();
    } else {
        Serial.println("Rockblock message send failed — will retry next loop.");
    }

    modem.sleep();  // conserve power
}
