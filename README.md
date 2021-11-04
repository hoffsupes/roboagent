# roboagents

Run a tiny simulation about robots running around a user defined map

### Install:

1. Install gcc, cmake and other required tools: ` sudo apt-get install cmake gcc g++ build-essential `
2. Clone this repo: `git clone https://github.com/hoffsupes/roboagent.git`

### Use:

1. Traverse to the root of the project folder and run
```
mkdir build && cd build && cmake .. && make
```
2. Open a terminal in the build folder (where you should be after running past command) and run `./roboagents`
3. Set the `debug_flag` to `true` in `main.cpp` to see state of robots in action
4. Press `Q` or `q`, immediately followed by `Enter` or the `Return` key. You can also hold down the `q` key and then press `Enter` to exit (i.e. `q + Enter` keys in that very order).
5. Alternatively, press `Ctrl-C` or `Ctrl-Z` to end the simulation

### Important methods

`addRobot`: Adds a robot

`removeRobot`: Removes a robot

`runWorld`: Runs the world
