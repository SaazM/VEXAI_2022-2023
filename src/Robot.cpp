#include "main.h"
#include "Robot.h"
// #include "PD.cpp"
#include <map>
#include <cmath>
#include <atomic>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <deque>
using namespace pros;
using namespace std;


std::map<std::string, std::unique_ptr<pros::Task>> Robot::tasks;

Controller Robot::master(E_CONTROLLER_MASTER);
/* --- OLD PORTS --- */
// Motor Robot::FLT(2, true); //front left top
// Motor Robot::FLB(1); //front left bottom
// Motor Robot::FRT(9); //front right top
// Motor Robot::FRB(10, true); //front right bottom
// Motor Robot::BRT(20, true); //back right top
// Motor Robot::BRB(19); //back right bottom
// Motor Robot::BLT(11); //back left top
// Motor Robot::BLB(12, true); //back left bottom

// Motor Robot::angler(17);
// Motor Robot::conveyor(18);

/* --- NEW PORTS 8/25 --- */
Motor Robot::FLT(1, true); //front left top
Motor Robot::FLB(2); //front left bottom
Motor Robot::FRT(9); // front right top
Motor Robot::FRB(10, true); //front right bottom
Motor Robot::BRT(20, true); //back right top
Motor Robot::BRB(19); //back right bottom
Motor Robot::BLT(11); //back left top
Motor Robot::BLB(12, true); //back left bottom

ADIDigitalOut Robot::piston(2);
ADIAnalogIn Robot::potentiometer(1);


void Robot::drive(void *ptr) {
    while (true) {
        lcd::print(1,"Potentiometer %d", potentiometer.get_value());
        int power = master.get_analog(ANALOG_LEFT_Y);
        int strafe = master.get_analog(ANALOG_LEFT_X);
        int turn = master.get_analog(ANALOG_RIGHT_X);

        bool angler_forward = master.get_digital(DIGITAL_L1);
        bool angler_backward = master.get_digital(DIGITAL_L2);

        bool piston_open = master.get_digital(DIGITAL_A);
        bool piston_close = master.get_digital(DIGITAL_B);
 
        bool conveyor_forward = master.get_digital(DIGITAL_R1);
        bool conveyor_backward = master.get_digital(DIGITAL_R2);

        if (angler_forward){
            while(potentiometer.get_value()<3710){
                angler = 50;
            }   
            angler = 0;
        } 
        else if (angler_backward){
            while(potentiometer.get_value()>2330){
                angler = -50;
            }
            angler = 0;
        } 
        else angler = 0;

        if (piston_open) piston.set_value(true);
        else if (piston_close) piston.set_value(false);
        
        if (conveyor_forward) conveyor = 100;
        else if (conveyor_backward) conveyor = -100;
        else conveyor = 0;
        
        mecanum(power, strafe, turn);
        delay(5);
    }
}

void Robot::mecanum(int power, int strafe, int turn) {

 int powers[] {
     power + strafe + turn,
     power - strafe - turn,
     power - strafe + turn, 
     power + strafe - turn
 };

 int max = *max_element(powers, powers + 4);
 int min = abs(*min_element(powers, powers + 4));

 double true_max = double(std::max(max, min));
 double scalar = (true_max > 127) ? 127 / true_max : 1;
    
 FLT = 0*(power + strafe + turn) * scalar;
 FLB = 0*(power + strafe + turn) * scalar;

 FRT = (power - strafe - turn) * scalar;
 FRB = (power - strafe - turn) * scalar;
 BLT = (power - strafe + turn) * scalar;
 BLB = (power - strafe + turn) * scalar;
 BRT = (power + strafe - turn) * scalar;
 BRB = (power + strafe - turn) * scalar;
}

void Robot::brake(std::string mode)
{

    if (mode.compare("coast") == 0)
    {
        FLT.set_brake_mode(E_MOTOR_BRAKE_COAST);
        FLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
        FRT.set_brake_mode(E_MOTOR_BRAKE_COAST);
        FRB.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BLT.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BRT.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BRB.set_brake_mode(E_MOTOR_BRAKE_COAST);

    }
    else if (mode.compare("hold") == 0)
    {
        FLT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        FLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        FRT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        FRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BLT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BRT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    }
    else FLT = FLB= FRT = FRB= BLT = BLB = BRT = BRB= 0;
}


