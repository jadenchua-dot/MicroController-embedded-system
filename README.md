# ATmega328P embedded C labs

[![Build labs](https://github.com/jadenchua-dot/MicroController-embedded-system/actions/workflows/build.yml/badge.svg)](https://github.com/jadenchua-dot/MicroController-embedded-system/actions/workflows/build.yml)

My lab programs for **Microcontroller Programming & Interfacing** (EG2E55) in the Diploma in Electronic and Computer Engineering at Nanyang Polytechnic. Each one programs an **ATmega328P** directly in C: no Arduino libraries, just the chip's registers (`DDRx`, `PORTx`, `PINx`, `ADMUX`, `UCSR0x`, `EICRA`...).

The labs build up from blinking an LED to a temperature monitor that reports to a PC over serial and reacts to interrupts.

## Labs

| Lab | Topic | Programs |
|---|---|---|
| [01](lab-01-gpio-output) | **GPIO output.** Set Port D as outputs and toggle LEDs with a busy-wait delay | `exercise01.c` all eight LEDs, `exercise02.c` only the lower four (`^= 0x0F`) |
| [02](lab-02-bit-masks) | **Bit masks.** Turn on one LED at a time with `&= ~mask`, leaving the other pins alone | `lab02.c` |
| [03](lab-03-seven-segment) | **7-segment display.** A lookup table turns a digit into its segment pattern | `listing2_1.c` counts 0-9, `3part2.c` counts down, `3part3.c` up then down |
| [04](lab-04-push-buttons) | **Push buttons.** Inputs with internal pull-ups, polled through `chkSw()` / `onLED()` helpers | `exercise02.c`, `exercise3_1.c`, `exercise3_3.c`, `exercise_3_5.c` (running light that changes direction) |
| [05](lab-05-adc) | **ADC.** Read analog sensors and show the value on a multiplexed 3-digit display | `exercise1.c` temperature, `exercise2.c` LDR night light (LEDs on when it gets dark, with a gap so they don't flicker), `exercise3.c` both together |
| [06](lab-06-serial-uart) | **Serial (UART).** Send data to a PC terminal at 9600 baud, then answer commands | `listing3_1.c` first characters, `figure4_2.c` the same at 300 baud, `listing3_1_part2.c` temperature to the PC, `listing7_2.c` sends °C or °F on a `C` / `F` command, `listing7_3.c` display multiplexing, `exercise4_1.c` |
| [07](lab-07-external-interrupts) | **External interrupts.** `INT0` / `INT1` on a falling edge run an ISR while the main loop keeps counting | `exercise2_1.c` one interrupt, `exercise3_2.c` two buttons, two different blink patterns |

Labs 05 to 07 include the lab sheet from the course (PDF) with the circuit and the tasks.

## Hardware

- **ATmega328P** at 16 MHz on the school's microcontroller trainer board
- LEDs on Port D (active low), push buttons on PB3-PB5 and on `INT0` / `INT1` (PD2, PD3)
- 3-digit 7-segment display: digit value on PC0-PC3, digit select on PB0-PB2, multiplexed in software
- Temperature sensor on ADC5 and a light-dependent resistor (LDR) on ADC4
- RS-232 link to a PC, viewed in Tera Term at 9600 baud, 8 data bits, no parity, 1 stop bit

## Build

Compiled with **avr-gcc** and **avr-libc**. To build one program yourself:

```bash
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o lab.elf lab-05-adc/exercise1.c
avr-objcopy -O ihex -R .eeprom lab.elf lab.hex
```

Then flash `lab.hex` with your programmer, for example `avrdude -c <programmer> -p m328p -U flash:w:lab.hex`.

GitHub Actions compiles every lab on each push and keeps the `.hex` files as a download ([latest run](https://github.com/jadenchua-dot/MicroController-embedded-system/actions/workflows/build.yml)).

## What these labs cover

- Configuring I/O with data-direction registers and reading inputs with pull-ups
- Bit masking (`|=`, `&= ~`, `^=`) so one pin changes without disturbing the rest
- Lookup tables and software multiplexing for 7-segment displays
- Polling the ADC and scaling raw readings into real units
- Configuring the UART baud rate and sending and receiving bytes
- Writing interrupt service routines and choosing edge triggers
