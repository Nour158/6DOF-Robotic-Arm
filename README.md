# 🤖 6-DOF Robotic Arm using Arduino & ESP32

A robotics project that implements a **6-Degree-of-Freedom (6-DOF) robotic arm** using **Arduino**, **ESP32**, and servo motors. The system combines two microcontrollers, where the Arduino manages communication while the ESP32 controls the servo channels responsible for the robotic arm's movement.

---

## 📌 Project Overview

This project was developed as part of a Robotics Programming course to explore embedded systems and robotic manipulation.

The robotic arm consists of five servo motors that provide multiple degrees of freedom for movement. An **Arduino** is used to handle communication with the system, while an **ESP32** is dedicated to controlling the servo motor channels. An external power supply provides stable power to the servos, ensuring reliable operation.

The project provided hands-on experience with embedded programming, servo motor control, and robotic system integration.

---

## 📷 Project Image

![Robotic Arm](media/robotic_arm.jpg)

---

## 🎥 Project Demo

A demonstration video showing the robotic arm in action is available in the **media/** folder.

---

## 🚀 Features

- 6-DOF robotic arm control
- Coordinated movement of multiple servo motors
- Arduino for communication
- ESP32 for servo channel control
- Real hardware implementation
- External power supply for stable servo operation

---

## 🛠 Technologies Used

- Arduino
- ESP32
- C++
- Arduino IDE
- Servo Library
- Embedded Systems

---

## ⚙️ Hardware Components

- Arduino Board
- ESP32 Development Board
- 5 Servo Motors
- 5-DOF Robotic Arm Kit
- External Power Supply
- Jumper Wires

---

## 📂 Repository Structure

```text
6DOF-Robotic-Arm/
│
├── 5dof.ino
├── README.md
├── requirements.txt
└── media/
    ├── robotic_arm.jpg
    └── robotic_arm_demo.mp4
```

---

## ▶️ Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Nour158/5DOF-Robotic-Arm.git
```

### 2. Open the project

Open `5dof.ino` using the Arduino IDE.

### 3. Install the required libraries

Install the Servo and ESP32 libraries if they are not already installed.

### 4. Upload the code

Upload the program to the appropriate board(s).

### 5. Power the robotic arm

Connect the external power supply to the servo motors.

### 6. Run the project

After uploading the program and powering the system, the robotic arm performs the programmed movements.

---

## 🔮 Future Improvements

- Bluetooth control
- Wi-Fi remote control
- Joystick-based control
- Forward Kinematics implementation
- Inverse Kinematics implementation
- Computer Vision integration
- Object pick-and-place functionality
- ROS integration

---

## 👩‍💻 Author

**Nourallah Ghonim**

Artificial Intelligence Student

Interested in Robotics, Computer Vision, Embedded Systems, and Machine Learning.
