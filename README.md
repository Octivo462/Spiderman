# Spider-Cube

A small C++ and SFML physics demo: a red cube falls under gravity and, while you hold the left mouse button, swings from a rope anchored at your cursor — Verlet-integration style, like a simplified grappling hook / Spider-Man swing.

## How It Works

- The cube falls freely under gravity when no rope is attached.
- Hold the **left mouse button** anywhere in the window to anchor a rope at that point and start swinging.
- Release the button to detach the rope and let the cube fall freely again.
- The cube bounces off the window's edges (floor, ceiling, and side walls).

## Controls

| Input | Action |
|---|---|
| Hold Left Mouse Button | Attach rope to cursor position and swing |
| Release Left Mouse Button | Detach rope, fall freely |
| Close window | Quit |

## Requirements

- A C++17-capable compiler (GCC, Clang, or MSVC)
- [SFML](https://www.sfml-dev.org/) (Graphics, Window, System modules — version 2.5 or 2.6 recommended)

No external assets (fonts/images) are needed — the cube is drawn as a plain colored rectangle.

## Building

### Linux / macOS (g++)

Install SFML first (`sudo apt install libsfml-dev` on Debian/Ubuntu, or `brew install sfml` on macOS), then:

```bash
g++ -std=c++17 main.cpp -o spider_cube -lsfml-graphics -lsfml-window -lsfml-system
./spider_cube
```

### Windows (Visual Studio)

1. Create a new C++ project and add this source file to it.
2. Install SFML (e.g. via [vcpkg](https://github.com/microsoft/vcpkg): `vcpkg install sfml`) and link the graphics, window, and system components.
3. Build and run — no additional files need to be copied alongside the executable.

### CMake (cross-platform, optional)

```cmake
cmake_minimum_required(VERSION 3.16)
project(SpiderCube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(spider_cube main.cpp)
target_link_libraries(spider_cube sfml-graphics sfml-window sfml-system)
```

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Tuning the Physics

All of the swing behavior is controlled by a handful of constants near the top of `main()`:

- `gravity` — downward acceleration applied every frame
- `max_stretch` — how far the rope can stretch beyond its rest length before it becomes rigid (like a max rope length)
- `stiffness` — how strongly the rope pulls the cube back toward its rest length when stretched (higher = snappier, less elastic)
- `friction` — velocity damping per frame (closer to 1.0 = less air resistance)
- `bounce` — how much velocity is retained (and reflected) when the cube hits a wall/floor/ceiling

Adjusting these lets you make the swing feel floatier, snappier, bouncier, etc.

## Notes

- Movement uses Verlet integration (position is derived from the previous position rather than tracking velocity directly), which is why `prev_pos` is stored and updated each frame.
- The rope's rest length is set to the distance between the cube and the cursor at the moment you click, so swings starting closer to the cube will have a shorter rope than swings starting farther away.
