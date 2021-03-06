#include "world.h"
#include "robot.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  // You should customize this data structure and the World constructor to
  // match your chosen data structure.
  vector<vector<char> > map = {
    {'1', '1', '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1', '1','1','1','1', '1', '1', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','1','1','1','0','0','0','0', '1','1','1','1', '1', '0', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '0', '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0', '0','0','0','0', '0', '0', '1'},
    {'1', '1', '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1', '1','1','1','1', '1', '1', '1'},    // default provided map value
  };
  World w(map);
  w.debug_flag = true;     // debugging set to true to see statistics

  w.addRobot(1, 1,10);  // add robot which moves fast with artificial delay of 10ms per move
  w.addRobot(0, 0,20);  // try to add robot at obstruction
  w.addRobot(1, 2,1000);  // add robot which moves slower, almost one move per second
  w.addRobot(5, 5,2000);  // add robot which moves slowest, about one move per two seconds
  w.addRobot(11, 1,5000);  // add robot which moves slowest, about one move per two seconds
  w.addRobot(5, 4,2000);  // add robot which moves slowest, about one move per two seconds
  w.removeRobot(4); // try and remove robot with ID 4


  w.runWorld();   // get to the bots!
}
