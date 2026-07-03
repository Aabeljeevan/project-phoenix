# ISO-TP (ISO 15765-2)

## What is ISO-TP?

ISO-TP (ISO 15765-2) is a transport protocol used on top of the CAN bus.

## Why is it needed?

Classical CAN can transmit a maximum of 8 bytes of data in one frame.

Diagnostic messages, such as reading a VIN or software version, are often larger than 8 bytes.

ISO-TP solves this limitation by:
- Segmenting large messages into multiple CAN frames.
- Reassembling the frames at the receiver.

## Position in the communication stack

Application
    ↓
UDS
    ↓
ISO-TP
    ↓
CAN