# DS1302 RTC Library for Nuvoton M031

This repository provides a lightweight and easy-to-use driver for the **DS1302 Real-Time Clock (RTC)** module, specifically adapted for **Nuvoton M031** series microcontrollers.

The library implements bit-banging communication via GPIOs without relying on heavy peripheral libraries, making it highly portable and efficient.


https://github.com/user-attachments/assets/6d35ad6f-4492-4eae-ba80-f66366107e63


## Features
- Read and write time (year, month, date, hour, minute, second, day)
- Microsecond-level timing using `CLK_SysTickDelay`
- Minimal dependencies

## Hardware Connections
| DS1302 Pin | M031 Pin |
|:-----------|:---------|
| CLK        | PA0      |
| IO         | PA1      |
| RST        | PA2      |
| VCC        | 3.3V     |
| GND        | GND      |
![WhatsApp Image 2025-04-27 at 20 49 10_60f6a7f9](https://github.com/user-attachments/assets/c2d296dc-d4bb-412b-9afe-3205658534cc)

## Getting Started

1. **Connect** your DS1302 module to the specified pins.
2. **Include** `DS1302.c` and `DS1302.h` in your project.
3. **Initialize** the RTC:
    ```c
    DS1302_Init();
    ```
4. **Set Time Example:**
    ```c
    uint8_t time_set[8] = {0x00, 24, 4, 27, 15, 30, 0, 7}; // Control, Year, Month, Date, Hour, Minute, Second, Day
    DS1302_WriteTime(time_set);
    ```
5. **Read Time Example:**
    ```c
    uint8_t time_read[8];
    DS1302_ReadTime(time_read);
    ```

## Notes
- Make sure `SYS_Init()` configures the core clock before using `CLK_SysTickDelay`.
- The IO (data) pin is dynamically configured as INPUT or OUTPUT as needed.

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Author
Developed and maintained by ibrahim ışıklı - https://www.ibrahimisikli.com/

⭐ Feel free to star this repository if you find it useful!  
🤝 Contributions and pull requests are welcome!
