#ifndef ROCKBLOCK_COMM_H
#define ROCKBLOCK_COMM_H

#include <Arduino.h>
#include <string>

// Call this in setup()
void setupRockblock();

// Call this in loop() every N seconds to manage the queue
void processRockblockQueue();

// Add a new message to the send queue
void queueRockblockMessage(const std::string& message);

#endif
