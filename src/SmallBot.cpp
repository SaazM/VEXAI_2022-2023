#include "main.h"
#include "SmallBot.h"
#include "system/json.hpp"
#include "Serial/Serial.h"
#include <map>
#include <cmath>
#include <atomic>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <deque>
using namespace pros;
using namespace std;

Controller SmallBot::master(E_CONTROLLER_MASTER);

PD SmallBot::power_PD(/*add values*/);
PD SmallBot::strafe_PD(/*add values*/);
PD SmallBot::turn_PD(/*add values*/);

Motor SmallBot::FL(1, true);
Motor SmallBot::ML(3, true);
Motor SmallBot::BL(5, true);
Motor SmallBot::FR(4);
Motor SmallBot::MR(2);
Motor SmallBot::BR(6);
Motor SmallBot::H(7);
double SmallBot::cur_x_gps;
double SmallBot::cur_y_gps;
double SmallBot::cur_heading_gps;
Gps SmallBot::gps(16);
Imu SmallBot::IMU(15);
Rotation SmallBot::BE(20);

std::map<std::string, std::unique_ptr<pros::Task>> SmallBot::tasks;

void SmallBot::drive(void *ptr) {
    
}

void SmallBot::gps_initialize(void *ptr) {

}

void SmallBot::send_data() {

}

void SmallBot::receive_data(nlohmann::json msg) {

}

void SmallBot::start_task(std::string name, void (*func)(void *)) {

}

bool SmallBot::task_exists(std::string name) {

}

void SmallBot::kill_task(std::string name) {

}

void SmallBot::move_to(void *ptr) {

}