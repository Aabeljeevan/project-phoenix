# ISO-TP Quiz

This quiz is designed to test my understanding of the ISO-TP protocol.

---

# Level 1 - Fundamentals

## Question 1

What is ISO-TP?

<details>
<summary>Answer</summary>

ISO-TP (ISO 15765-2) is a transport layer protocol that enables the transmission of application messages larger than a single Classical CAN frame by segmenting and reassembling data.

</details>

---

## Question 2

Why is ISO-TP required?

<details>
<summary>Answer</summary>

Classical CAN supports a maximum payload of 8 bytes. ISO-TP allows larger application messages to be transmitted by splitting them into multiple CAN frames.

</details>

---

## Question 3

On which protocol does ISO-TP operate?

<details>
<summary>Answer</summary>

CAN.

ISO-TP is a transport layer built on top of the CAN protocol.

</details>

---

## Question 4

What are the four ISO-TP frame types?

<details>
<summary>Answer</summary>

- Single Frame (SF)
- First Frame (FF)
- Consecutive Frame (CF)
- Flow Control (FC)

</details>

---

# Level 2 - Understanding

## Question 5

When is a Single Frame used?

<details>
<summary>Answer</summary>

A Single Frame is used when the application data fits within the maximum payload supported by a Single Frame.

For Classical CAN with normal addressing, this is up to 7 bytes of application data.

</details>

---

## Question 6

Why is a First Frame required?

<details>
<summary>Answer</summary>

A First Frame starts a multi-frame transmission and informs the receiver of the total application message length.

</details>

---

## Question 7

What is the purpose of Consecutive Frames?

<details>
<summary>Answer</summary>

Consecutive Frames carry the remaining application data after the First Frame until the complete message has been transmitted.

</details>

---

## Question 8

Why are Flow Control frames required?

<details>
<summary>Answer</summary>

Flow Control frames allow the receiver to regulate the transmission speed, preventing receiver buffer overflow and ensuring reliable communication.

</details>

---

# Level 3 - Protocol Details

## Question 9

What does the first nibble of the PCI indicate?

<details>
<summary>Answer</summary>

It identifies the ISO-TP frame type.

0 → Single Frame

1 → First Frame

2 → Consecutive Frame

3 → Flow Control

</details>

---

## Question 10

What information does a First Frame contain?

<details>
<summary>Answer</summary>

- Frame Type
- Total Application Message Length
- First six bytes of application data

</details>

---

## Question 11

What is the purpose of the Sequence Number?

<details>
<summary>Answer</summary>

The Sequence Number helps detect:

- Missing Frames
- Duplicate Frames
- Out-of-order Frames

during a multi-frame transmission.

</details>

---

## Question 12

Why does the Sequence Number wrap after 15?

<details>
<summary>Answer</summary>

The Sequence Number occupies only 4 bits.

A 4-bit field can represent 16 values (0–15), so after 15 it wraps back to 0.

</details>

---

# Level 4 - Frame Decoding

## Question 13

Decode the following frame:

```
03 22 F1 90 00 00 00 00
```

<details>
<summary>Answer</summary>

Frame Type:

Single Frame

Application Data Length:

3 bytes

Application Data:

22 F1 90

</details>

---

## Question 14

Decode the following frame:

```
10 19 62 F1 90 AA BB CC
```

<details>
<summary>Answer</summary>

Frame Type:

First Frame

Total Message Length:

25 bytes

Application Data:

62 F1 90 AA BB CC

</details>

---

## Question 15

Decode the following frame:

```
21 DD EE FF 11 22 33 44
```

<details>
<summary>Answer</summary>

Frame Type:

Consecutive Frame

Sequence Number:

1

Application Data:

DD EE FF 11 22 33 44

</details>

---

## Question 16

Decode the following frame:

```
30 03 0A 00 00 00 00 00
```

<details>
<summary>Answer</summary>

Frame Type:

Flow Control

Flow Status:

Continue To Send (CTS)

Block Size:

3

STmin:

10 ms

Meaning:

The sender may transmit three Consecutive Frames with a minimum delay of 10 ms between them before waiting for another Flow Control frame.

</details>

---

# Level 5 - Interview Questions

## Question 17

Why doesn't ISO-TP simply increase the CAN payload size?

<details>
<summary>Answer</summary>

CAN was designed to be deterministic, reliable, and efficient. Increasing the payload size would affect timing, arbitration, and hardware compatibility. ISO-TP solves the problem by adding a transport layer without modifying the CAN protocol.

</details>

---

## Question 18

What would happen if Flow Control did not exist?

<details>
<summary>Answer</summary>

The sender could transmit Consecutive Frames faster than the receiver can process them, causing receiver buffer overflow and potential data loss.

</details>

---

## Question 19

What would happen if Sequence Numbers were not used?

<details>
<summary>Answer</summary>

The receiver would not be able to detect missing, duplicate, or out-of-order Consecutive Frames, leading to incorrect message reassembly.

</details>

---

## Question 20

Describe the complete ISO-TP communication sequence for transmitting a large application message.

<details>
<summary>Answer</summary>

1. Sender transmits a First Frame.
2. Receiver responds with a Flow Control frame.
3. Sender transmits Consecutive Frames according to the Block Size and STmin.
4. Receiver reassembles the complete application message.

</details>

---

# Self Evaluation

| Topic | Confidence (1-5) |
|--------|------------------|
| ISO-TP Basics | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Single Frame | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| First Frame | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Consecutive Frame | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Flow Control | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Block Size | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| STmin | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Sequence Numbers | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Frame Decoding | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
| Interview Readiness | ☐ 1 ☐ 2 ☐ 3 ☐ 4 ☐ 5 |
