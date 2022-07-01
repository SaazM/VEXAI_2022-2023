#include "Fundamental/GPS.h"
#include "main.h"



int gps_portnum = 0;
pros::GPS gps(gps_portnum);
std::atomic<double> gps_x;
std::atomic<double> gps_y;
std::atomic<double> gps_heading;
std::atomic<double> gps_heading_for_trig;
void GPS_update()//quick way to update all GPS variables constantly
{
    while(true)
    {
        gps_x = gps.get_status().x;
        gps_y = gps.get_status().y;
        gps_heading = gps.get_heading();
        double temp = 90-gps_heading;
        gps_heading_for_trig = temp<0 ? temp+=360 : temp;
        delay(5);
    }
    
}