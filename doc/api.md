# T3Vtech3 Game Engine library API

The core part of the engine is compiled as a static library and is ready to be used with C and C++.

## Initialization

To be able to initialize the engine the main header tt.h has to be included.

```c
#include <tt.h>
```

The engine has to be initialized by calling the function

```c
bool tt_init(
	const char *window_name,
	const uint32_t res_x, 
	const uint32_t res_y,
	const bool fullscreen,
	const int msaa,
	const bool quiet);
```
The msaa value is used for anti-aliasing. The engine currently uses MSAA for anti-aliasing. Typical values are 0 (no anti-aliasing), 2, 4 or 8. The higher the value the more expensive a frame becomes.

The quiet toggle tells the engine if it should show non-error messages or not. Error messages are still visible in quiet mode.

If you call other T3Vtech3 functions without initializing the engine first then the behaviour is undefined.

## Quitting

There is no need to call tt_quit() explicitly. It will be called at the end of the program's execution anyway. It is only necessary to clean the resources that you loaded on your own during the engine's runtime.

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

### Gouraud Shading

Gouraud shading is a shading method that needs quite little resources in comparison with other methods. It is possible to activate or deactivate it by calling 

```c
void tt_gfx_gouraud_shading(bool active);
```

When active is true gouraud shading will activated and with false it will be deactivated.

### Fog

Fog can be activated with tt_gfx_fog_set_active(true) while the other two functions are used to determine the appearance of the fog.

```c
void tt_gfx_fog_set_active(bool fog_active);
void tt_gfx_fog_set_color(const tt_vec3 *fog_color);
void tt_gfx_fog_set_max_distance(float distance);
void tt_gfx_fog_set_min_distance(float distance);
```

## 3D

### Camera

In 3D settings a camera is used as a point of view. It can be positioned anywhere in the world. Additionally the camera can be rotated around any axis.

```c
void tt_camera_set_position(tt_vec3 *position);
```

```c
void tt_camera_rotate(tt_vec3 *rot_axis, float radians);
```

#### Getting the Current Viewing Direction

If necessary it is possible to get the current viewing direction of the camera by calling

```c
tt_vec3 tt_camera_view_direction();
```

#### Using a FPS Camera

T3Vtech-3 natively supports FPS style cameras. It is simply necessary to give the engine the current pitch and roll in radians. Usually you want to get these by using the mouse input and adding up the pitch and roll in static float variables.

```c
void tt_camera_fps(float pitch_radians, float yaw_radians);
```

An example of setting up a FPS camera.

```c
//while initializing the engine/level/...
tt_input_mouse_set_relative_mode(true);

//inside the main loop
static float yaw_radians=0;
static float pitch_radians=0;
int dx, dy;
float time=tt_time_current_frame_s();
tt_input_mouse_relative_motion(&dx, &dy);
pitch_radians+=(float)dy * time * 0.02;
yaw_radians+=(float)dx * time * 0.02;
tt_camera_fps(pitch_radians, yaw_radians);
```

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

#### Enabling/Disabling Lighting Effects

It can be toggled whether a 3D object is affected by light or not. This comes in handy if one wants to place a light bulb or something else that emits light. By default 3D objects are affected by light.

```c
void tt_3d_object_light_affected(tt_3d_object *object, bool toggle);
```

#### Making a 3D Object visible/invisible

3D objects can be toggled to be visible or invisible. This is helpful if you already prepared an object but you need display it later.

```c
void tt_3d_object_make_invisible(tt_3d_object *object, bool toggle);
```

By default a 3D object is visible.

True makes it invisible and false makes it visible.

#### Enabling/Disabling Back Face Culling

Usually the back face culling is set to on for all objects but in some cases it is desired to have back face culling turned off for some objects. It can be turned on or off by calling.

```c
	void tt_3d_object_back_face_culling(tt_3d_object *object, bool toggle);
```

With the toggle set to true it is turned on and when it is set to false it is turned off for the object.

#### Usage of a Texture

To use a texture to cover a 3D object it needs to be created first by calling tt_3d_texture_new() and is available until the call the of tt_3d_texture_delete(). In between the texture is usable on as many models as desired. And if no texture is specified then the pink default texture will be used.

In order to use a created texture on a 3D object call tt_3d_object_use_texture().

```c
void tt_3d_object_use_texture(tt_3d_object *object, tt_3d_texture *texture);
void tt_3d_object_use_default_texture(tt_3d_object *object); 
```

