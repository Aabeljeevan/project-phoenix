# ISO-TP Real Communication Examples

This document contains practical examples of ISO-TP communication over Classical CAN.

---

# Example 1 - Single Frame Communication

## Scenario

The diagnostic tester requests the ECU to start the default diagnostic session.

Application Data

```
10 01
```

Since the application data is only **2 bytes**, it fits within a Single Frame.

CAN Frame

```
02 10 01 00 00 00 00 00
```

### Breakdown

| Byte | Value | Description |
|------|------|-------------|
| Byte 0 | 02 | Single Frame, Application Data Length = 2 Bytes |
| Byte 1 | 10 | UDS Service ID (Diagnostic Session Control) |
| Byte 2 | 01 | Default Session |
| Remaining | 00 | Unused |

Communication

```
Tester
   |
   |---- Single Frame ---->
   |
ECU
```

No segmentation or Flow Control is required.

---

# Example 2 - Multi-frame Communication (25 Bytes)

## Scenario

The ECU needs to transmit 25 bytes of application data.

Application Data

```
25 Bytes
```

Since the message exceeds the maximum payload of a Single Frame, ISO-TP performs segmentation.

---

### Step 1 - First Frame

```
10 19 AA BB CC DD EE FF
```

Explanation

| Byte | Description |
|------|-------------|
| 10 | First Frame |
| 19 | Total Message Length = 25 Bytes |
| AA-FF | First 6 Bytes of Application Data |

---

### Step 2 - Flow Control

Receiver responds

```
30 08 14 00 00 00 00 00
```

Explanation

| Byte | Meaning |
|------|---------|
| 30 | Continue To Send |
| 08 | Block Size = 8 |
| 14 | STmin = 20 ms |

---

### Step 3 - Consecutive Frames

```
21 11 22 33 44 55 66 77

22 88 99 AA BB CC DD EE

23 FF 11 22 33 44 00 00
```

Explanation

CF1

- Sequence Number = 1

CF2

- Sequence Number = 2

CF3

- Sequence Number = 3

After the final Consecutive Frame, the complete 25-byte message has been successfully reconstructed.

Communication Flow

```
Sender

↓

First Frame

↓

Receiver

↓

Flow Control

↓

Consecutive Frame 1

↓

Consecutive Frame 2

↓

Consecutive Frame 3

↓

Transfer Complete
```

---

# Example 3 - Flow Control

Flow Control Frame

```
30 03 0A 00 00 00 00 00
```

### Breakdown

| Byte | Meaning |
|------|---------|
| 30 | Flow Control (Continue To Send) |
| 03 | Block Size = 3 |
| 0A | STmin = 10 ms |

Meaning

The receiver instructs the sender to:

- Send three Consecutive Frames.
- Maintain a minimum delay of 10 ms between each Consecutive Frame.
- Pause after transmitting the third Consecutive Frame.
- Wait for another Flow Control frame before continuing.

Communication

```
Flow Control

↓

CF1

↓

10 ms

↓

CF2

↓

10 ms

↓

CF3

↓

Stop

↓

Wait for next Flow Control
```

---

# Key Learning

Single Frame

- Used for small messages.
- No segmentation required.

First Frame

- Starts a multi-frame transmission.
- Contains the total application message length.

Consecutive Frame

- Carries the remaining application data.
- Uses sequence numbers to ensure correct ordering.

Flow Control

- Sent by the receiver.
- Controls transmission speed.
- Prevents receiver buffer overflow.

---

# Summary

ISO-TP enables the transmission of application messages larger than a single Classical CAN frame by using segmentation, reassembly, sequence numbering, and receiver-controlled flow management.`