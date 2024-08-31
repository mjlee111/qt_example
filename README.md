# qt_example

`qt_example` a simple application developed using the Qt framework. This project implements a application with various functionalities.

## Table of Contents
- [Keyboard](#keyboard)
- [Serial](#serial)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Keyboard
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

![keyboard-run-image](https://github.com/mjlee111/qt_example/blob/master/Keyboard/docs/run.png)
</div>

#### Usage
- **Text Input**: Click on the buttons to input text. Special keys like Backspace, Tab, and Enter perform their respective functions.
- **Language Switching**: Use the "Kor" or "영어" button to switch between Korean and English keyboard layouts.
- **Caps Lock**: Toggle Caps Lock to switch between uppercase and lowercase text.

## Serial
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

<div align=center>

![Serial-run-image](https://github.com/mjlee111/qt_example/blob/master/Serial/docs/run.gif)
</div>

## Usage

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

## Contributing
Feel free to submit issues, feature requests, and pull requests to improve the package.

## License
This project is licensed under the MIT License - see the [LICENSE][LICENSE] file for details.

## Contact
For any questions or feedback, please contact [menggu1234@naver.com][email].

[qtlink]: https://doc.qt.io/
[LICENSE]: https://github.com/mjlee111/qt_example/blob/master/LICENSE
[email]: mailto:menggu1234@naver.com