If the texture isn't need anymore on this particular engine you can simply use another texture or use the default texture by calling tt_3d_object_use_default_texture().

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
float rot_angle=0.5*tt_PI; //radians instead of degrees are used
tt_3d_object_rotate(object, &rot_axis, rot_angle);
```

In addition to a regular rotation, it is also possible to rotate a 3D object exactly like a previously rotated 3D model.

```c
void tt_3d_object_rotate_like(tt_3d_object *object_target, tt_3d_object *object_already_rotated);
```

#### Quads

A created 3D object can be converted into a quad by using the function tt_3d_object_make_quad().

```c
void tt_3d_object_make_quad(tt_3d_object *object)
```

#### Cubes

A created 3D object can also become a cube. It is just necessary to use

```c
void tt_3d_object_make_cube(tt_3d_object *object);
```

#### Custom Models Loaded From Files

Custom models are basically the content of a 3D model file (currently only OBJ is supported) that can be used as 3D objects. You can load a 3D model from a file with 

```c
tt_3d_custom_model* tt_3d_custom_model_load_file(const char *path);
```

This will give you a 3D custom model object that can be associated with 3D objects with

```c
void tt_3d_object_use_custom_model(tt_3d_object *object, tt_3d_custom_model *model);
```

The 3D custom model needs to be only loaded once into the video memory and can be associated with as many 3D objects as desired. After the last rendering instance is not used anymore you may want to delete the 3D custom model. In order to delete it you need to call 

```c
void tt_3d_custom_model_delete(tt_3d_custom_model **model);
```

Here is an example of usage

```c
tt_3d_object *ship=tt_3d_object_new();
tt_3d_custom_model *ship_model=tt_3d_custom_model_load_file("assets/models/ship/ship.obj");
tt_3d_texture *tex=tt_3d_texture_new("assets/models/ship/ship.bmp", false);
tt_3d_object_use_texture(ship, tex);
tt_3d_object_use_custom_model(ship, ship_model);
```

#### Batched Objects

If it happens that too many 3D objects are getting rendered it might be wise to batch some of the 3D custom models up into one 3D object. This will increase performance in some instances strongly as this will decrease the necessary amount of communication between RAM and video RAM/CPU and GPU. Though batching up big amounts of geometry might take up to a couple of seconds. So this isn't a one size fits all solution but if you have many static 3D objects that use the same 3D custom model then this might improve performance.

A new 3D batch object is created by calling
```c
tt_3d_batch_object* tt_3d_batch_object_new();
```

When it comes to the actual batching of 3D objects then it is necessary to call this
```c
void tt_3d_batch_object_batch_custom_model_objects(
	tt_3d_batch_object *batch_object,
	tt_3d_custom_model *model,
	unsigned int num,
	tt_3d_object **object);
```
It is important to note that the used 3D objects will be used for their transformations such as rotation and scaling. This will lead to a usable batched object that cointains only the the custom model that was specified but with the previously specified locations, rotations and scalings of the 3D objects in the list.
In many cases you might want to make the previously existing 3D objects invisibly or delete them to avoid unnecessary duplicates being rendered.

After the batch object was created it can be used with a regular 3D object by calling
```c
void tt_3d_object_use_batch_object(tt_3d_object *object, tt_3d_batch_object *batch_object);
```

The batch object can be destroyed after its usage by calling
```c
void tt_3d_batch_object_delete(tt_3d_batch_object **batch_object);
```

#### Textures

Textures are an object that is very similarily used like "tt_3d_object"s. They are created and deleted and in between they can be used to cover 3D models. If no texture is specified for a 3D object then the object will get a pink default texture.

```c
tt_3d_texture* tt_3d_texture_new(const char *path, const bool bilinear_filtering);
void tt_3d_texture_delete(tt_3d_texture **texture);
```

An example of usage:

```c
tt_3d_object *quad=tt_3d_object_new();
tt_3d_object_make_quad(quad);
tt_3d_texture *tex=tt_3d_texture_new("path/to/asset.png", false);
tt_3d_object_use_texture(quad, tex);

//render and do stuff


