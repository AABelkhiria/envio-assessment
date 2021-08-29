# Coding Task

### Contents
---

- [Introduction](#Introduction)
- [How to Build the Source Code](#How-to-Build-the-Source-Code)
- [Proprietary Serial Communication Structure](#Proprietary-Serial-Communication-Structure)

### Introduction
---

This project has been implemented to transfer current sensor data from an embedded device to a PC over UART serial communication protocol. Below is the list of the libraries developed:

- `bsp.c`:
	- This file contains the *weak* *stub* functions that are required to interact with the MCU.
- `currentsensor.c`:
	- This file contains `Current Sensor` related APIs to convert ADC reads to current measurements. The APIs accept Context and Data pointers instead of static/global variables to give the users the option of multiple current sensor measurements in the same context.
- `propcom.c`:
	- This file contains the proprietary serial communication algorithm. The APIs accept Context and Data pointers instead of static/global variables to give the users the option of running multiple UART busses at the time.
- `circular_buffer.c`
	- This file contains the circular buffer algorithm and retrieved from the [Embedded Artistry](https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/)'s Circular Buffer implementation. The original implementation was based on `byte` entries as the buffer elements, we changed the library to put `CurSensor_Data_t` entries in the fifo instead.
- `main.c`
	- This file contains the example usage of the libraries and executes the main requirements of the project as below:
	
	```
	- Current sensor measurement in every 1 second.
	- The sensor measurement data is put into the circular buffer with a TimeStamp.
	- The size of the circular buffer is set to 1024. The new entries overwrite the oldest entry if fifo usage exceeds the buffer limits.
	- The circular buffer status is checked and if there is a data entry waiting in the buffer, it is serialized and transferred over the UART with the First In First Out order.
	- The UART bus is checked to detect incoming packets and Packet Start/Stop events are flagged.
	```
	

### How to Build the Source Code
---

The source code can be compiled by using the `GNU ARM Toolchain` and the `GNU Make` tool. The code compilation has been tested in `Ubuntu 18` using below tools:

- `gcc-arm-none-eabi-10.3-2021.07`
- `Gnu Make 4.3`

Follow the below steps to compile the source code:

- Head to the `coding-task` folder where the `makefile` file presents.
- Open a command line terminal (alternatively a `bash terminal` in `Windows`)
- Run `make clean` command to clean the build directory.
- Run `make` command to build the source code.
- The output binaries should be generated under the `build` folder.

### Proprietary Serial Communication Structure
---

*There are only 3 possible serial packet types given in the assessment but we preferred to write a generic serial communication structure that can be extended by adding more packet types.*

The serial communication structure is explained in the below table:

| Entry          | Length | Description                                                                                                                                                                                                     |
|----------------|:------:|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Head of Packet | 1 Byte | Always = 0x55                                                                                                                                                                                                   |
| OpCode         | 1 Byte | 0x10 = Control Packet (PC to MCU)<br>0x11 = Sensor Packet (MCU to PC)                                                                                                                                           |
| Data Length    | 1 Byte | Length of the Data Buffer                                                                                                                                                                                       |
| Data Buffer    | 1 Byte | **For Control Packet:**<br>0xA0 = Start the Communication<br>0xA1 = Stop the Communication<br>**For Sensor Packet:**<br>4 Bytes Unix Epoch Time Stamp (LSB First)<br>2 Bytes Current Sensor Value (Unit: mA, LSB First) |
| Checksum       | 1 Byte | 8-bit XOR of the whole packet                                                                                                                                                                                   |



Examples of serial packet arrays are given in the below table:


| Hex Array                                         | Description                                                                                                            |
|---------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| 0x55 0x00 0x01 0xA0 0xF4                          | Start the Communication                                                                                                |
| 0x55 0x00 0x01 0xA1 0xF5                          | Stop the Communication                                                                                                 |
| 0x55 0x01 0x06 0x50 0x64 0x2A 0x61 0x74 0x40 0x19 | Sensor Data Example:<br>**TimeStamp**: 0x612A6450 (*Saturday, 28 August 2021 16:29:01*)<br>**Current Value**: 16500 mA |

