# Traffic Light System with Pedestrian Crossing

## Overview

This project simulates a four-way traffic light system with a pedestrian crossing request button using an Arduino.

The system manages two traffic directions (North–South and East–West) and safely integrates pedestrian crossing logic using a Finite State Machine (FSM).

---

## Features

- North–South and East–West traffic lights cycle between **Green → Yellow → Red** at timed intervals.
- A pedestrian push button allows safe crossing:
  - When pressed, the system waits for the current vehicle cycle to finish.
  - All vehicle lights turn **Red**.
  - The pedestrian light turns **Green**.
- The pedestrian light shows **Yellow** while pedestrians are waiting.
- The system remembers which traffic direction was active before the pedestrian request and resumes it afterward.
- Implemented using a **Finite State Machine (FSM)** with `enum` states for clarity and scalability.

---

## Technical Highlights

- Digital I/O pins control LEDs representing traffic lights and pedestrian signals.
- Push button configured with `INPUT_PULLUP` for reliable input detection.
- Uses `millis()` for non-blocking timing instead of relying entirely on `delay()`.
- Demonstrates:
  - State transitions
  - Event handling (button press)
  - Synchronization between vehicle traffic and pedestrian crossing logic

---

## Components Used

- Arduino board
- 2x RGB LEDs (North–South and East–West traffic lights)
- 1x Red LED (Pedestrian stop)
- 1x Yellow LED (Pedestrian waiting)
- 1x Green LED (Pedestrian go)
- 220Ω resistors (x7)
- Push button (pedestrian request)
- Breadboard
- Jumper wires

---

## System Design

The system is structured as a **Finite State Machine**, with states representing:

- NS Green  
- NS Yellow  
- EW Green  
- EW Yellow  
- Pedestrian Crossing  
- Pedestrian Waiting  

State transitions are triggered by:

- Timed intervals using `millis()`
- Button press events

---

## How to Run

1. Connect components according to your wiring setup.
2. Upload the `.cpp` / `.ino` file to the Arduino.
3. Power the board.
4. Press the button to simulate a pedestrian crossing request.

---

## Project Image

![IMG_3529](https://github.com/user-attachments/assets/51725a82-a83a-4b34-878f-7a142a061c64)


