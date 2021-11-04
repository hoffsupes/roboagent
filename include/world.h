#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "robot.h"
#include <mutex>
#include <unordered_map>
#include <atomic>


using namespace std;  // using standard namespace, single inclusion usable everywhere
// Forward declaration
class Robot;

// Define and implement the following class. Feel free to change the given
// interfaces and data structures to better match your design
class World {
private:
  vector<vector<char> > map_;    // world map
  int robot_count=0;  // number of robots in simulation
  int display_time = 5; // refresh rate or delay in "global tick"
  mutex map_mutex;  // mutex so that shared map_ is not accessed wrongfully by two threads at once
  unordered_map<int,Robot> robots;   //  vector of robot objects, to collect and keep track of robots
  atomic_bool stop_sim{false};  // stops the simulation using a common flag shared amongst all threads
 public:
  bool debug_flag = false; // debugging flag can be set by user to display extra output
  World();  // default constructor
  World(vector<vector<char> >); // parameterized constructor
  void run();   //  to display
  void display();   //  intermediate function to display
  void runWorld();    //  to run the actual simulation
  void zeroOutCurrentPosition(Robot&robot);   // Erasing the current position of robot in map
  bool addRobot(int, int,int);    //  add a robot to the simulation
  bool removeRobot(int);  // remove robot
  bool updateRobotPosition(Robot&robot,int row,int col);    //  update robot position to new one
  bool moveRobot(Robot &robot);   //  move one robot
  void roboRunner(Robot &robot);    //  start moving robots!
  void stopSimulation();
};

#endif
