# UDS Module 3 - Lesson 2
# Positive and Negative Responses

---

# Positive Response

When the ECU successfully executes a request, it returns a Positive Response.

Rule:

Positive Response Service ID

=

Request Service ID + 0x40

Examples:

10

↓

50

22

↓

62

27

↓

67

2E

↓

6E

31

↓

71

---

# Example

Tester

22 F1 90

↓

Read VIN

ECU

62 F1 90 VIN

Meaning:

The ECU successfully processed the request and returned the VIN.

---

# Negative Response

If the ECU cannot execute a request, it returns:

7F

Original Service ID

Negative Response Code

Format:

7F xx yy

Example:

7F 22 31

Meaning:

7F

↓

Negative Response

22

↓

Read Data By Identifier failed

31

↓

Request Out Of Range

---

# Why Include the Original Service ID?

Including the original Service ID allows the tester to determine exactly which request failed.

Without it, the tester would not know which diagnostic service generated the error.

---

# Common NRCs

0x10

General Reject

0x11

Service Not Supported

0x12

Sub-function Not Supported

0x13

Incorrect Message Length or Invalid Format

0x22

Conditions Not Correct

0x31

Request Out Of Range

0x33

Security Access Denied

0x35

Invalid Key

0x36

Exceeded Number of Attempts

0x37

Required Time Delay Not Expired

---

# Example

Request:

22 F1 90

Response:

7F 22 31

Meaning:

The ECU understood the Read Data request but cannot process the requested DID.

---

# Key Takeaways

- Positive Response = Request Service ID + 0x40.
- Negative Responses always begin with 0x7F.
- NRC explains why the request failed.
- Original Service ID identifies which request failed.