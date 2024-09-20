# qt_example

`qt_example` a simple application developed using the Qt framework. This project implements a application with various functionalities.


<div align=center>
<img src="https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white"/> 
<img src="https://img.shields.io/badge/Qt-41CD52?&style=flat&logo=qt&logoColor=white"/> 
</div>

## Table of Contents
- [Keyboard](#️-keyboard)
- [Serial](#-serial)
- [Astar](#-a-pathfinding)
- [IMU](#-imu-inertial-measurement-unit)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## ⌨️ Keyboard
### Features

- **Keyboard Layout**: Supports qwerty and Korean keyboard layouts.
- **Caps Lock and Shift Keys**: Toggles between uppercase and lowercase.
- **Text Input**: Displays input text in a `QLabel`.
- **Keypress Capture**: Captures key press event and display.
- **Special Functions**: Handles Backspace, Tab, Enter, Windows key, and other special functions.

### Installation and Running

#### Prerequisites

- CMake
- Qt 5 or Qt 6 -> [Qt Docs][qtlink]
- X11 & XTest (required only for Linux)
    ```bash
    $ sudo apt-get install libx11-dev libxtst-dev
    ```

#### Build and Run

1. **Clone the Source Code**
    ```bash
    $ git clone https://github.com/mjlee111/qt_example.git
    ```

2. **Build**
   
    - Linux
    ```bash
    $ cd qt_example/Keyboard
    $ mkdir build && cd build
    $ cmake ..
    $ make
    ```
    - Windows
    ```bash
    $ cd qt_example/Keyboard
    $ mkdir build && cd build
    $ cmake -G "Visual Studio 16 2019" ..
    $ cmake --build . --config Release
    ```

3. **Run**
    - Linux
    ```bash
    ./keyboard
    ```
    - Windows

    Double-click the executable generated after building, or run it from the Command Prompt.

<div align=center>

![keyboard-run-image](https://github.com/mjlee111/qt_example/blob/master/keyboard/docs/run.png)
</div>

#### Usage
- **Text Input**: Click on the buttons to input text. Special keys like Backspace, Tab, and Enter perform their respective functions.
- **Language Switching**: Use the "Kor" or "영어" button to switch between Korean and English keyboard layouts.
- **Caps Lock**: Toggle Caps Lock to switch between uppercase and lowercase text.

## 🔌 Serial
### Features
- **Serial Port Communication**: Establishes communication with serial devices using various baud rates(up to 115200).
- **Data Reception**: Reads and displays incoming serial data in a `QTextEdit`.
- **Data Transmission**: Allows sending data to the serial device via the `writeToDevice()` methods.
- **Device Management**: Lists available serial ports and allows opening or closing the connection.
- **Automatic Scroll**: Ensures the `QTextEdit` view automatically scrolls to the latest received data.
- **Status Indication**: Changes the background color of a status label based on serial activity.

### Installation and Running
#### Prerequisites

- CMake
- Qt 5 or Qt 6 -> [Qt Docs][qtlink]
- For Windows: Ensure the Qt installation includes the Qt Serial Port module.
- For Linux: Install the libqt5serialport5 package (or 6).

#### Build and Run

1. **Clone the Source Code**
    ```bash
    $ git clone https://github.com/mjlee111/qt_example.git
    ```

2. **Build**
   
    - Linux
    ```bash
    $ cd qt_example/Serial
    $ mkdir build && cd build
    $ cmake ..
    $ make
    ```
    - Windows
    ```bash
    $ cd qt_example/Serial
    $ mkdir build && cd build
    $ cmake -G "Visual Studio 16 2019" ..
    $ cmake --build . --config Release
    ```

3. **Run**
    - Linux
    ```bash
    ./serial
    ```
    - Windows

    Double-click the executable generated after building, or run it from the Command Prompt.

    - Simple test with arduino. (returns NONE when no data to read, READ: ${DATA} when data available per 1 seconds.)
<div align=center>

![Serial-run-image](https://github.com/mjlee111/qt_example/blob/master/Serial/docs/run.gif)
</div>


#### Usage

- **Connect to Serial Device:**
    * Select a serial port from the dropdown menu.
    * Set the desired baud rate.
    * Click "OPEN" to establish the connection.

- **Data Reception:**
    * Incoming data will be displayed in the QTextEdit widget.
    * The widget scrolls automatically to show the latest data.

- **Data Transmission:**
    * Use the `writeToDevice()` methods to send data to the connected serial device.

- **Device Status:**
    * The status label will turn green when data is received.
    * The status label will return to its default color when no data is present.

- **Clear Display:**
    * Click the "CLEAR" button to clear the data from the display

## 🧭 A* Pathfinding
### Features
- **Grid-Based Pathfinding**: Implements the A* pathfinding algorithm to find the shortest path on a grid.
- **Dynamic Grid Visualization**: Displays a dynamic grid in the GUI where users can set obstacles, start, and end points.
- **Interactive Controls**: Allows users to interactively set the start and end points and obstacles through the UI.
- **Path Display**: Visualizes the calculated shortest path in the grid using color-coding.
- **Error Handling**: Provides feedback when a valid path cannot be found or if the start and end points are not set.

### Installation and Running
#### Prerequisites

- CMake
- Qt 5 or Qt 6 -> [Qt Docs][qtlink]
- For Windows: Ensure the Qt installation includes the necessary Qt modules.
- For Linux: Install the relevant Qt packages.

#### Build and Run

1. **Clone the Source Code**
    ```bash
    git clone https://github.com/mjlee111/qt_example.git
    ```

2. **Build**
   
    - **Linux**
    ```bash
    cd qt_example/Astar
    mkdir build && cd build
    cmake ..
    make
    ```
    - **Windows**
    ```bash
    cd qt_example/Astar
    mkdir build && cd build
    cmake -G "Visual Studio 16 2019" ..
    cmake --build . --config Release
    ```

3. **Run**
    - **Linux**
    ```bash
    ./astar
    ```
    - **Windows**  
      Double-click the executable generated after building, or run it from the Command Prompt.

<div align="center">
    <img src="https://github.com/mjlee111/qt_example/blob/master/Astar/docs/run.gif" alt="Astar-run-image">
</div>

### Usage

- **Initialize Grid:**
  - Set the number of rows and columns using the provided input fields.
  - Click "Generate" to create the grid.

- **Set Start and End Points:**
  - Click "Set Start" and select a cell to define the starting point (marked in green).
  - Click "Set End" and select a cell to define the ending point (marked in red).

- **Place Obstacles:**
  - Click on any cell to toggle obstacles (marked in black).

- **Find Path:**
  - Click "Start A*" to execute the A* algorithm and display the shortest path (highlighted in blue).

- **Clear Grid:**
  - Click the "Reset" button to clear all points, obstacles, and reset the grid.

- **Error Feedback:**
  - If no valid path is found or if the start/end points are not set, a message will be displayed.

## 📐 IMU (Inertial Measurement Unit)
### Features
- **Serial Port Communication**: Extends the functionality of the Serial project to communicate with [EBIMU][ebimu] sensors. Allows communication over various baud rates, with support for up to 115200.
- **Data Reception & Packet Analysis**: Reads incoming data from EBIMU sensors via serial communication, decodes sensor packets, and displays the values of parameters like acceleration, gyroscope, and magnetometer.
- **Real-time Data Visualization**: Utilizes OpenGL to render a 3D cube that reacts in real-time to changes in roll, pitch, and yaw values, providing visual feedback on the sensor's orientation.
- **Device Management**: Lists available serial ports and allows opening or closing the connection with EBIMU sensors. Automatically handles packet structure and parsing for seamless communication.
- **Automatic Scroll**: Ensures that the `QTextEdit` view, used for displaying raw data, automatically scrolls to the latest received data from the sensor.
- **Status Indication**: Provides visual feedback on sensor data reception by changing the background color of the status label.
- **Roll, Pitch, and Yaw Calculation**: Automatically computes roll, pitch, and yaw values from IMU sensor data, translating raw measurements into meaningful orientation angles.
  
### Installation and Running
#### Prerequisites

- CMake
- Qt 5 or Qt 6 -> [Qt Docs][qtlink]
- OpenGL for 3D visualization of IMU data
- EBIMU sensor (or any 9DOF sensor with compatible communication protocols)
- For Windows: Ensure the Qt installation includes the Qt Serial Port and OpenGL modules.
- For Linux: Install the libqt5serialport5 (or 6) and OpenGL libraries.

#### Build and Run

1. **Clone the Source Code**
    ```bash
    $ git clone https://github.com/mjlee111/qt_example.git
    ```

2. **Build**
   
    - Linux
    ```bash
    $ cd qt_example/IMU
    $ mkdir build && cd build
    $ cmake ..
    $ make
    ```
    - Windows
    ```bash
    $ cd qt_example/IMU
    $ mkdir build && cd build
    $ cmake -G "Visual Studio 16 2019" ..
    $ cmake --build . --config Release
    ```

3. **Run**
    - Linux
    ```bash
    ./IMU
    ```
    - Windows

    Double-click the executable generated after building, or run it from the Command Prompt.

    - Test the real-time visualization with an EBIMU sensor to see live changes in the orientation of the 3D cube.

<div align=center>

![IMU-run-image](https://github.com/mjlee111/qt_example/blob/master/IMU/docs/run.gif)
</div>

#### Usage

- **Connect to IMU Sensor:**
    * Select the EBIMU sensor's serial port from the dropdown menu.
    * Set the desired baud rate and communication parameters.
    * Click "OPEN" to establish the connection.

- **Data Reception:**
    * Incoming IMU data, including acceleration, gyroscope, and magnetometer values, will be displayed in the `QTextEdit` widget.
    * The widget automatically scrolls to the latest data.

- **3D Visualization:**
    * As the sensor's orientation changes, the 3D cube rendered using OpenGL will react in real-time, rotating to reflect the changes in roll, pitch, and yaw.
  
- **Device Status:**
    * The status label will turn green when data is received from the IMU.
    * It will return to its default color when no data is present.

- **Clear Display:**
    * Click the "CLEAR" button to clear the data from the display.

## 🤖 3DOF Robot Arm
### Features

- **Robot Arm Control**: Control the angles of a 3DOF robotic arm using QSlider.
- **Link Length Customization**: Adjust the length of each arm link using QSpinBox.
- **Real-Time Visualization**: Displays the robotic arm in a `QGraphicsView` with real-time updates.
- **Joint and End Effector Visualization**: Each joint is marked with a blue circle, and the end effector is marked with a red circle.
- **Reset Functionality**: Reset the arm's position and link lengths to default values.

### Installation and Running

#### Prerequisites

- CMake
- Qt 5 or Qt 6 -> [Qt Docs][qtlink]

#### Build and Run

1. **Clone the Source Code**
    ```bash
    $ git clone https://github.com/mjlee111/qt_example.git
    ```

2. **Build**

    - Linux
    ```bash
    $ cd qt_example/3DOF_robot_arm
    $ mkdir build && cd build
    $ cmake ..
    $ make
    ```
    - Windows
    ```bash
    $ cd qt_example/3DOF_robot_arm
    $ mkdir build && cd build
    $ cmake -G "Visual Studio 16 2019" ..
    $ cmake --build . --config Release
    ```

3. **Run**

    - Linux
    ```bash
    ./3DOF_robot_arm
    ```
    - Windows

    Double-click the executable generated after building, or run it from the Command Prompt.

<div align=center>

![robot-arm-run-image](https://github.com/mjlee111/qt_example/blob/master/3DOF_robot_arm/docs/run.gif)
</div>

#### Usage

- **Joint Angle Control**: Use the sliders to adjust the angles of the three joints. The corresponding angle value is displayed in real-time next to each slider.
- **Link Length Customization**: Adjust the length of each link using the spin boxes labeled `link1`, `link2`, and `link3`. The arm will update dynamically based on the entered values.
- **Generate Arm**: Click the "Generate Arm" button after setting the link lengths to visualize the updated robotic arm.
- **Reset Arm**: Click the "Reset" button to reset the arm's position and link lengths to their default values.

## Contributing
Feel free to submit issues, feature requests, and pull requests to improve the package.

## License
This project is licensed under the MIT License - see the [LICENSE][LICENSE] file for details.

## Contact
For any questions or feedback, please contact [menggu1234@naver.com][email].

[qtlink]: https://doc.qt.io/
[ebimu]: https://www.e2box.co.kr/
[LICENSE]: https://github.com/mjlee111/qt_example/blob/master/LICENSE
[email]: mailto:menggu1234@naver.com
