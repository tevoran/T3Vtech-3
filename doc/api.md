# T3Vtech3 Game Engine library API

The core part of the engine is compiled as a static library and is ready to be used with C and C++.

## Initialization

The engine has to be initialized by calling the function

```c
bool tt_init(
	const char *window_name,
	const uint32_t res_x, 
	const uint32_t res_y,
	const bool fullscreen);
```

If you call other T3Vtech3 functions without initializing the engine first then the behaviour is undefined.

## Quitting

At the end of the game the engine will clean itself up. So there is no need to actually calling tt_quit() yourself.

```c
void tt_quit();
```

## Frame Update

To show what has been drawn onto the screen you have to call tt_new_frame(). It will show the latest frame and will update some things that need to be updated on a per frame basis.

```c
void tt_new_frame();
```

## 3D

### 3D Objects

A 3D object has the following life cycle. At first you need to create an empty 3D object which you have to destroy at the end of its life. While it is alive it is usually part of the rendering process, where it gets rendered each frame if it's visible. Also it is possible to modify it during its life cycle. This kind of modification is necessary to give the 3D object a specific shape or apply transformations like rotations to it.

#### Creation of a 3D Object

A 3D object gets created by calling tt_3d_object_new(). This basically starts the 3D object's life but immediately after its creation there is nothing to display yet. It is necessary to add at least a model to it.

```c
tt_3d_object* tt_3d_object_new();
```

#### Destruction of a 3D Object

At the end of its life it is necessary to delete a 3D object. It can't get displayed anymore. But it is important to note that deleting the object doesn't free the resources that are used by the object. 

```c
void tt_3d_object_delete(tt_3d_object **object);
```