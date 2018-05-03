# mammut_prototype2
Second prototype of a local multiplayer boardgame... thing.

### to build
`mkdir -p ./build && clang++ -std=c++14 -Wall -Wextra -Wpedantic -fno-exceptions -fno-rtti -O0 -g -lasan -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf ./*.cpp ./GUI/*.cpp ./Video/*.cpp -o ./build/mammut`

### to run
`./build/mammut`

### requirements
* LLVM Clang
* GLEW
* SDL2
* SDL2-image
* SDL2-ttf

