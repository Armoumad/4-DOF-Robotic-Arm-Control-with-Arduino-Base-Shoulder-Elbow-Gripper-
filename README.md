# 4-DOF Robotic Arm Control with Arduino (Base, Shoulder, Elbow, Gripper)

This project lets you control a 4-servo robotic arm from the Arduino Serial Monitor. Each joint (base, shoulder, elbow) and the gripper can be positioned using simple text commands such as `B 90` or `G 30`.

The sketch uses the built-in Arduino `Servo.h` library and defines text commands to set each servo to a given angle (in degrees).

---

## Features

- Direct serial control of 4 servos:
  - B: Base
  - S: Shoulder
  - E: Elbow
  - G: Gripper
- Angles in degrees (0–180)
- Safe startup position (Base=90°, Shoulder=90°, Elbow=90°, Gripper=0°)
- Simple Serial Monitor interface at 115200 baud
- Easy to extend (per-joint limits, smooth motion, sequences, presets, etc.)

---

## Hardware

- 1x Arduino (Uno/Nano/MEGA or compatible)
- 4x Servos (micro SG90/MG90S or higher torque like MG995/MG996R depending on your arm)
- 1x Dedicated 5–6 V power supply for servos (current capacity 2–5 A depending on your servos)
- Dupont wires / breadboard
- Recommended: Filtering capacitor (470–1000 µF, ≥6.3 V) across the servo supply rails
- Common ground between Arduino GND and servo power supply GND
- Optional: master power switch, emergency stop, fuse

---

## Wiring

- Servo signal pins to Arduino:
  - Base   → D6
  - Shoulder → D3
  - Elbow  → D5
  - Gripper → D9
- Servo V+ (red): external 5–6 V power supply +
- Servo GND (brown/black): external power supply GND
- Arduino GND must connect to servo power supply GND (common ground)
- Do not power high-torque servos from the Arduino 5 V pin

Default pin mapping in the code:
```
const int BASE_PIN = 6;
const int SHOULDER_PIN = 3;
const int ELBOW_PIN = 5;
const int GRIPPER_PIN = 9;
```

If your wiring differs, update these constants accordingly.

---

## Installation

1. Install the Arduino IDE: https://www.arduino.cc/en/software
2. Open `servo_control.ino`.
3. Ensure the `Servo` library is available (bundled with the IDE).
4. Select your board and port under Tools → Board / Port.
5. Upload the sketch.

---

## Usage

1. Open the Serial Monitor (Ctrl+Shift+M) at 115200 baud.
2. Set line ending to “Newline” so a `\n` is sent.
3. Send commands in the format:
   - `B angle` → Base
   - `S angle` → Shoulder
   - `E angle` → Elbow
   - `G angle` → Gripper
4. Examples:
   - `B 90`   (base to 90°)
   - `S 45`   (shoulder to 45°)
   - `E 120`  (elbow to 120°)
   - `G 30`   (gripper to 30°)

The program prints confirmation messages and helpful errors (unknown servo, invalid format, etc.).

Startup behavior:
- On reset, the servos move to a safe position: Base=90°, Shoulder=90°, Elbow=90°, Gripper=0°.
- Make sure the workspace is clear before powering on.

---

## Calibration and Angle Limits

- Before mounting horn/links, power the servos and set them to 90° to mechanically center them.
- Each joint has its own mechanical range. Add per-joint software limits to avoid hitting hard stops and overloading servos.

Example of global and per-joint limits to integrate into your code:
```cpp
// Recommended limits (adapt to your arm)
int minBase = 0,     maxBase = 180;
int minShoulder = 10, maxShoulder = 150;
int minElbow = 10,    maxElbow = 170;
int minGripper = 0,   maxGripper = 90;

// After parsing `angle` from the command:
angle = constrain(angle, 0, 180); // global safety bound

switch (toupper(servo)) {
  case 'B':
    angle = constrain(angle, minBase, maxBase);
    base.write(angle);
    break;
  case 'S':
    angle = constrain(angle, minShoulder, maxShoulder);
    shoulder.write(angle);
    break;
  case 'E':
    angle = constrain(angle, minElbow, maxElbow);
    elbow.write(angle);
    break;
  case 'G':
    angle = constrain(angle, minGripper, maxGripper);
    gripper.write(angle);
    break;
}
```

If one joint moves in the opposite direction, invert its command with:
```cpp
servo.write(180 - angle);
```

---

## Customization

- Change pins: edit `BASE_PIN`, `SHOULDER_PIN`, `ELBOW_PIN`, `GRIPPER_PIN`.
- Smooth motion (ramping): move in small steps with short delays, or use a library like `VarSpeedServo`.
- Motion sequences: create functions that chain positions with delays.
- Presets: add text commands like `HOME`, `OPEN`, `CLOSE`, etc.
- Microsecond control: use `writeMicroseconds(500–2500)` for fine control (check your servo’s specs).

---


## Troubleshooting

- Servos buzzing/shaking: unstable supply → use a dedicated servo PSU, add a large capacitor across V+/GND, check common ground.
- Arduino resets when a servo starts: voltage drop → power supply too weak, wires too thin/long.
- A servo doesn’t move: check signal pin mapping, connector orientation (GND/5V/Signal), test servo alone.
- Serial commands do nothing: check baud (115200), line ending “Newline”, exact format “LETTER space ANGLE”.
- Gripper closes the wrong way: invert with `180 - angle` or remount horn.
- Mechanical stops reached too early: tighten per-joint `min/max` software limits.

---

## Safety

- Keep fingers clear of the gripper and gears.
- Start with no payload and slow motions.
- Disconnect power before mechanical changes.
- Add an emergency stop if possible.

---

## Possible Extensions

- Inverse kinematics (IK) for X/Y/Z and tool orientation control.
- Save and replay positions/trajectories.
- Richer interfaces (Bluetooth, Wi‑Fi, joystick, potentiometers).
- Position feedback (modified servos or external sensors).
- Motion profiles with acceleration/deceleration and trajectory planning.

---

## Notes and Recommended Fixes for the provided `servo_control.ino`

Adjust these to ensure compilation and correct behavior:

- Fix the gripper example line (remove the stray character `a`):
  ```
  Serial.println("  G 30     (gripper at 30°)");
  ```
- Add angle bounding after parsing the angle:
  ```cpp
  int angle = angleStr.toInt();
  angle = constrain(angle, 0, 180);
  ```
- Ensure your Serial Monitor sends a newline `\n` (set line ending to “Newline”).

---


---

## Credits

- Arduino `Servo.h` library
- Mechanical design: your 2D drawing
- Author: You (and contributors)

