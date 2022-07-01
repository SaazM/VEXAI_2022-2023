#ifndef _GPS
#define _GPS
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include "Serial/json.hpp"
#include "main.h"
#include <atomic>
using namespace pros;


class Data{
	public:
    	static pros::GPS gps;
		static void GPS_update();
		std::atomic<double> gps_x;
		std::atomic<double> gps_y;
		std::atomic<double> gps_heading;
		std::atomic<double> gps_heading_for_trig;
};
#endif
