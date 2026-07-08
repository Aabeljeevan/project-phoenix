# UDS Module 3 - Lesson 5
# Read Data By Identifier (Service ID: 0x22)

---

# Objective

Understand how the UDS Read Data By Identifier (0x22) service allows a diagnostic tester to request specific information from an ECU using Data Identifiers (DIDs).

---

# What is Read Data By Identifier?

Read Data By Identifier (Service ID 0x22) is one of the most commonly used UDS services.

It allows a diagnostic tester to request specific information stored inside an ECU.

Examples include:

- Vehicle Identification Number (VIN)
- ECU Software Version
- ECU Hardware Version
- ECU Serial Number
- Battery Voltage
- Coolant Temperature
- Manufacturer-specific parameters

---

# Request Format

22 DID_H DID_L

Example:

22 F1 90

Meaning:

22

↓

Read Data By Identifier

F1 90

↓

Vehicle Identification Number (VIN)

---

# Positive Response

Rule:

Positive Response = Request Service ID + 0x40

22 + 0x40 = 62

Example:

Request

22 F1 90

Response

62 F1 90 <VIN Data>

Meaning:

62

↓

Positive Response

F1 90

↓

Requested DID

VIN

↓

Requested Data

---

# ECU Internal Processing

When the ECU receives a request:

1. CAN Driver receives the CAN frame.
2. ISO-TP reassembles the UDS message if required.
3. UDS identifies Service ID 0x22.
4. The DID is extracted.
5. The ECU searches the DID table.
6. If the DID exists, the corresponding handler is executed.
7. The requested data is read.
8. A positive response is constructed.
9. ISO-TP segments the response if it exceeds 8 bytes.
10. CAN transmits the response.

---

# DID Table

Professional ECUs usually maintain a DID table instead of using hundreds of if-else statements.

Example:

| DID | Description | Handler |
|------|-------------|----------|
| F190 | VIN | ReadVIN() |
| F187 | Software Version | ReadSoftwareVersion() |
| F18C | ECU Serial Number | ReadSerialNumber() |
| F123 | Battery Voltage | ReadBatteryVoltage() |

Advantages:

- Easier to maintain
- Easy to add new DIDs
- Better scalability
- Cleaner implementation

---

# Example Flow

Tester

↓

22 F1 90

↓

ECU extracts DID F190

↓

Search DID Table

↓

VIN Handler Found

↓

Read VIN

↓

Build Response

↓

62 F1 90 VIN

↓

ISO-TP Segmentation (if required)

↓

CAN Transmission

---

# Multi-frame Response

The VIN contains 17 ASCII characters.

Response:

62

+

F1 90

+

17-byte VIN

Total payload exceeds the CAN 8-byte limit.

Therefore:

- First Frame
- Flow Control
- Consecutive Frames

are required using ISO-TP.

---

# DID Not Found

Request

22 F1 91

Suppose DID F191 does not exist.

The ECU returns:

7F 22 31

Meaning:

7F

↓

Negative Response

22

↓

Original Service ID

31

↓

Request Out Of Range

The tester now knows that the requested DID is not supported.

---

# Internal ECU Error

If the DID exists but the ECU cannot retrieve the requested data (for example, because of an internal memory or Flash access failure), the ECU should return an appropriate Negative Response Code instead of sending invalid or corrupted data.

The tester cannot repair the ECU's internal failure, but the negative response helps identify that the request could not be completed successfully.

---

# Important Notes

- Service ID = 0x22
- DID identifies the requested information.
- Positive Response = 0x62
- Missing DID results in NRC 0x31 (Request Out Of Range).
- Large responses require ISO-TP segmentation.
- Professional ECUs commonly implement a DID lookup table.

---

# Interview Notes

Q: Why do ECUs use a DID table instead of multiple if-else statements?

Answer:

A DID table provides better scalability and maintainability. Each DID is mapped to a dedicated handler function, making it easy to add, remove, or modify supported diagnostic data without changing the overall service logic. This approach is widely used in production automotive software.

---

# Key Takeaways

✔ Service ID = 0x22

✔ DID specifies which data is requested.

✔ Positive Response = 0x62

✔ VIN responses usually require ISO-TP multi-frame transmission.

✔ Production ECUs commonly use DID lookup tables.

✔ Unsupported DIDs return NRC 0x31.