# UDS Module 3 - Lesson 1
# Service IDs and Data Identifiers (DIDs)

---

# UDS Message Structure

Most UDS requests follow this format:

Service ID

↓

Data Identifier (Optional)

↓

Data (Optional)

---

# What is a Service ID?

A Service ID tells the ECU what action to perform.

Think of it as the "verb" of a sentence.

Examples:

0x10

Diagnostic Session Control

0x11

ECU Reset

0x22

Read Data By Identifier

0x2E

Write Data By Identifier

0x27

Security Access

0x19

Read Diagnostic Trouble Codes

---

# What is a DID?

DID stands for Data Identifier.

A DID identifies which specific information is requested.

Think of it as the "object" of the sentence.

Example:

22 F1 90

22

↓

Read Data

F1 90

↓

VIN Number

---

# Analogy

English

Read VIN

↓

Read = Service ID

VIN = Data Identifier

UDS

22 F1 90

↓

22 = Read

↓

F1 90 = VIN

---

# Common DIDs

F190

Vehicle Identification Number (VIN)

F187

ECU Software Version

F18C

ECU Serial Number

(Note: DIDs vary depending on manufacturer.)

---

# Key Takeaways

- Service ID defines the requested action.
- DID identifies the requested data.
- A UDS message is similar to calling a function in C.