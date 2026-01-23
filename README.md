# Prototype-RPGS

This repository is archive for the development build of the prototype.
Features fictional city inspired by real life architecture.
There are 3 protagonists in this game.
The 1st protagonist is a chill guy.
Story and map are in progress.
The 2nd and 3rd protagonists aren't planned yet.

# Install Dependencies

## Linux (Debian/Ubuntu)

1. Install build tools and dependencies:
   ```bash
   sudo apt install build-essential git libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
   ```

2. Install Raylib:
   ```bash
   git clone https://github.com/raysan5/raylib.git raylib
   cd raylib/src/
   make PLATFORM=PLATFORM_DESKTOP
   sudo make install
   ```

## Windows (MinGW)

1. Install a MinGW compiler (e.g., MSYS2 or w64devkit).
2. Install Raylib.
   - **MSYS2**: Run `pacman -S mingw-w64-x86_64-raylib`.
   - **Manual**: Download the MinGW release from [Raylib Releases](https://github.com/raysan5/raylib/releases), and ensure the `include` and `lib` directories are in your compiler's search path (or update the Makefile).

# Patch notes for version 0.1

- Migrated to raylib 5.
- Transitioned to **Full 3D Environment** with city districts and street-level geometry.
- Implemented **GTA-style Third-Person Orbit Camera** with smooth mouse control.
- Developed a **Multi-Protagonist System** (3 Characters) with real-time switching HUD (Alt key).
- Added a **Driveable Vehicle System** with support for multiple active cars (up to 12).
- Implemented a **Cheat Console** (Tilde `~` key) with commands for speed, teleportation, and spawning vehicles.
- Refactored codebase into a **Professional Modular Structure** (src/include/bin/obj).
- Added a working collision detection.
- Improved project maintenance with a robust **Makefile** and **.gitignore**.
- Optimized rendering with **4x MSAA support**.

# Patch notes for version 0.2

- Added **Save System** with support for multiple save slots (1-5).
- Added **Load System** with support for multiple load slots (1-5).
- Added GitHub Actions CI for Linux and Windows.
- Added Coordinate System
- Fixed Collision Detection
- Added Pause Menu
- Fixed console bug

# Commands & Cheats

### Controls
- **WASD**: Move Player / Drive Vehicle
- **Space**: Ascend (Cheat Speed) / Multi-use
- **F**: Enter/Exit Vehicle
- **Left Alt**: Hold to show Character Switcher (Click to select)
- **F3**: Toggle Coordinate Display
- **ESC**: Toggle Pause Menu
- **Tilde (`~`)**: Open Cheat Console

### Cheat Console Commands
Open the console with `~` and type any of these commands:
- `FAST`: Set movement speed to 60.
- `SLOW`: Set movement speed to 5.
- `NORMAL`: Set movement speed to 15.
- `NY`: Teleport to first district.
- `DHAKA`: Teleport to second district.
- `SHENZEN`: Teleport to third district.
- `CAR`: Spawn a vehicle at your location.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0). See the [LICENSE](LICENSE) file for details.
