//包含必要的头文件
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <text2_tutorials/text2_Config.h>


void callback(text2_tutorials::text2_Config &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %d %f %s %s %d", 
            config.int_param, config.double_param, 
            config.str_param.c_str(), 
            config.bool_param?"True":"False", 
            config.size);
}
//还需要定义回调函数，并将回调函数和服务端绑定。当客户端请求修改参数时，服务端即可跳转到回调函数进行处理。

int main(int argc, char **argv) {
/*先来看main函数的内容。首先初始化ROS节点，然后创建了一个参数动态配置的服务端实例，
参数配置的类型与配置文件中描述的类型相同。该服务端实例会监听客户端的参数配置请求。*/
 
  ros::init(argc, argv, "example4");

  dynamic_reconfigure::Server<text2_tutorials::text2_Config> server;
  dynamic_reconfigure::Server<text2_tutorials::text2_Config>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
