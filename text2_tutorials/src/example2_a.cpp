#include "ros/ros.h"
#include "text2_tutorials/text2_srv1.h"//包含先前所创建的srv文件

//对3个变量求和，并将计算结果发生给其他节点，Request为上一部分的请求，而Response为下一部分的响应
//这个函数提供两个int值求和的服务，int值从request里面获取，而返回数据装入response内，这些数据类型都定义在srv文件内部，函数返回一个boolean值。
bool add(text2_tutorials::text2_srv1::Request  &req,
         text2_tutorials::text2_srv1::Response &res)
{
  res.sum = req.A + req.B + req.C;//加法
  ROS_INFO("request: A=%d, B=%d C=%d", (int)req.A, (int)req.B, (int)req.C);//在命令行窗口输出信息
  ROS_INFO("sending back response: [%d]", (int)res.sum);//在命令行窗口输出信息
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_3_ints_server");//初始化节点
  ros::NodeHandle n;

  //创建服务并在ROS中发布广播
  //创建名为service的服务并在ROS中发布广播，add_3_ints是，add是回调函数
  ros::ServiceServer service = n.advertiseService("add_3_ints", add);
  ROS_INFO("Ready to add 3 ints.");//在命令行窗口输出信息
  ros::spin();

  return 0;
}
