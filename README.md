# Simple Chip 8 Emulator in C
I have always been fascinated by how emulators are built. So, I finally decided to write my first emulator for the Chip-8 system. The Chip-8 is one of the simplest systems you can emulate, making it a perfect starting point for me to learn more about the world of emulation. I kept the code as straightforward as possible, using plain C and SDL2.

To help others get started with their own emulators, I plan to integrate a tutorial explaining the code in detail. Stay tuned!

# State of emulator
This project emulates only the basic Chip-8 instructions. No extensions are implemented yet! As a reference to test the emulator, I used this [Chip-8 Test Suite](https://github.com/Timendus/chip8-test-suite) on GitHub. It includes a set of testing ROMs to verify if your emulator is functioning correctly.

#### Tests passed ✔️
- [CHIP-8 splash screen](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#chip-8-splash-screen) ✔️
![CHIP-8 splash](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/chip-8-logo.png)
- [IBM Logo](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#chip-8-splash-screen) ✔️
![IBM Logo](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/ibm-logo.png)
- [Corax+ opcode test](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#corax-opcode-test) ✔️
![Corax+ opcode test](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/corax+.png)
- [Flags test](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#flags-test) ✔️
![Flags test](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/flags.png)
- [Quirks test](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#quirks-test) ✔️⚠️
![Quirks test](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/quirks-platform.png)
- [Keypad test](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#keypad-test) ✔️⚠️
![Keypad test](https://github.com/Timendus/chip8-test-suite/raw/main/pictures/keypad-menu.png)

### Kwon Issues️ ⚠
- Audio is not yet supported.
- The Quirks Test has some glitches.
- The Keyboard Test fails Halt test.

# Resources
- http://www.codeslinger.co.uk/pages/projects/chip8.html
- https://en.wikipedia.org/wiki/CHIP-8
- https://github.com/Timendus/chip8-test-suite