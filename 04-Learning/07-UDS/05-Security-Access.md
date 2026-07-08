# UDS Module 3 - Lesson 4
# Security Access (Service ID: 0x27)

---

# Objective

Understand why Security Access is required in UDS and how the Seed-Key challenge-response mechanism protects the ECU from unauthorized access.

---

# Why is Security Access Required?

An ECU should not allow every connected diagnostic tester to perform sensitive operations such as:

- ECU Programming
- Flash Memory Erase
- Calibration Updates
- VIN Modification
- Key Programming
- Configuration Changes

Without Security Access, any person with a diagnostic tool could modify the ECU, creating serious safety and security risks.

Security Access ensures that only authorized diagnostic tools can perform protected operations.

---

# Where Does Security Access Fit?

Typical Programming Flow

Default Session

↓

10 02

(Request Programming Session)

↓

50 02

(Session Accepted)

↓

27 01

(Request Seed)

↓

67 01 <Seed>

↓

Tester Calculates Key

↓

27 02 <Key>

↓

67 02

(Security Access Granted)

↓

Protected Services Allowed

---

# Security Access Service

Service ID

27

Purpose

Authenticate the diagnostic tester before allowing access to protected ECU functions.

---

# Seed-Key Mechanism

Instead of sending a password, UDS uses a Challenge-Response Authentication mechanism.

Step 1

Tester requests a Seed.

27 01

↓

Request Seed

---

Step 2

ECU generates a random Seed.

67 01 12 34 56 78

Meaning

67

Positive Response

01

Seed Response

12 34 56 78

Random Seed

---

Step 3

Tester calculates the Key.

Conceptually

Key = f(Seed, Secret)

The actual algorithm is manufacturer-specific and is not publicly disclosed.

---

Step 4

Tester sends the calculated Key.

27 02 AB CD EF 11

Meaning

27

Security Access

02

Send Key

AB CD EF 11

Calculated Key

---

Step 5

ECU verifies the Key.

If the calculated Key matches the expected Key,

↓

67 02

Security Access Granted

Protected services are now available.

---

# Why Not Send a Password?

If a fixed password were transmitted on the CAN bus, anyone monitoring the communication could capture and reuse it.

Instead, UDS sends a new random Seed for each authentication attempt.

Since the Key depends on the Seed, every authentication uses a different Key.

This prevents Replay Attacks.

---

# Replay Attack

Suppose an attacker records the following communication.

27 01

↓

67 01 12 34 56 78

↓

27 02 AB CD EF 11

↓

67 02

The next day, replaying

27 02 AB CD EF 11

will fail because the ECU generates a different Seed for the new authentication attempt.

New Seed

↓

New Key

↓

Old Key becomes invalid

---

# Challenge-Response Authentication

ECU

↓

Generates Challenge (Seed)

↓

Tester

↓

Calculates Response (Key)

↓

ECU

↓

Verifies Response

↓

Access Granted

The Secret Algorithm and Secret Key are never transmitted over the CAN network.

---

# Common Negative Response Codes

7F 27 35

Invalid Key

Meaning

The received Key does not match the expected Key.

---

7F 27 36

Exceeded Number of Attempts

Meaning

Too many incorrect Key attempts were received.

The ECU may temporarily lock Security Access.

---

7F 27 37

Required Time Delay Not Expired

Meaning

The tester attempted Security Access before the lockout timer expired.

---

# Important Notes

- Security Access uses Service ID 0x27.
- Security Access is commonly required after entering Programming Session.
- A new Seed typically generates a new Key.
- The Secret Algorithm remains inside the ECU and the authorized diagnostic tool.
- Replay attacks fail because the Seed changes.
- Security Access is based on Challenge-Response Authentication.

---

# Interview Notes

Q: Why does UDS use a Seed instead of sending the Key directly?

Answer:

Sending the Key directly would expose the secret to anyone monitoring CAN traffic. Instead, the ECU generates a random Seed and the tester computes a Key using a manufacturer-specific secret algorithm. Since the Seed changes for each authentication, the calculated Key also changes, preventing replay attacks while ensuring that the secret is never transmitted.

---

# Key Takeaways

✔ Service ID = 0x27

✔ Security Access protects sensitive ECU operations

✔ Authentication uses Seed-Key Challenge-Response

✔ Secret Algorithm is never transmitted

✔ Replay attacks are prevented by changing the Seed

✔ Incorrect Keys result in Negative Response Codes