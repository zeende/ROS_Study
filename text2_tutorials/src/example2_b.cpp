#include "ros/ros.h"
#include "text2_tutorials/text2_srv1.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_3_ints_client");
  if (argc != 4)
  {
    /* code for True */
    ROS_INFO("usage: add_3_ints_client A B C ");
    return 1;
  }

  ros::NodeHandle n;
  //以add_3_ints为名称创建一个服务的客户端
  ros::ServiceClient client = n.serviceClient<text2_tutorials::text2_srv1>("add_3_ints");
  //下面创建srv文件的一个实例，并且加入需要发生的数据值
  text2_tutorials::text2_srv1 srv;
  srv.request.A = atoll(argv[1]);
  srv.request.B = atoll(argv[2]);
  srv.request.C = atoll(argv[3]);
  //调用服务并发生数据。如果调用成功，call()函数会返回true；如果没成功，call()函数会返回false
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
