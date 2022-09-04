#ifndef _SmallBot
#define _SmallBot
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <atomic>
using namespace pros;

class SmallBot {
    public:
        static Controller controller;
        static Controller master;
        static Motor FL;
        static Motor ML;
        static Motor BL;
        static Motor FR;
        static Motor MR;
        static Motor BR;
        static Motor H;
        static double cur_x_gps;
        static double cur_y_gps;
        static double cur_heading_gps;
        static Gps gps;
        static Imu IMU;
        static Rotation BE;
        static std::map<std::string, std::unique_ptr<pros::Task>> tasks;
        static void drive(void *ptr);
        static void gps_initialize(void *ptr);
        static void send_data();
        static void receive_data(nlohmann::json msg);
        static void start_task(std::string name, void (*func)(void *));
        static void task_exists(std::string name);
        static void kill_task(std::string name);
        static void move_to(void *ptr);
};
#endif
