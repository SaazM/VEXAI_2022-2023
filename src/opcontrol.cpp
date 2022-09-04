#include "main.h"
#include "Robot.h"
#include "15inch.h"

using namespace pros;

void opcontrol(){
  //autonomous coding starts in this file ALWAYS
  //Robot::win_game();
  Robot::start_task("DRIVE", Robot::drive);
}