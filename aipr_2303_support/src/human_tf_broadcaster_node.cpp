/*
    tf2_human_broadcaster node ROS2

    Copyright 2023 Università degli studi della Campania "Luigi Vanvitelli"
    Author: Marco Costanzo <marco.costanzo@unicampania.it>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("human_tf_broadcaster");

  std::string base_link = node->declare_parameter("base_link", "meca_base_link");

  tf2_ros::TransformBroadcaster br(node);

  rclcpp::Rate loop_rate(10);
  rclcpp::Time t0 = node->now();
  rclcpp::Duration t = rclcpp::Duration::from_seconds(0.0);

  while (rclcpp::ok())
  {
    loop_rate.sleep();
    rclcpp::spin_some(node);

    t = node->now() - t0;

    geometry_msgs::msg::TransformStamped transformStamped;

    transformStamped.header.stamp = node->now();
    transformStamped.header.frame_id = base_link;

    transformStamped.child_frame_id = "human";

    transformStamped.transform.translation.x =
        0.5 * (0.8 + 0.25) + 0.5 * (0.8 - 0.25) * sin(2.0 * M_PI * 0.05 * t.seconds());
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.25;

    transformStamped.transform.rotation.x = 0.0;
    transformStamped.transform.rotation.y = 0.0;
    transformStamped.transform.rotation.z = 0.0;
    transformStamped.transform.rotation.w = 1.0;

    br.sendTransform(transformStamped);
  }

  return 0;
};