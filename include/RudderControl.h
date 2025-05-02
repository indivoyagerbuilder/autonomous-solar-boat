#ifndef ROCKBLOCK_COMM_H
#define ROCKBLOCK_COMM_H

#include <Arduino.h>
#include <string>

// Setup Rockblock modem
void setupRockblock();

// Call this in loop to attempt sending queued messages
void processRockblockQueue();

// Add a message to the send queue
void queueRockblockMessage(const std::string& message);

#endif
