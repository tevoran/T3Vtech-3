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

At the end of the game you should quit the engine. Although tt_quit() will be also called if there happens something unexpected.

```c
void tt_quit();
```