#include <ros/ros.h>
#include <grid_map/grid_map.hpp>
#include <grid_map_msgs/GridMap.h>
#include <cmath>

using namespace std;
using namespace grid_map;

int main(int argc, char** argv)
{
  // Initialize node and publisher.
  ros::init(argc, argv, "grid_map_simple_demo");
  ros::NodeHandle nh("~");
  ros::Publisher publisher = nh.advertise<grid_map_msgs::GridMap>("grid_map", 1, true);

  // Create grid map.
  GridMap map({"elevation"});
  map.setFrameId("map");
  map.setGeometry(Length(1.2, 2.0), 0.03);
  ROS_INFO("Created map with size %f x %f m (%i x %i cells).",
    map.getLength().x(), map.getLength().y(),
    map.getSize()(0), map.getSize()(1));

  // Work with grid map in a loop.
  ros::Rate rate(30.0);
  while (nh.ok()) {

    // Add data to grid map.
    for (GridMapIterator it(map); !it.isPassedEnd(); ++it) {
      Position position;
      map.getPosition(*it, position);
      double t = ros::Time::now().toSec();
      map.at("elevation", *it) = -0.04 + 0.2 * sin(3.0 * t + 5.0 * position.y()) * position.x();
    }

    // Publish grid map.
    map.setTimestamp(ros::Time::now().toNSec());
    grid_map_msgs::GridMap message;
    GridMapRosConverter::toMessage(map, message);
    publisher.publish(message);
    ROS_INFO_THROTTLE(1.0, "Grid map (timestamp %f) published.", message.info.header.stamp.toSec());

    // Wait for next cycle.
    rate.sleep();
  }

  return 0;
}
