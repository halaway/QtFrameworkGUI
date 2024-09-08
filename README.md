<h1 align="center"> Qt Framework GUI </h1>

<h3>A simple Qt6.5 program for creating both native and browser based GUI applications, built with CMake, Qt Creator, and Emscripten.</h3> 

## Description
Following a previous implementation of a Sudoku Board using the Simple Direct Media Layer library, 
this project utilizes a more modern framework that handles extensive widget customization, event handling, and cross-platform functionality 
along with I/O and file imports. The project also enables web support using WebAssembly, a binary instruction format capable of running alongside Javascript inside a 
virtual environment such as a web browser. The toolchain, Emscripten, will be used to compile our C++ GUI 
application into WebAssembly ( `WASM` ) and Javascript (`js`) files.


## Getting Started

### Dependencies

* Qt 5/6 
* CMake 
* Launch Qt VSCode Extension 
* GCC (Linux/macOS) – C++ compiler (install via ```apt``` or ```brew```)
* Clang (macOS/Linux) – C++ Compiler (x86/x64)
* Xcode Command Line Tools - Required for macOs
* Emscripten – Compiling C++/C projects to WebAssembly

## Building

### VSCode macOs

Running on mac using VSCode requires the Launch Qt Extension along with CMake. 
Using WebAssembly for browser compilation requires setting system Path for Emscripten: ```source "$HOME/emsdk/emsdk_env.sh" ```

To Run: 

```
- cd build
- cmake .. 
- cmake —build .
- open Project.app
```
### Qt Creator 
Using the Qt IDE:
```
- Run cmake
- Run
```

To run the application on a web browser using Qt Creator, ensure that compatible versions of Emscripten and WebAssembly are installed. Then 
set the Devices' Emscripten SDK path ```/users/path/to/emsdk/``` 
and Build using the WebAssembly Qt Kit.

## Native Desktop GUI Build
<img width="600" alt="gui_app_build" src="https://github.com/user-attachments/assets/516c296a-6859-4ce8-8b92-8367f56c6c21">

## WebAssembly Based Browser Build 
<img width="600" alt="web_based_gui" src="https://github.com/user-attachments/assets/c2d97e53-41cb-4e44-b5fb-215aa0ef5907">

