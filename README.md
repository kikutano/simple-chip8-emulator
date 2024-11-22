# Simple Chip 8 Emulator in C
I was always fashinating about how emulators are coded. So finally I started to write my own first emulator fo Chip-8 system. This is the simplest emulator that you can write, and it's a good starting point for me to understand somenthing about emulations world :). So I keep all code as simple as I can, using plain C and SDL2. I will integrate a Tutorial to make more understable the code and allows everybody to start to write they own emulator. Stay tuned!

# State of emulator
This project emulate **only Chip-8 basic** instructions. No extensions for now! As references to test the emulator I used this github project [here](https://github.com/Timendus/chip8-test-suite). It's a suite of testing roms to understand if your emulator it's working fine. 

#### Test passed ✔️
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
- Audio not supported yet
- Quirks test has some gliches
- Keyboard half dosen't pass

# Resources
- http://www.codeslinger.co.uk/pages/projects/chip8.html
- https://en.wikipedia.org/wiki/CHIP-8
- https://github.com/Timendus/chip8-test-suite