tt_3d_texture_delete(&tex);
```

#### Collisions

It can be checked if two 3D objects are colliding with each other.

Currently only axis aligned bounding boxes are available. But they follow the scaling and rotation of the initial model. Sadly the rotations can make the aabb somewhat inaccurate which needs to be considered if rotating is necessary. Besides that the return value is true if there is a collision and is false if there is none.

```c
bool tt_3d_object_colliding_aabb(tt_3d_object *a, tt_3d_object *b);
```

### Lighting

#### Ambient Light

Ambient light is just a diffuse light that seems to come from everywhere equally. It has two functions to manipulate it.

```c
void tt_ambient_light_set_strength(float strength);
void tt_ambient_light_set_color(tt_vec3 *color);
```
It is always on but if it is not desired to have ambient lighting enabled it is possible to set its strength to 0.0f.

#### Directional Lights

A directional light is a light that is similar to the sun. It appears to be infinitely far away. T3Vtech-3 currently supports up to 8 directional lights.

A new directional light can be created by calling 

```c
tt_dir_light tt_directional_light_new();
```

The function returns a light_id. It is used to change attributes of that particular directional light. It is also used to delete light sources.

```c
void tt_directional_light_delete(tt_dir_light light_id);
```

It is important to note that the directional light sources are ordered in a stack like manner. Your most important light should be the first one that you create. If you delete your latest light then only this one gets deleted. But if you delete your second latest light then the latest AND the second latest light will be deleted.

##### Setting Parameters

It is possible to change the individual lights parameters. These parameters are direction, strength and color.

The direction is set by calling

```c
void tt_directional_light_set_direction(tt_dir_light light_id, tt_vec3 *direction);
```

The light_id is the return value of a light created by tt_directional_light_new(). And direction is a tt_vec3 vector. The struct contains x, y and z members.

The strength is changed by calling

```c
void tt_directional_light_set_strength(tt_dir_light light_id, float strength);
```

The strength is a floating point value. In most cases you want to have the value between 0.0f and 1.0f while 0.0f is basically a light that affects nothing.

The last changeable property of a directional light is the color.

```c
void tt_directional_light_set_color(tt_dir_light light_id, tt_vec3 *color);
```

The color values are stored in a tt_vec3 vector which is a struct containg the members x, y and z. X gets interpreted as r, y as g, z as b values. The individual color values have to be between 0.0f and 1.0f.

#### Point Lights

T3Vtech-3 allows currently up to 128 point lights at a time. They act like the directional lights in a stack like manner.
It is possible to create a new point light with 

```c
tt_point_light tt_point_light_new();
```

This adds a new point light at the end and returns the light_id as an integer. 

One or more lights can be deleted by calling

```c
void tt_point_light_delete(tt_point_light light_id);
```

This will delete all the point lights that have been created since the light that has the light_id. This can be used to delete all point lights by deleting the first one.

##### Setting Parameters

Point lights have several different parameters than can be changed. The intensity or strength of the point light can be set by calling

```c
void tt_point_light_set_strength(tt_point_light light_id, float strength);
```

The color of the point light can be set by calling

```c
void tt_point_light_set_color(tt_point_light light_id, tt_vec3 *color);
```

Colors are represented by a vector of three floats. Each basic color (red, green and blue) gets represented with a float between 0.0f and 1.0f.

Since a point light has a location unlike other kinds of lighting, the position can be set by calling

```c
void tt_point_light_set_position(tt_point_light light_id, tt_vec3 *position);
```

## 2D

### 2D Objects

A 2D object has the following life cycle. It needs to be created first. After its initial creation you need to tell the engine what kind of object you want to make it. When this is done you can start to render it in your game's main loop. At the end of its usage it is very wise to delete the object.

#### Creation of a 2D Object

To create a 2D object simply call

```c
tt_2d_object* tt_2d_object_new();
```

In most cases you want to make your 2D object a sprite. To do so, simply call

```c
void tt_2d_object_make_sprite(tt_2d_object *object);
```

#### Deletion of a 2D Object

If a 2D object is not necessary anymore then it can be deleted. It is just necessary to call 

```c
void tt_2d_object_delete(tt_2d_object **object);
```

#### Rendering of a 2D Object

Unlike 3D objects 2D objects are not rendered automatically in T3Vtech-3. They are not rendered automatically because the engine can not know in which order the engine's user wants them to be rendered. Therefor the responsibility is given to the user. A 2D object can be issued to be rendered for a frame by calling

```c
void tt_2d_object_render(tt_2d_object *object);
```

#### Rotation of a 2D Object

2D objects can be rotated by calling

```c
void tt_2d_object_rotate(tt_2d_object *object, float radians);
```

#### Scaling of a 2D Object

Scaling 2D objects is done by calling 

```c
void tt_2d_object_scale(tt_2d_object *object, tt_vec2 *scale);
```

#### Translation of a 2D Object

Setting the position of a 2D object is done by calling

```c
void tt_2d_object_set_position(tt_2d_object *object, tt_vec2 *position);
```

#### 2D Textures

##### Creation of 2D Textures

When a sprite is created one usually doesn't want to simply display the pink default texture. To create a new 2D texture, that can be used for many different 2D objects if desired, call 

```c
tt_2d_texture* tt_2d_texture_new(const char *path, const bool bilinear_filtering);
```
Unlike 3D textures T3Vtech-3's 2D textures support transparency. 

It is also possible to create 2D textures from arbitrary data as well. If you have an array of pixel data in the RGBA and unsigned char format then you can call the function

```c
tt_2d_texture* tt_2d_texture_new_from_RGBA(
	void *image_data, 
	const int res_x,
	const int res_y,
	const bool bilinear_filtering);
