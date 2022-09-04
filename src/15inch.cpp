#include "main.h"
#include "15inch.h"
#include "system/json.hpp"
#include "serial/Serial.h"
#include <map>
#include <cmath>
#include <atomic>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <deque>
using namespace pros;
using namespace std;

Controller 15inch::master(E_CONTROLLER_MASTER);

PD 15inch::power_PD(/*add values*/);
PD 15inch::strafe_PD(/*add values*/);
PD 15inch::turn_PD(/*add values*/);

Motor 15inch::FL(1, true);
Motor 15inch::ML(3, true);
Motor 15inch::BL(5, true);
Motor 15inch::FR(4);
Motor 15inch::MR(2);
Motor 15inch::BR(6);
Motor 15inch::H(7);
double 15inch::cur_x_gps;
double 15inch::cur_y_gps;
double 15inch::cur_heading_gps;
Gps 15inch::gps(16);
Imu 15inch::IMU(15);
Rotation 15inch::BE(20);

std::map<std::string, std::unique_ptr<pros::Task>> 15inch::tasks;

void 15inch::drive(void *ptr) {
    
}

void 15inch::gps_initialize(void *ptr) {

}

void 15inch::send_data() {

}

void 15inch::receive_data(nlohmann::json msg) {

}

void 15inch::start_task(std::string name, void (*func)(void *)) {

}

bool 15inch::task_exists(std::string name) {

}

void 15inch::kill_task(std::string name) {

}

void 15inch::move_to(void *ptr) {

}