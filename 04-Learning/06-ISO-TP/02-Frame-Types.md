# ISO-TP Frame Types

ISO-TP defines four frame types to transmit messages over the CAN bus.

---

# Protocol Control Information (PCI)

Every ISO-TP frame begins with a Protocol Control Information (PCI) field.

The PCI identifies the frame type and provides additional information such as message length or sequence number.

For Classical CAN, the PCI occupies the first one or two bytes of the CAN payload depending on the frame type.

---

# Frame Type Identification

The upper nibble (first 4 bits) of the first PCI byte identifies the frame type.

| First Nibble | Frame Type |
|--------------|------------|
| 0 | Single Frame (SF) |
| 1 | First Frame (FF) |
| 2 | Consecutive Frame (CF) |
| 3 | Flow Control (FC) |

---

# 1. Single Frame (SF)

A Single Frame is used when the entire application message fits inside a single CAN frame.

For Classical CAN with normal addressing:

- CAN Payload = 8 bytes
- PCI = 1 byte
- Maximum Application Data = 7 bytes

Example:

```
03 22 F1 90 00 00 00 00
```

Explanation:

```
03

↓

0 = Single Frame

3 = Application Data Length
```

Application Data:

```
22 F1 90
```

---

# 2. First Frame (FF)

A First Frame is used when the application message is larger than the maximum payload of a Single Frame.

The First Frame:

- Indicates the start of a multi-frame transmission.
- Contains the total application message length.

For Classical CAN:

- PCI = 2 bytes
- Application Data = 6 bytes

Example:

```
10 19 62 F1 90 AA BB CC
```

Explanation:

```
10

↓

1 = First Frame
```

```
19 (Hex)

↓

25 Bytes Total Message Length
```

The remaining six bytes are the first six bytes of application data.

---

# 3. Consecutive Frame (CF)

After the First Frame, the remaining application data is transmitted using Consecutive Frames.

Each Consecutive Frame contains:

- PCI = 1 byte
- Application Data = 7 bytes

Example:

```
21 DD EE FF 11 22 33 44
```

Explanation:

```
21

↓

2 = Consecutive Frame

1 = Sequence Number
```

Sequence Numbers:

```
21 → Sequence Number 1

22 → Sequence Number 2

23 → Sequence Number 3

...

2F → Sequence Number 15

20 → Sequence Number 0 (Wrap Around)
```

Sequence numbers help the receiver detect:

- Missing Frames
- Duplicate Frames
- Out-of-order Frames

---

# 4. Flow Control (FC)

Flow Control frames are transmitted by the receiver after receiving a First Frame.

Their purpose is to control the speed of transmission and prevent receiver buffer overflow.

Example:

```
30 08 14 00 00 00 00 00
```

---

## Byte 0

```
30

↓

3 = Flow Control

0 = Continue To Send (CTS)
```

Possible Flow Status values:

| Value | Meaning |
|-------|---------|
| 0 | Continue To Send (CTS) |
| 1 | Wait (WT) |
| 2 | Overflow / Abort (OVFLW) |

---

## Byte 1 - Block Size (BS)

Block Size specifies how many Consecutive Frames the sender may transmit before waiting for another Flow Control frame.

Example:

```
08

↓

Transmit 8 Consecutive Frames

↓

Wait for another Flow Control
```

---

## Byte 2 - STmin (Separation Time Minimum)

STmin specifies the minimum delay between Consecutive Frames.

Example:

```
14 Hex

↓

20 ms
```

Meaning:

```
CF1

↓

Wait 20 ms

↓

CF2

↓

Wait 20 ms

↓

CF3
```

This prevents the receiver from being overwhelmed.

---

# Multi-frame Communication Sequence

```
Sender

↓

First Frame (FF)

↓

Receiver

↓

Flow Control (FC)

↓

Sender

↓

Consecutive Frame (CF)

↓

Consecutive Frame (CF)

↓

...

↓

Message Complete
```

---

# Example: Sending 25 Bytes

Application Data:

```
25 Bytes
```

Transmission:

```
First Frame

↓

6 Bytes Sent

↓

19 Bytes Remaining

↓

Flow Control

↓

CF1 (7 Bytes)

↓

CF2 (7 Bytes)

↓

CF3 (5 Bytes)
```

---

# Key Takeaways

- Single Frame is used when the application data fits in one frame.
- First Frame starts a multi-frame transfer.
- Consecutive Frames carry the remaining data.
- Flow Control regulates the transmission speed.
- PCI identifies the frame type.
- Sequence Numbers detect transmission errors.
- Block Size controls how many Consecutive Frames are sent before pausing.
- STmin defines the minimum delay between Consecutive Frames.