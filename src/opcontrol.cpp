#include "main.h"
#include "robot.h"
using namespace pros;

void opcontrol(){
  //autonomous coding starts in this file ALWAYS
  //Robot::win_game();
  Robot::start_task("DRIVE", Robot::drive);
}