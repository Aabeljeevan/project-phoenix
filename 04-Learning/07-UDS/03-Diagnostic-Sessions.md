# UDS Module 3 - Lesson 3
# Diagnostic Sessions (Service ID: 0x10)

---

## Objective

Understand why an ECU does not allow every diagnostic service immediately after a tester connects and how Diagnostic Sessions provide controlled access to different ECU functionalities.

---

# What is a Diagnostic Session?

A Diagnostic Session is an operating mode of the ECU.

Each session determines which UDS services are allowed. The ECU starts in the **Default Session** and only permits basic diagnostic operations. To perform advanced operations, the tester must first request a different diagnostic session.

---

# Why are Diagnostic Sessions Required?

Without Diagnostic Sessions, any diagnostic tester could immediately:

- Reset the ECU
- Flash new firmware
- Change calibration values
- Write configuration data
- Perform actuator tests

Allowing unrestricted access could lead to:

- Safety hazards
- Accidental ECU reset while driving
- Unauthorized ECU programming
- Vehicle theft
- Incorrect calibration
- System instability

Diagnostic Sessions ensure that sensitive operations are only available after the ECU explicitly grants permission.

---

# Types of Diagnostic Sessions

## 1. Default Session (0x01)

Purpose:

- Normal vehicle operation
- Basic diagnostic services

Typical Allowed Services:

- Read VIN
- Read sensor values
- Read Diagnostic Trouble Codes (DTCs)

Example Request:

10 01

Positive Response:

50 01

---

## 2. Programming Session (0x02)

Purpose:

Used for ECU software programming and firmware updates.

Typical Operations:

- Flash new firmware
- Erase flash memory
- Download application software

Example Request:

10 02

Positive Response:

50 02

Programming Session alone is **not sufficient** for ECU programming.

The tester must usually complete Security Access (Service 0x27) before programming is permitted.

---

## 3. Extended Diagnostic Session (0x03)

Purpose:

Provides access to advanced diagnostic functions.

Typical Operations:

- Actuator tests
- ECU configuration
- Calibration
- Advanced diagnostics

Example Request:

10 03

Positive Response:

50 03

---

# UDS Request and Response

Request:

10 03

Meaning:

- Service ID = 0x10
- Request Extended Diagnostic Session

Positive Response:

50 03

Explanation:

Positive Response Service ID

= Request Service ID + 0x40

0x10 + 0x40 = 0x50

---

# Negative Response Example

ECU Response:

7F 10 22

Meaning:

7F

- Negative Response

10

- Original Service ID
- Diagnostic Session Control

22

- NRC (Negative Response Code)
- Conditions Not Correct

Interpretation:

The ECU understood the request but cannot enter the requested session because the required operating conditions are not satisfied.

---

# Examples of "Conditions Not Correct"

The ECU may reject the request if:

- Vehicle speed is not zero
- Battery voltage is too low
- Engine is running
- Ignition state is incorrect
- Another diagnostic routine is already active
- Required preconditions are not satisfied

---

# Typical Programming Flow

Tester Connects

↓

Default Session

↓

10 02

(Request Programming Session)

↓

50 02

(Session Accepted)

↓

27 01

(Request Security Seed)

↓

67 01

(Seed Received)

↓

27 02

(Send Calculated Key)

↓

67 02

(Security Access Granted)

↓

Programming Services Allowed

---

# Important Notes

- The ECU always starts in Default Session.
- Sensitive services are protected using Diagnostic Sessions.
- Programming Session does not automatically grant programming permission.
- Security Access is typically required after entering Programming Session.
- Positive Response = Request Service ID + 0x40.

---

# Interview Notes

Q: Why are Diagnostic Sessions required?

Answer:

Diagnostic Sessions provide controlled access to ECU functionality. Basic diagnostic operations are available in the Default Session, while advanced operations such as ECU programming, calibration, and actuator testing require specific sessions. This improves safety, prevents unauthorized modifications, and protects the ECU from accidental or malicious operations.

---

# Key Takeaways

✔ ECU starts in Default Session

✔ Tester requests a new session using Service ID 0x10

✔ Positive Response = Service ID + 0x40

✔ Advanced services require Extended or Programming Session

✔ Programming Session is usually followed by Security Access

✔ Diagnostic Sessions improve both safety and security