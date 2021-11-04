#include <iostream>
#include <thread>
#include <chrono>
#include "world.h"
#include <cstdlib>

World::World(){
  map_ = {
    {'1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1'},    // default provided map value
  };
}

World::World(vector<vector<char> > map) {
  map_ = map;
}

void World::run() {
  // run the display in a loop with a "global tick"
  while (!stop_sim) {

    display();
    std::this_thread::sleep_for(std::chrono::milliseconds(display_time));

  }
}

void World::stopSimulation(){ // runs on a separate thread to check for character input, if it finds ESC, then sets a flag which breaks all loops
  char ch;
  while(!stop_sim){ // run another loop which listens in for user input
  cin.get(ch);
  if(ch == 'q' || ch == 'Q'){
    stop_sim = true;
  }
}
}

void World::zeroOutCurrentPosition(Robot&robot){
  int r,c;
  robot.getPosition(r,c); // get current (past) position of robot
  map_[r][c] = '0'; //  set it to unobstructed or free the position that the robot was previously in
}

bool World::removeRobot(int ID){
  // remove a robot
  zeroOutCurrentPosition(robots[ID]);
  if(robots.erase(ID) == 1){    // erase element of hashmap
    cout << "\n Successfully removed robot with ID: " << ID << "\n";
    return true;
  }
  cout <<"\n Remove failed for robot with ID: " << ID << "\n";
  return false;
}

bool World::addRobot(int row, int col, int delay=100){
  // try and add a robot
  if(map_[row][col]!='0'){    // in case there's something already there when trying to add robot
    cout << "\n Cannot add robot at location (" << row << "," << col  << ") please select another one!\n";
    return false;   // return false, value can be used later on if needed be or in case this is extended
  }
  // int delay = rand()%1000 + 20;
  Robot robot(row,col,delay); // robot object initalized
  robot.setRobotID(robot_count);  // ID set, is equal to index used to access in vector
  robot.setLabel('A' + (robot_count));  // sets tha label of the robot, increments the number of robots
  robots[robot_count++] = robot;    // add to collection of robots
  map_[row][col] = robot.getLabel();    // Mark the robot's position on the map
  // robot.printRobotState();
  cout << "\n Successfully added robot to location (" << row << "," << col  << ")!\n";
  return true;
}


bool World::updateRobotPosition(Robot&robot,int row,int col){
  // attempts updates position of robot
  lock_guard<mutex> map_guarder(map_mutex); // lock guard to automatically lock access within this scope, releases access to another thread when destroyed
  if(map_[row][col] == '0'){    // if map value to move to is open or not obstructed then move to that position
    zeroOutCurrentPosition(robot);
    robot.updatePosition(row,col);  // update robot's new position
    map_[row][col] = robot.getLabel();  // mark it again on map, on its new position
    return true;  // can move in direction
  }
  else{
    robot.setRandomDirection(); // if row,col is obstructed then set a new random direction to move to
    return false; //cannot move on this "tick", if new direction unobstructed, will move on next "tick"
  }
}

bool World::moveRobot(Robot &robot){
  // move the robot, helper function
  char ndirection = robot.getDirection();
  int row,col;
  robot.getPosition(row,col);
  if(ndirection == 'r'){  // if direction is right, then future position is one step ahead in columns
    if(!updateRobotPosition(robot,row,col+1)){
      return false; // if update not possible, return false
    }
  }
  else if(ndirection == 'l'){  // if direction is left, then future position is one step behind in columns
    if(!updateRobotPosition(robot,row,col-1)){
      return false; // if update not possible, return false
    }
  }
  else if(ndirection == 'u'){ // if direction is up, then future position is one step behind in rows
    if(!updateRobotPosition(robot,row-1,col)){
      return false; // if update not possible, return false
    }
  }
  else{
    if(!updateRobotPosition(robot,row+1,col)){  // if direction is down, then future position is one step ahead in rows
      return false; // if update not possible, return false
    }
  }

  return true;  // update possible, return true

}

void World::roboRunner(Robot &robot){
  // overall runner for the robots, move them!
  while(!stop_sim)
  {
    bool moved = moveRobot(robot);  // move robot
    std::this_thread::sleep_for(std::chrono::milliseconds(robot.getMoveTime()));    // robot speed or rate of "tick" decided by delay in robot
  }

}

void World::runWorld(){
  int i = 0;

  std::vector<thread> threads;    // vector of threads

  for(auto& robo_it: robots){

      threads.emplace_back(&World::roboRunner,this,ref(robo_it.second));   // push all robot objects to be processed by different threads on robotunner with separate "ticks"
  }
  threads.emplace_back(&World::run, this);  // global "tick" with much much faster refresh rate, @ one frame per 5 milliseconds by default
  threads.emplace_back(&World::stopSimulation, this); // to stop the simulation on a button press, a separate thread for listening in on keypresses

  for(i = 0; i < threads.size(); i++){
    threads[i].join();
  } // wait for them to finish


}

void World::display() {
  // "Clear" screen
  lock_guard<mutex> map_guarder(map_mutex);   // protect the map from wrongful multiple simeltaneous intrusion!
  if(debug_flag){
    for(auto& robo_it: robots){
    robo_it.second.printRobotState();  // print state for confirming that state of robots valid
  }
  std::cout << std::endl;}
  else
  { for (int i = 0; i < 20; i++){
    std::cout << std::endl;
  }
  }


  for (int i = 0; i < map_.size(); i++) {
    for (int j = 0; j < map_[i].size(); j++) {
      std::cout << map_[i][j];    // print map
    }
    std::cout << std::endl;
  }
}
