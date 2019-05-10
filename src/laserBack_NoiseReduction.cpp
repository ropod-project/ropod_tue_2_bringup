#include <ros/ros.h>
//#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>

#define N_SCANS_FOR_AVERAGE     3

sensor_msgs::LaserScan scan;
ros::Publisher averagedScan_pub;

std::vector< sensor_msgs::LaserScan > latestScans(N_SCANS_FOR_AVERAGE);

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    scan = *msg;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "laserBack_NoiseReduction");
  ros::NodeHandle n;

   ros::Subscriber sub_laser = n.subscribe<sensor_msgs::LaserScan>("/ropod/laserBack/scan", 10, laserCallback);  
   averagedScan_pub = n.advertise<sensor_msgs::LaserScan>("/ropod/laserBack_avg/scan", 1);
   
   unsigned int latestScansPos = 0;
   int latestSeqId = 0;
   ros::Rate r(40);
   
  while(n.ok()){
  
    if(scan.header.seq != latestSeqId)
    {
          latestSeqId = scan.header.seq; 
          
          latestScans[latestScansPos] = scan;
          latestScansPos++;
          latestScansPos = latestScansPos % N_SCANS_FOR_AVERAGE;
          
          sensor_msgs::LaserScan avgScan = scan;
          
          for(unsigned int iScan = 0; iScan < scan.ranges.size(); iScan++)
          {
                  float distanceSum = 0.0;
                  float intensitySum = 0.0;
                  
                  for(unsigned int iMultiScans = 0; iMultiScans < N_SCANS_FOR_AVERAGE; iMultiScans++)
                  {
                          distanceSum+= latestScans[iMultiScans].ranges[iScan];
                          intensitySum+= latestScans[iMultiScans].intensities[iScan];
                  }
                  
                  avgScan.ranges[iScan] = distanceSum / N_SCANS_FOR_AVERAGE;
                  avgScan.intensities[iScan] = intensitySum / N_SCANS_FOR_AVERAGE;
          }
          
          averagedScan_pub.publish( avgScan );
    }
        
    ros::spinOnce();           
    r.sleep();
  }
}
