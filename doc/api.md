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

## Setting Parameters

### Field of View

The field of view only affects 3D scenes but it can be set differently in each frame at all times. The effect will be visible in the next frame. The input parameter is given in radians. So 1.0 * tt_PI will be 180° and 0.5 * tt_PI will be 90°. Because of the usage of tan() in the projection matrix it is recommended to have your field of view smaller than 180°.

```c
void tt_set_fov(float radians);
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

Please note the pointer pointer as an argument. This pointer pointer is used to prevent set the objects pointer to NULL to avoid issues when trying to delete an object twice.

```c
void tt_3d_object_delete(tt_3d_object **object);
```

#### Transformations

##### Translation / Setting a position

Setting the position of a 3D object is also a quite easy task. Just create a tt_vec3 vector with the desired position and give the address of the vector and the object pointer to the function tt_3d_object_set_position().

```c
void tt_3d_object_set_position(tt_3d_object *object, tt_vec3 *position);
```

##### Scaling

A 3D object can be scaled in each axis differently. This is the reason why a vector is for scaling instead of a simple scalar value.

```c
void tt_3d_object_scale(tt_3d_object *object, tt_vec3 *scale);
```

##### Rotation

Rotations are quaternion based. This means that no matter what combination of rotations you have ends up in a gimbal lock. Additionally this gives the freedom to rotate around any arbitrary axis and not just the X, Y and Z axes.

```c
void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
```

An example of usage:
```c
//rotating an object 90° around the X axis
tt_vec3 rot_axis={1,0,0};
float rot_angle=0.5*tt_PI;
tt_3d_object_rotate(object, &rot_axis, rot_angle);
```

#### Quads

A created 3D object can be converted into a quad by using the function tt_3d_object_make_quad().

```c
void tt_3d_object_make_quad(tt_3d_object *object)
```