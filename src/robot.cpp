#include "robot.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Robot::Robot() {
}

void Robot::setRobotID(int ID){
  // set robot ID
  id = ID;
}

Robot::Robot(int row,int col, int timemove, char ndirection){
  // intialize a robot
  r = row;
  c = col;
  direction = ndirection;
  per_move_time = timemove;
}

void Robot::setLabel(char lab){
  // set the label for a robot
  label = lab;
}
char Robot::getLabel(){
  // get label
  return label;
}

void Robot::printRobotState(){
  // print information about a robot
  // for debugging purposes
  cout << "\n Robot with ID: " << id << " has label " << label << " with delay: " << per_move_time << "ms \n";
  cout << "Current Position: (" << r << "," << c << ") and direction: " << direction << "\n";
}

char Robot::pickRandomDirection(){
  // gets a random direction based on 'l','r','u','d' or left, right, up or down based on selection of random index b/w 0 and 3
  char directions[4] = {'l','r','u','d'};
  int i = rand()%4;
  return directions[i];
}

int Robot::getMoveTime(){
  // get the delay time for a robot
  return per_move_time;
}

void Robot::setRandomDirection(){
  // sets the direction of a robot to a selected random direction in case there's an obstruction
  updateDirection(pickRandomDirection());
}

void Robot::updateDirection(char newdirection){
  // update the robot to a new direction; in case of obstructions
  direction = newdirection;
}

void Robot::updatePosition(int newr,int newc){
  // update the position of the robot
  r = newr;
  c = newc;
}

char Robot::getDirection(){
  // get the direction
  return direction;
}

void Robot::getPosition(int&getr,int&getc){
  // get the position
  getr = r;
  getc = c;
}
