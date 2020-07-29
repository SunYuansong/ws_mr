/*
 * navfn_service_test.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: thobotics
 */

#include "ros/ros.h"
#include <mpepc_global_planner/GetNavCost.h>
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nav_test_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<mpepc_global_planner::GetNavCost>("/move_base/NavfnROSExt/nav_cost");
  mpepc_global_planner::GetNavCost srv;

  //srv.request.world_point =
  if (client.call(srv))
  {
    ROS_INFO("Resp: %f", (double)srv.response.cost);
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }

  return 0;
}


