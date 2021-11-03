#ifndef ROBOT_H_
#define ROBOT_H_

// #include "world.h"

// Forward declaration
class World;

// Define and implement the following class
class Robot {
private:
  int r=-1,c=-1;  // position of the robot
  char direction = 'r'; // the direction of the robot, default is right
  int id = -1;  // robot ID
  int per_move_time = 100;    // millisecond delay this robot takes or "tick" of the robot, default value 100
  char label = '*'; // label used by the robot
 public:
  Robot();  // default constuctor
  Robot(int row,int col,int movetime=100,char dirxn='r'); // parameterized constructor
  void updateDirection(char newdirection);    // Update the direction of the robot's heading
  void updatePosition(int newr,int newc);   //  update the position of the robot
  char getDirection();    //  get the current direction of the robot
  void getPosition(int&getr,int&getc);    //  get the current position of the class
  void setRobotID(int ID);    //  set the ID of the robot
  char pickRandomDirection();   //  pick a new random direction for the robot to head to
  int getMoveTime();    // get the current "tick" value or delay time for the robot
  void setRandomDirection();    //  set a new random direction using pickRandomDirection(), if current move is not allowed
  void setLabel(char);    //  set label for robot
  char getLabel();    //  get label for robot
  void printRobotState();   //  print the robot state, useful for diagnostics

};

#endif
