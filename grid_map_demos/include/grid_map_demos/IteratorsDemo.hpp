/*
 * IteratorsDemo.hpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, Autonomous Systems Lab
 *
 */

#pragma once

#include <grid_map/grid_map.hpp>

// ROS
#include <ros/ros.h>

namespace grid_map_demos {

/*!
 * Visualizes a grid map by publishing different topics that can be viewed in Rviz.
 */
class IteratorsDemo
{
 public:

  /*!
   * Constructor.
   * @param nodeHandle the ROS node handle.
   */
  IteratorsDemo(ros::NodeHandle& nodeHandle);

  /*!
   * Destructor.
   */
  virtual ~IteratorsDemo();

  /*!
   * Demos.
   */
  void demoGridMapIterator();
  void demoSubmapIterator();
  void demoCircleIterator();
  void demoLineIterator();
  void demoPolygonIterator();

  /*!
   * Publish the grid map to ROS.
   */
  void publish();

 private:

  //! ROS nodehandle.
  ros::NodeHandle& nodeHandle_;

  //! Grid map publisher.
  ros::Publisher gridMapPublisher_;

  //! Polygon publisher.
  ros::Publisher polygonPublisher_;

  //! Grid map data.
  grid_map::GridMap map_;
};

} /* namespace */
