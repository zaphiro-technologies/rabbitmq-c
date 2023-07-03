# Getting started

This library serves as a wrapper between the native rabbitmq-c library 
and LabVIEW, with its main objective being the adaptation of data types and 
memory allocation for rabbitmq-c functions.

## How to build library

This library can be built alongside the main rabbitmq-c library using CMake.

```bash
mkdir build ; cd build
cmake ..
cmake --build .
```

The LabVIEW library build can be disabled by changing the default value of the
 variable "BUILD_LABVIEW" to "OFF" in the main CMakeLists.txt file.

```bash
option(BUILD_LABVIEW "Build LabVIEW shared library" ON)
```
