# UDS Module 3 - Lesson 1
# Introduction to UDS (Unified Diagnostic Services)

---

# What is UDS?

UDS (Unified Diagnostic Services) is an application layer diagnostic protocol defined by ISO 14229.

It provides a standardized method for a diagnostic tester to communicate with an Electronic Control Unit (ECU).

UDS allows a tester to:

- Read vehicle information
- Read sensor values
- Read Diagnostic Trouble Codes (DTCs)
- Clear fault codes
- Reset an ECU
- Update ECU software
- Perform actuator tests
- Configure ECU parameters

---

# Why Do We Need UDS?

CAN only transports data between ECUs.

Example:

CAN Frame

ID: 0x7E0

Data:

22 F1 90

CAN does not know the meaning of these bytes.

UDS defines what those bytes represent.

---

# Protocol Stack

+-------------------------+
| UDS                     |
| (Application Layer)     |
+-------------------------+
| ISO-TP                  |
| (Transport Layer)       |
+-------------------------+
| CAN                     |
| (Data Link Layer)       |
+-------------------------+

Responsibilities:

CAN
- Transfers CAN frames

ISO-TP
- Splits and reassembles messages larger than 8 bytes

UDS
- Defines diagnostic services and message meanings

---

# Real World Example

Technician wants to:

- Read VIN
- Read ECU Software Version
- Read Battery Voltage
- Read Fault Codes
- Reset ECU

Instead of sending English commands, the tester sends standardized UDS messages.

Example:

22 F1 90

Meaning:

Read VIN

---

# Key Takeaways

- UDS is defined by ISO 14229.
- UDS operates above ISO-TP and CAN.
- UDS standardizes diagnostic communication.
- UDS is used by diagnostic tools and service centers.