# Bullet Hell Pattern Editor

This project is a Bullet Hell / Danmaku Pattern Editor, you can create and edit patterns for any kind of bullet hell game. It also supports [BulletML](https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html) XML Files.

Most pattern examples are from [BulletMLExamples](https://github.com/dmanning23/BulletMLExamples).

The used sprites are from the game DoDonPachi Daiffukatsu, developed by CAVE. All rights reserved.

# Dependencies

- [Raylib 5.5](https://github.com/raysan5/raylib/): Used for graphics rendering and input handling.
- [ImGui](https://github.com/ocornut/imgui): Used to manage UI.
- [rlImGui](https://github.com/raylib-extras/rlImGui): Used to communicate Raylib with ImGui.
- [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit): Used to draw XML and JSON files.

Build dependencies:
- [CMake](https://github.com/Kitware/CMake): Build system generator.
- [EmSDK](https://emscripten.org/docs/getting_started/downloads.html): Used to generate HTML5 Web builds.
- [Ninja](https://github.com/ninja-build/ninja): Used with EmSDK to generate HTML5 Web builds.
- [mingw-w64](https://www.mingw-w64.org/build-systems/cmake/): Used to generate Windows builds directly on Linux.

# Build

## On Linux

Build for Linux:
```bash
cmake -B build
cmake --build build

# Running
./final-builds/Linux/BulletHellPatternEditor
```

Build for Web:
```bash
source ~/emsdk/emsdk_env.fish
cmake -S . -B build -G Ninja -DPLATFORM=Web "-DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Running
cd ./final-builds/Web
python3 -m http.server 1337 # access http://localhost:1337/BulletHellPatternEditor.html on any web browser
```

Build for Windows:
```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw64.cmake
cmake --build build

# Running
wine ./final-builds/Windows/BulletHellPatternEditor.exe
```

## On Windows

Maybe someday... Just download from releases page or use the Web version