# MeddySDKCLI

A command-line interface application for Meddy.

For a superproject with all components Meddy has to offer, see [MeddySDK](https://github.com/ChristianHinko/MeddySDK).
- This provides the individual MeddySDK libraries, tied together with CMake.

## Dependencies

MeddySDKCLI
- [MeddySDK_Meddyproject](https://github.com/ChristianHinko/MeddySDK_Meddyproject)

## Build System ⌨

Built with CMake - cross-platform, standardized, and IDE-friendly.

We provide CMake presets, which handle feeding arguments to CMake for you.

### IDE Support

Most IDEs provide built-in CMake integration.

#### VS Code

Has the "CMake Tools" and "C/C++" extensions, both developed by Microsoft.

#### Visual Studio

Has very nice integration, but they seem behind when it comes to supporting the latest CMake features. I've had experiences where I have to switch to VS Code because of this.

## Build Instructions 🔨

This project is fully isolated from its dependencies, and therefore must be tied together by a superproject. See [MeddySDKStandalone](https://github.com/ChristianHinko/MeddySDKStandalone) for a complete build setup.

### 1. Invoke CMake on the Project (the Configure Step)

Command line: `cmake --preset="windows-x64-debug"`.

IDE: Choose the `windows-x64-debug` configure preset, and "configure" the CMake project.

### 2. Invoke a Build Command

Command line: `cmake --build --preset="windows-x64-debug"`.

IDE: Choose the `windows-x64-debug` build preset, and "build" it.

## Package Instructions 📦

Here's how to package the build into a distributable product.

### 1. Build the Project

See "Build Instructions" above.

### 2. Invoke CPack

Command line: `cpack --preset="meddysdkcli-windows-x64-debug-nsis"`.

IDE: Choose the `meddysdkcli-windows-x64-debug-nsis` package preset, and "package" it.

## Test Instructions 🧪

Here's how to run automated tests, to verify that our code behaves as intended.

### 1. Build the Project

See "Build Instructions" above.

### 2. Invoke CTest

Command line: `ctest --preset="meddysdkcli-windows-x64-debug"`.

IDE: Choose the `meddysdkcli-windows-x64-debug` test preset, and "run tests".
