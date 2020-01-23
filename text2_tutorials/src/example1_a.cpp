#include "ros/ros.h"           //包含了ros节点所必要的文件
#include "std_msgs/String.h"   //包含了所使用的消息类型
#include <sstream>             //包含要使用的文件类型

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example1_a"); //启动该节点并设置其名称,名称必须唯一
  ros::NodeHandle n;                   //设置节点进程的句柄 

  ros::Publisher pub = n.advertise<std_msgs::String>("message", 1000);
/*将节点实例化，设置成发布者,并将所发布的主题和类型（字符串string）的名称告知节点管理器。
第一个参数是消息的名称:message,第二个是缓冲区道大小。
如果主题发布数据速度较快,那么将缓冲区设置为1000个消息。*/
  ros::Rate loop_rate(10);//设置发送数据道频率为10Hz 
  
  while (ros::ok())//当收到Ctrl+C的按键消息或ROS停止当前节点运行时,ros::ok()库会执行停止节点运行道命令  
  {
//////创建一个消息变量,变量类型必须符合发送数据的要求  
    std_msgs::String msg;  //定义msg
    std::stringstream ss;  //
    ss << " I am the example1_a node ";
    msg.data = ss.str();
    //ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);//消息被发布 
    ros::spinOnce();//如果一个订阅者出现,ROS就会更新和读取所有主题  
    loop_rate.sleep();//按照10Hz的频率将程序挂起 
  }
  return 0;
}
