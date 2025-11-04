# SFML Backend for DR4 Graphics Interface

A minimal SFML-based implementation of the DR4 graphics backend interface. This plugin provides window management, basic drawing capabilities, and event handling using SFML.

## Features

- Window creation and management
- Basic shape drawing (rectangles)
- Texture and image support  
- Event handling (keyboard, mouse, window)
- Plugin architecture compatible with DR4 standard

## Dependencies

- SFML 2.5+
- C++17 compiler
- CMake 3.16+

## Building

```bash
mkdir build && cd build
cmake ..
make
```

The plugin will be built as dr4_sfml_backend.so.
## Usage

Load the plugin in your DR4-compatible application:
```cpp
void* plugin = dlopen("dr4_sfml_backend.so", RTLD_LAZY);
auto create_func = (dr4::DR4Backend*(*)())dlsym(plugin, "CreateDR4Backend");
dr4::DR4Backend* backend = create_func();
```

# Interface Standard

This implementation follows the DR4 graphics interface standard defined in:
https://github.com/NeIIor/zemax-gui-interface