```

instead. The handling of the texture won't be any different, no matter the it was created. 

##### Usage of 2D Textures

When it needs to be used with a 2D object then it is just necessary to call

```c
void tt_2d_object_use_texture(tt_2d_object *object, tt_2d_texture *texture);
```

##### Deletion of 2D Textures

If a 2D texture is not used anymore then it can be deleted by calling

```c
void tt_2d_texture_delete(tt_2d_texture **texture);
```

In the case that there is not active 2D texture assigned to a sprite then the default texture will be assigned in the next rendering of the sprite.

##### 2D Text

2D Text will be rendered by the engine into 2D textures that can then be used as regular 2D textures on sprites. These 2D text textures can also be deleted in the same way as regular 2D textures.

To create a 2D text texture call

```c
tt_2d_texture* tt_2d_texture_make_text(
	const tt_font *font,
	const char *text,
	const tt_color_rgba_u8 color);
```

The tt_color_rgba_u8 struct is a simple struct that contains the color information that is necessary for the text to be rendered.

```c
struct tt_color_rgba_u8
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} typedef tt_color_rgba_u8;
```

A complete example for the creation of a new 2D text texture would look like this

```c
tt_color_rgba_u8 color={0,255,0,255};
tt_2d_texture *text_tex=tt_2d_texture_make_text(font, "test text message", color);
```
### Fonts

Fonts are used for rendering text into textures for sprites. Currently fonts and text are only used in 2D.

Fonts can also be handled like other resources in T3Vtech-3. They have to be loaded to be used and once they are not necessary they need to be free'd manually.

```c
//loading a font into memory
tt_font* tt_font_open(
	const char* filename,
	const int size_pt);

//deleting a font from memory
void tt_font_delete(tt_font **font);
```

## Handling of Input

### Mouse

The mouse can be used in two different modes. One is the absolute mode where the user of the engine can get the absolution mouse cursor coordinates. This can be useful for menus or RTS games. The other mode is the relative mode where the user gets relative mouse coordinates to the last frame. This is especially useful for FPS games.

The relative mode can be toggled by calling 

```c
void tt_input_mouse_set_relative_mode(const bool toggle);
```

True will activate it and false will deactivate it. By default the engine is in absolute mode.

#### Relative Mouse Coordinates

When the relative mode is set then it is possible to get the relative mouse coordinates to the last frame. By calling

```c
void tt_input_mouse_relative_motion(
	int *x_relative,
	int *y_relative);
