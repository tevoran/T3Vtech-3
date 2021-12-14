# Building a Project With T3Vtech-3

If you want to build a project with the T3Vtech-3 engine. It is recommended to use the engine as a git submodule.

In the directory where you want to place the engine repository you have to execute

```
git submodule add https://github.com/tevoran/T3Vtech-3.git
```

When your repo is being initialized or when you are initializing you submodules then you have to execute

```
git submodule update --init --recursive
```

After the initialization of the engine submodule it is necessary to create a CMakeLists.txt file if you are using CMake. This explanation will use CMake, if you are using another method of building your project then you have to translate the following steps into your own procedure.

The CMakeLists.txt from this directory can be used as a base. It just needs to be adapted to your local directory names. There are some annotations where to change things.

After you edited the CMakeLists.txt and it is in your root directory of your repository then you can use the following commands to build your project.

```
mkdir build
cd build
```

```
cmake ..
make
```

Your project should be executable now.