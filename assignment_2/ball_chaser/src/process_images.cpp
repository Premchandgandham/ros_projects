#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>


int k = 0;
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
  int bpp=img.step/img.width;
  int ball_x,ball_y;  
  float lin_x,ang_z;
  
  ROS_INFO("Height(rows) = %d",img.height);
  ROS_INFO("wodth(colums) = %d",img.width);
  ROS_INFO("Step value = %d",img.step);
  ROS_INFO("actual matrix size %d",img.height*img.step);
  
 found_ball=false;

   for (int y = 0; y < img.height; y++) {
    for(int x=0; x < img.width; x++) {
      if (img.data[y*img.step+x*bpp] == white_pixel) {
        found_ball=true;
        ball_x=x;ball_y=y;
        ROS_INFO("width at which ball places %d",x);
        ROS_INFO("height at which ball places %d",y);
        break;
      }
    }
  }
  
// Height is no of rows
// width is  no of colums

  
if(k < 5){
  
if(found_ball) {
	
	ROS_INFO("Turn value = %d",k);

    
     
    	ROS_INFO_STREAM("ball_x: " + std::to_string(ball_x));
    		if(ball_x < 400)
   			 {
			      ROS_INFO_STREAM("ball in the left 1/3");
			      lin_x=0.0;
			      ang_z=0.005*(400-ball_x);
			      k++;
			      ROS_INFO("turn value = %d",k);
			      
    			} 

      		else if(ball_x >= 400)
        	 
			{
			  ROS_INFO_STREAM("ball in the right section");
			  lin_x=0.0;
			  ang_z=-0.005*(ball_x-400);
			  k++;
			  ROS_INFO("turn value = %d",k);
			  
			}
		
       

    drive_robot(lin_x, ang_z);
    
    
  }
  
  
 else
 	{
  		drive_robot(0.0,0.0);
  		ROS_INFO("No ball found");
  		k = 0;
  		
  	}
  
}




       else
       	{
       
        		lin_x = 0.4;
        		ang_z = 0.0;
        		
        		if(ball_x < 400)
        			ang_z = 0.02;
        		else
        			ang_z =-0.02;
        			
        		drive_robot(lin_x, ang_z);
        		if(!(ball_x >0 && ball_x<799)){
        			ROS_INFO("NO BALL FOUND");	
        			k=0;
        		}

       	}
       	
    }
    

void scan_call_back(const sensor_msgs::LaserScan scan){

/*	ROS_INFO("minimum_range = %f", scan.range_min);
	ROS_INFO("maximum_range = %f", scan.range_max);
	ROS_INFO("scan time = %f", scan.scan_time); 
*/
	int n = std::distance(std::begin(scan.ranges), std::end(scan.ranges));
	ROS_INFO("length of the array of ranges = %d",n);

	for(int i=0;i<n;i++){

	if(scan.ranges[i] < 0.2){
	
		ROS_INFO("Obstacle is a head ");
		drive_robot(0.0,0.0); 
	}
   }

 } 
  
int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    
    ros::NodeHandle n;

    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 2, process_image_callback);
    
    ros::Subscriber sub2 = n.subscribe("hokuyo/scan",2,scan_call_back);

    ros::spin();

    return 0;
}
