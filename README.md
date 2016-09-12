
# SkyGL

## Dependencies

- GLFW3
- GLEW
- ASSIMP
- SOIL
- GLM
- Boost.Signals2

For `Ubuntu` users:

```sh
sudo apt-get install libglfw3-dev libglew-dev libassimp-dev libsoil-dev libglm-dev libboost-dev
```

For `ArchLinux` users:

```sh
sudo pacman -S glfw-x11 glew assimp soil glm boost
```

## Build

```sh
mkdir build && cd build
cmake ..
make
```

