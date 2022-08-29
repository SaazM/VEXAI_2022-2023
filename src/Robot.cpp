#include "main.h"
#include "Robot.h"
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


/* --- NEW PORTS 8/25 --- */

Motor Robot::BRB(19, true);
Motor Robot::BRT(20);
Motor Robot::BLT(11, true);
Motor Robot::BLB(12);
Motor Robot::FLT(1, true);
Motor Robot::FLB(2);
Motor Robot::FRB(10, true);
Motor Robot::FRT(9);


void Robot::drive(void *ptr) {
    while (true) {
        int power = master.get_analog(ANALOG_LEFT_Y);
        int strafe = master.get_analog(ANALOG_LEFT_X);
        int turn = master.get_analog(ANALOG_RIGHT_X);
        
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
    //200 is the max speed
    double scalar = (true_max > 200) ? 200 / true_max : 1;

    FLT = powers[0] * scalar;
    FRT = powers[1] * scalar;
    BLT = powers[2] * scalar;
    BRT = powers[3] * scalar;
    FLB = powers[0] * scalar;
    FRB = powers[1] * scalar;
    BLB = powers[2] * scalar;
    BRB = powers[3] * scalar;
}

// void Robot::brake(std::string mode)
// {

//     if (mode.compare("coast") == 0)
//     {
//         FLT.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         FLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         FRT.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         FRB.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         BLT.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         BLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         BRT.set_brake_mode(E_MOTOR_BRAKE_COAST);
//         BRB.set_brake_mode(E_MOTOR_BRAKE_COAST);

//     }
//     else if (mode.compare("hold") == 0)
//     {
//         FLT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         FLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         FRT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         FRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         BLT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         BLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         BRT.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//         BRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);

//     }
//     else FLT = FLB= FRT = FRB= BLT = BLB = BRT = BRB= 0;
// }

void Robot::start_task(std::string name, void (*func)(void *)) {
    if (!task_exists(name)) {
        tasks.insert(std::pair<std::string, std::unique_ptr<pros::Task>>(name, std::move(std::make_unique<pros::Task>(func, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, ""))));
    }
}

bool Robot::task_exists(std::string name) {
    return tasks.find(name) != tasks.end();
}

void Robot::kill_task(std::string name) {
    if (task_exists(name)) {
        tasks.erase(name);
    }
}