```

#### Absolute Mouse Coordinates

It is also possible to get the absolute mouse location inside the window of the game. It is strongly recommended to not use the relative mode when getting the absolute mouse location. It is still possible to use it but the OS cursor may appear randomly.

```c
void tt_input_mouse_location(int *x, int *y);
```

#### Mouse Buttons

There are two methods of getting information about mouse button presses. The two methods are presses which are registered only once and checks if a button is pushed down continuously. 

```c
bool tt_input_mouse_button_press(const unsigned char button); //single mouse click
bool tt_input_mouse_button_down(const unsigned char button); //continuously pushing down a mouse button
```

The key map for mouse buttons is a follow
```c
#define TT_MOUSE_LEFT 0
#define TT_MOUSE_MIDDLE 1
#define TT_MOUSE_RIGHT 2
#define TT_MOUSE_X1 3
#define TT_MOUSE_X2 4
```

### Keyboard

The keyboard is a very important method for game input. It is possible to check if a certain key is currently pressed in this this very frame (a key press is only registered once) or pushed down for a longer period of time.

```c
bool tt_input_keyboard_key_down(const unsigned char key); //longer period
```

tt_input_keyboard_key_down() returns true if the desired key is currently pushed in the current frame. 

The key value are defines like TT_KEY_ESC for the escape key.

The most important keys are
```c
//number keys
#define TT_KEY_0 SDL_SCANCODE_0
#define TT_KEY_1 SDL_SCANCODE_1
#define TT_KEY_2 SDL_SCANCODE_2
#define TT_KEY_3 SDL_SCANCODE_3
#define TT_KEY_4 SDL_SCANCODE_4
#define TT_KEY_5 SDL_SCANCODE_5
#define TT_KEY_6 SDL_SCANCODE_6
#define TT_KEY_7 SDL_SCANCODE_7
#define TT_KEY_8 SDL_SCANCODE_8
#define TT_KEY_9 SDL_SCANCODE_9

//letters
#define TT_KEY_A SDL_SCANCODE_A
#define TT_KEY_B SDL_SCANCODE_B
#define TT_KEY_C SDL_SCANCODE_C
#define TT_KEY_D SDL_SCANCODE_D
#define TT_KEY_E SDL_SCANCODE_E
#define TT_KEY_F SDL_SCANCODE_F
#define TT_KEY_G SDL_SCANCODE_G
#define TT_KEY_H SDL_SCANCODE_H
#define TT_KEY_I SDL_SCANCODE_I
#define TT_KEY_J SDL_SCANCODE_J
#define TT_KEY_K SDL_SCANCODE_K
#define TT_KEY_L SDL_SCANCODE_L
#define TT_KEY_M SDL_SCANCODE_M
#define TT_KEY_N SDL_SCANCODE_N
#define TT_KEY_O SDL_SCANCODE_O
#define TT_KEY_P SDL_SCANCODE_P
#define TT_KEY_Q SDL_SCANCODE_Q
#define TT_KEY_R SDL_SCANCODE_R
#define TT_KEY_S SDL_SCANCODE_S
#define TT_KEY_T SDL_SCANCODE_T
#define TT_KEY_U SDL_SCANCODE_U
#define TT_KEY_V SDL_SCANCODE_V
#define TT_KEY_W SDL_SCANCODE_W
#define TT_KEY_X SDL_SCANCODE_X
#define TT_KEY_Y SDL_SCANCODE_Y
#define TT_KEY_Z SDL_SCANCODE_Z

//additional standard keys
#define TT_KEY_ESC SDL_SCANCODE_ESCAPE
#define TT_KEY_LSHIFT SDL_SCANCODE_LSHIFT //left shift key
#define TT_KEY_RSHIFT SDL_SCANCODE_RSHIFT //right shift key
#define TT_KEY_LCTRL SDL_SCANCODE_LCTRL //left ctrl key
#define TT_KEY_RCTRL SDL_SCANCODE_RCTRL //right ctrl key
#define TT_KEY_SPACE SDL_SCANCODE_SPACE
#define TT_KEY_ENTER SDL_SCANCODE_RETURN //big enter key / return key
```

It is also possible to use the SDL scancodes, as apparent in the text above. Although it is recommend to use the T3Vtech-3 defines, since they are shorter.

Like mentioned above it can be registered if there is a key press, which is only registered for a single frame.

```c
bool tt_input_keyboard_key_press(const unsigned char key);
```

### Gamepads/Controllers

A lot of different controllers can be used thanks to SDL2. There is also no limit on how many controllers you can use with the engine. The controllers will be automatically registered by the engine when they are plugged in.

It is just necessary to know the number of the controller. This means player 1 has controller 1 and player 2 has controller 2 and so on.
If controller 1 is plugged out then controller 2 will become controller 1. The highest controller number is always the number of controllers plugged in.

#### Getting Button Presses

There are two different modes for button input. One is checking for a single button press. While the other one checks if a button is still pushed down. The first button press mode will just register that hit once.

The two functions will return true if the desired button is pressed/pushed down and false if not.

```c
bool tt_input_controller_button_press(const int ctl_number, const unsigned char button);
bool tt_input_controller_button_down(const int ctl_number, const unsigned char button);
```

The button keys are

```c
#define TT_CTL_A SDL_CONTROLLER_BUTTON_A
#define TT_CTL_B SDL_CONTROLLER_BUTTON_B
#define TT_CTL_X SDL_CONTROLLER_BUTTON_X
#define TT_CTL_Y SDL_CONTROLLER_BUTTON_Y
#define TT_CTL_BACK SDL_CONTROLLER_BUTTON_BACK
#define TT_CTL_GUIDE SDL_CONTROLLER_BUTTON_GUIDE
#define TT_CTL_START SDL_CONTROLLER_BUTTON_START
#define TT_CTL_LSTICK SDL_CONTROLLER_BUTTON_LEFTSTICK
#define TT_CTL_RSTICK SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define TT_CTL_LSHOULDER SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define TT_CTL_RSHOULDER SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define TT_CTL_UP SDL_CONTROLLER_BUTTON_DPAD_UP
#define TT_CTL_DOWN SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define TT_CTL_LEFT SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define TT_CTL_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
```

They are oriented towards an XBox controller. So they might vary if you use a controller with a different set of buttons.

#### Getting the Axes States

Many controllers don't just have buttons but axes as well. It is possible to get the current state of the controller's axes by calling

```c
void tt_input_controller_axis_state(
	const int ctl_number, 
	float *l_stick_x_out,
	float *l_stick_y_out,
	float *r_stick_x_out,
	float *r_stick_y_out);
