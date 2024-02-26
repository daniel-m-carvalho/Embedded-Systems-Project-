# Storage Management System with RFID Lock

## Objective

The project work of the Embedded Systems (ES) course aims to achieve an autonomous system that allows the management of a cabinet for depositing and retrieving objects with an RFID lock.

## Architecture

The system to be developed, whose block diagram is presented in Figure 1, will be implemented based on the LPCXpresso LPC1769 development board from NXP [D2], which includes an LPC1769 microcontroller [D1], a contactless card reader module [D7] based on the MFRC522 chip [D6], and a cabinet latch (simulated by an LED). The system will provide a local interface for the user with a rotary and pressure button [D19] and an LCD display MC1602C [D4] based on the HD44780 controller [D5].

![Figure 1: Block diagram of the system to be developed](/docs/figure1.png)

## Operation

It is intended that the system to be developed presents two distinct operating modes (normal mode and maintenance mode) and be an autonomous system, i.e., the application should run automatically after the electrical power is turned on.

### Normal Mode

The system should display on the LCD screen the information related to the calendar, clock, and state of the cabinet (occupied or empty), the door latch should be active, and it should be receptive to the presence of contactless cards. In the case of the cabinet being empty, when the user approaches an authorized card, the system should deactivate the door latch, allowing the user to place the object to be stored in the cabinet. The rotary button allows the visualization of existing authorized cards, and the pressure button, when pressed, selects the card number that allows the retrieval of the object stored in the cabinet. Finally, the system should reactivate the cabinet door latch. If the cabinet is occupied, when the user approaches the authorized card to retrieve the object stored in the cabinet, the system should deactivate the door latch for 5 seconds and display the card number on the screen. If the card is not authorized, the display should indicate that the card is not authorized to retrieve the stored object. In both deposit and retrieval cases, the system should record in the non-volatile memory of the microcontroller (flash) the card number, the action (deposit or retrieval), and the moment when the object was deposited or removed (date and time).

### Maintenance Mode

The system enters this operating mode when the button is pressed twice in a row (double click) and should allow adding or removing authorized cards, adjusting the calendar and clock, as well as viewing the records stored in the non-volatile memory of the microcontroller. In this operating mode, the rotary button allows navigation through the menus, and the pressure button, when pressed, accesses the selected menu. During the adjustment of the calendar and clock, the rotary button increments or decrements the value of the selected field. The pressure button, when pressed, changes the field to adjust or returns to the menu if the field is the last one, confirming its value. During the addition of a card, the system awaits the reading of a card, displaying its identifier on the screen. The pressure button, when pressed, adds the card to the system and returns to the menu. During the removal of a card, the rotary button allows the visualization of existing cards. The pressure button, when pressed, removes the visible card and returns to the menu. During the visualization of stored records, the rotary button allows the visualization of the next or previous record. The pressure button, when pressed, cancels the visualization and returns to the menu.

## Structure of the Work: CMSIS_CORE_LPC17xx -> HAL -> DRIVERS -> MFRC522 -> Project

The project's architecture follows a structured approach, progressing through layers that facilitate development and integration:

1. **CMSIS_CORE_LPC17xx**: At the foundational level, this layer implements the Cortex Microcontroller Software Interface Standard (CMSIS) for the LPC17xx series microcontrollers. It establishes a standardized hardware abstraction layer, essential for interfacing with the ARM Cortex-M processor core.

2. **HAL (Hardware Abstraction Layer)**: Building upon the CMSIS_CORE_LPC17xx, this layer provides higher-level abstractions to access various hardware peripherals and functionalities of the LPC1769 microcontroller. It simplifies the development process by offering standardized interfaces and functions.

3. **DRIVERS**: This layer incorporates specific device drivers necessary for interacting with external hardware components. Within this layer lies the driver for the MFRC522 chip, which is a crucial component utilized for contactless card reading in the project.

4. **MFRC522**: This submodule focuses on the functionalities specific to the MFRC522 chip. It includes tasks such as initializing the chip, managing communication protocols, and facilitating data transfer with RFID tags.

5. **Project**: Serving as the top-level layer, this segment encompasses the actual application logic and integration of various components. Leveraging functionalities provided by lower layers, it implements the desired features, such as the management of the storage cabinet for depositing and retrieving objects using RFID technology.

This structured approach aids in organizing the codebase, fostering modularity, and easing the development and maintenance processes of the storage management system with RFID lock.


**Notes:** 
- Although the implementation is intended to use the flash memory of the controller to store data, the project is not currently utilizing this feature.
- Additionally, it's worth mentioning that the modules CMSIS_CORE_LPC17xx and MFRC522 were provided by the teacher.


Instituto Superior de Engenharia de Lisboa
BSc in Computer Science and Engineering
Programming in Mobile Devices
Winter Semester of 2023/2024
