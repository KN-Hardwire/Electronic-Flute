# Software

## Instalation
You can install already compiled firmware on github by going to **Actions**
section and choosing the latest passing commit on the **build** workflow.
There you will find the **'firmware'** binary ready to download.

## Dependencies
- pico-sdk for C/C++ (included as submodule)

## Compilation
To compile the firmware locally you must first:   
Initialize pico-sdk and its submodules:
```
git submodule update --init --recursive
```

Create a build directory and from it run cmake: 
```
mkdir build
cd build
cmake ..
```

There are CMake flags available for easier debugging and development,
which you don't need to worry about them for standard compilation:   
*No debug and int32_t type on default*
```
-DDEBUG_MODE=<OFF/ON> -DPROJECT_TYPE=<INT/FLOAT>
```

If succesful, run the Makefile from build directory:
```
make
```