```

The values for each stick's axes are between -1.0f and 1.0f with 0.0f being the mid.

## Time

T3Vtech-3 provides the possibility to get the system time with a nanosecond resolution. Although it is important to note that the actual time resolution may be smaller because of the system's implementation.

tt_time_current_ns() will always give the current time stamp to the user.

```c
long tt_time_current_ns();
```

There are also two functions for the current frame time because many functions in a game depend on how much time has passed since the last frame. Therefore these two function will always return the time that it took for the last frame to be completed.

```c
long tt_time_current_frame_ns(); //returns ns resolution
float tt_time_current_frame_s(); //returns a float with the fraction of a second
```

## Audio

T3Vtech-3 supports audio output and can currently read WAV files for songs and sound effects.

### Basic Usage

The typical usage of audio in T3Vtech-3 is the creation of a sound source from which a sound is played back. Then a sound is loaded from a file that is being buffered for a source or is loaded into the source so to speak. After the buffering the source can be played.

The creation of a source is done by calling 
```c
tt_3d_audio_source* tt_audio_3d_source_new();
```

A sound can be loaded from a file by using
```c
tt_sound* tt_audio_sound_from_file(const char *path);
```

The buffering is done with
```c
void tt_audio_buffer_sound_for_3d_source(
	tt_sound *sound,
	tt_3d_audio_source *source);
```

and the playing of a source by
```c
void tt_audio_play_3d_source(tt_3d_audio_source *source);
```

A full example would be
```c
tt_3d_audio_source *source = tt_audio_3d_source_new();
if(source)
{
	printf("Audio source successfully created\n");
}

tt_sound *sound = tt_audio_sound_from_file("assets/audio/test-moo.wav");
if(sound)
{
	printf("Audio file could be successfully loaded\n");
}

tt_audio_buffer_sound_for_3d_source(sound, source);
tt_audio_play_3d_source(source);
```

### Changing Gain

The gain for one single sound can be changed by with
```c
void tt_audio_set_sound_gain(tt_sound *sound, const float gain);
```

By default the gain is a float between 0.0f and 1000.f.

It is also possible to set a global gain which can be used to change the global volume. This is done by calling
```c
void tt_audio_set_global_gain(float volume);
```

### Loops

A sound can be set to looping mode. If this is done then it plays indefinitely.

The looping mode can be set by calling
```c
void tt_audio_loop_3d_source(tt_3d_audio_source *source, const bool loop_toggle);
```
If the loop_toggle is true then the sound will be looped when it's played back from a source.

## Logging

T3Vtech-3 has a simple logging system that can be used to store information in a logging file during runtime. The default logging file will be T3Vtech-3.log in the directory where the executable is located.

There are three different levels for logging messages. They are

```c
TT_INFO
TT_WARN
TT_ERROR
```
For now they will simply be a prefix to the logged message.

Messages can be logged by calling

```c
void tt_log(enum tt_log_type type, const char *format, ...);
```

An example would be

```c
tt_log(TT_ERROR, "file %s couldn't be found", file_path);
```
