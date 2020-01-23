#include "ros/ros.h"
#include "std_msgs/String.h"

//设置回调函数messageCallback,每次该节点收到一条消息时都会调用此函数。该函数可以处理数据。
void messageCallback(const std_msgs::String::ConstPtr& msg) 
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  //初始化节点并设置名称(名称唯一)
  ros::init(argc, argv, "example1_b");
//进程的处理程序，允许我们与环境交互
  ros::NodeHandle n;
//将节点实例化为订阅者，并将所发布的主题类型的名称告知节点管理器。名为message。处理消息的函数为messageCallback
  ros::Subscriber sub = n.subscribe("message", 1000, messageCallback);
//spin()函数负责处理节点开始读取主题和在消息到达时，回调函数messageCallback被调用的主循环。Ctrl+C组合建，节点退出消息循环，于是结束循环
  ros::spin();
  return 0;
}
