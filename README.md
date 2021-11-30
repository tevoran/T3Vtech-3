# T3Vtech-3
A 3D game engine in C.

## Dependencies

T3Vtech-3 currently needs SDL2 and GLEW as a dependency. The other dependency that is used is used as a submodule.

## Building

If you are trying to build the repository for the first time then you need the following git commands

```
git clone https://github.com/tevoran/T3Vtech-3.git
git submodule update --init --recursive
```

and to prepare the repository a build directory has to be created.

```
mkdir build
cd build
```

The final step is using cmake and on Linux make to build the 
engine.

```
cmake ..
make
```

