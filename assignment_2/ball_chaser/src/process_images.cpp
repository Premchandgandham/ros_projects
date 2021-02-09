#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z)
{
    
    ROS_INFO_STREAM("Requesting new linear x and angular z velocities");
    
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service safe_move");
}

void process_image_callback(const sensor_msgs::Image img)
{

  int white_pixel = 255;
  bool found_ball=false;
  int ball_x,ball_y;
  int bpp=img.step/img.width;
  float lin_x,ang_z;

  
  found_ball=false;
  for (int y = 0; y < img.height; y++) {
    for(int x=0; x < img.width; x++) {
      if (img.data[y*img.step+x*bpp] == white_pixel) {
        found_ball=true;
        ball_x=x;ball_y=y;
        break;
      }
    }
  }
  
  if(found_ball) {
    ROS_INFO_STREAM("ball_x: " + std::to_string(ball_x));
    if(ball_x < 266)
    {
      ROS_INFO_STREAM("ball in the left 1/3");
      lin_x=0.1;
      ang_z=0.01*(400-ball_x);
    } 
    else
      if(ball_x >= 266 && ball_x < 533)
      {
        ROS_INFO_STREAM("ball in the middle section");
        lin_x=0.5;
        if(ball_x<400)
          ang_z=0.01*(400-ball_x);
        else
          ang_z=-0.01*(ball_x-400);
        
      }
      else
        if(ball_x >= 533) 
        {
          ROS_INFO_STREAM("ball in the right section");
          lin_x=0.1;
          ang_z=-0.01*(ball_x-400);
        }
    drive_robot(lin_x, ang_z);
  } else drive_robot(0, -1.5);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    
    ros::NodeHandle n;

    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    ros::spin();

    return 0;
}
