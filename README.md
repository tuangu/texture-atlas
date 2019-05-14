This application's purpose is to generate a texture atlas from png and jpeg images. 
It outputs a new texture atlas in png format and a metadata file that contains
each image's position (xy-axis), width, and height.

## Binary
You can find the pre-built binary for Ubuntu (built on Ubuntu 18.04 with GCC 8.3) and Window (built on Windows 10 with Visual Studio 15 2017) in the *bin* directory.

## Building
You can build this project with [CMake](https://cmake.org/).

Get the code:
```
git clone --recursive https://github.com/tuangu/texture-atlas.git
```

### Windows
Make sure you are using Visual Studio 15 2017 or newer for filesystem support. All the commands are run within Powershell.
* Create a folder called **build-msvc**
```
mkdir build-msvc
cd build-msvc
```
* Generate projects to target **x64**
```
cmake -G "Visual Studio 15 2017 Win64" .. 
```

* Navigate to the project folder to open the solution file ({project_name}.sln).

Otherwise, you can use cmake-gui to configure and generate the project.

### GCC
Make sure GCC version > 8.0 for filesystem support.

* Create a folder called **build** and run CMake inside
```
#export CC=path/to/gcc-8
#export CXX=path/to/g++-8

mkdir build
cd build
cmake ..
```
* Build the project, then run the application (*texture-atlas-bin* in this case) or the tests (*texture-atlas-tests* in this case)
```
make

# Run the application
./texture-atlas-bin path/to/images/folder

# Run the tests
./texture-atlas-tests
```
