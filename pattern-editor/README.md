# BulletJSON Pattern Editor

This is the implementation of BulletJSON in C++. It also includes a real-time pattern editor that allows you to write patterns directly in JSON or using UI elements.

# Dependencies

- [Raylib 5.5](https://github.com/raysan5/raylib/): Used for graphics rendering and input handling.
- [ImGui](https://github.com/ocornut/imgui): Used to manage UI.
- [rlImGui](https://github.com/raylib-extras/rlImGui): Used to communicate Raylib with ImGui.
- [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit): Used on JSON editor.

Build dependencies:
- [CMake](https://github.com/Kitware/CMake): Build system generator.
- [EmSDK](https://emscripten.org/docs/getting_started/downloads.html): Used to generate HTML5 Web builds.
- [Ninja](https://github.com/ninja-build/ninja): Used with EmSDK to generate HTML5 Web builds.
- [mingw-w64](https://www.mingw-w64.org/build-systems/cmake/): Used to generate Windows builds directly on Linux.

# Build

## On Linux

Build for Linux:
```bash
$ cmake -B build
$ cmake --build build

# Running
$ ./final-builds/Linux/BulletHellPatternEditor
```

Build for Web:
```bash
$ source ~/emsdk/emsdk_env.fish
$ cmake -S . -B build -G Ninja -DPLATFORM=Web "-DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" -DCMAKE_BUILD_TYPE=Release
$ cmake --build build

# Running
$ cd ./final-builds/Web
$ python3 -m http.server 1337 # access http://localhost:1337/BulletHellPatternEditor.html on any web browser
```

Build for Windows:
```bash
$ cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw64.cmake
$ cmake --build build

# Running
$ wine ./final-builds/Windows/BulletHellPatternEditor.exe
```

## On Windows

Maybe someday... Just download from releases page or use the Web version