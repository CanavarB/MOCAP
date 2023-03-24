# ESP32-MOCAP (WIRELESS)

[Sample Video](https://www.youtube.com/watch?v=PjA4n_jvgSc)

This project involves building a motion capture suit using an **ESP32** microcontroller and an **MPU6050** IMU sensor. The aim of the project is to create a **low-cost** and **wireless** solution for capturing and transmitting motion data.

![frtzing](https://user-images.githubusercontent.com/100694366/227400860-ccfcbb69-c432-4a4b-aa63-f76c925b7759.jpg)

The suit consists of four MPU6050 sensors that are placed on different body parts. The sensor data is read by the ESP32 microcontroller, which processes and transmits the data wirelessly over a **WiFi** connection. The data is then received and processed by a computer or other device for visualization and analysis. 

I have created a model in **UPBGE** for demonstration purposes. The model is a humanoid character rigged with an armature, which can be animated with the motion capture data obtained from the ESP32 and MPU6050 setup. 
This can be a useful tool for visualizing the motion capture data in real-time and can be used for presentations or demonstrations of the project.

![upbge](https://user-images.githubusercontent.com/100694366/227400810-0cc6c251-6082-42de-b117-8c95387695f4.gif)

---
The project uses the ESP32's built-in WiFi capabilities to transmit the data in **real-time**, enabling live motion capture applications. The MPU6050 sensor provides 6 degrees of freedom (6DOF) motion tracking for each body part, including rotation rate data.

The firmware is written in C++ using the **PlatformIO** and UPBGE part is writen in Python.

Overall, this project provides a low-cost and customizable solution for motion capture, with the potential for applications in sports, entertainment, and robotics.

## Features
1. Wireless Communication
2. 4 IMU sensor without I2C multiplexer.
3. UDP transmission for speed.
4. Optimized data transfer

## Developer
- **Canavar B.** - _Initial work_ - [CanavarB](https://github.com/CanavarB)
## Model
- **asmvanime1998**  - _Designner_ - [CGTrader](https://www.cgtrader.com/free-3d-models/character/woman/kawaii-anime-girl-3d-model)
- **Canavar B.** - _Weight Paint_ - [CanavarB](https://github.com/CanavarB)

## TODO
- Comment adding.
- Unity and Unreal Engine examples.
- ESP8266 version.
- Including acceleration.
- Local discovery protocol for suit (SSDP)
## License

This project is licensed under the MIT License.

