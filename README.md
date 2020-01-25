# ROS_Study
ros基础学习

完整内容见 http://note.youdao.com/noteshare?id=266a1b966fc3e7fbe9dd43ae6bc5bc70


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

〇、安装ros
安装方式一：ubuntu 16.04为例的安装，参照官网过程（建议）
http://wiki.ros.org/cn/kinetic/Instamp,plllation/Ubuntu

安装方式二：一键式脚本安装

#下载脚本
git clone https://github.com/maxen0604/ROS_Study.git
cd ROS_Study/
chmod +x autoInstallROS.sh
./ autoInstallROS.sh


安装方式三：镜像
参考博客 https://blog.csdn.net/zhangrelay/article/details/54632130



一、创建工作空间
1、首先创建工作空间
cd ~ #进入用户目录下
mkdir -p catkin_ws/src  #创建新文件夹 catkin_ws为工作空间名，可自定义
cd catkin_ws/src      #进入目录
catkin_init_workspace #创建工作空间


2、这时工作空间内没有功能包，只有CMakelist.txt，下一步开始编译工作空间
cd ~/catkin_ws
catkin_make    #编译  （对于一些低性能处理器使用catkin_make -j1 进行单线程编译）

这时出现了build 和 devel 两个文件夹。

3、为了完成配置需要加载 setup.bash 文件
方法一： 只对当前终端有效
source devel/setup.bash

方法二：在 .bashrc中添加一句话 使得终端开启时自动初始化
（.bashrc是主文件夹下的隐藏文件 ctrl+h可以显示，可以用gedit编辑，也可以如下在终端中添加）

source ~/catkin_ws/devel/setup.bash
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc


二、创建功能包和元功能包
1、使用catkin_create_pkg命令创建
在src目录下创建
catkin_create_pkg text2_tutorials std_msgs roscpp 

第一个参数为功能包名  之后的为依赖项  std_msgs  roscpp

一些常用功能包相关命令
rospack find [package_name]     #查找路径
rospack depends [package_name]  #查看依赖
rospack profile                 #查看新安裝的内容
rosls [package_name]            #查看包内
roscd [package_name]            #进入功能包


2、编译功能包
cd ~/catkin_ws
catkin_make

这时会编译工作空间内所有的功能包

如果编译单个功能包
catkin_make --pkg [package_name]


这时创建好了ros功能包(但此时只是相当于一个壳子，还没有实质内容)

3、创建节点
节点都是可执行的程序，通过编译保存在devel空间中。现在创建两个节点，一个发布数据，一个接受数据。
回到/catkin_ws/src/text2_tutorials/src 创建两个文件分别为example1_a.cpp和example1_b.cpp 
代码如下 （已含注释）



修改CMakelist.txt  (用以下替换)


4、编译节点
cd ~/catkin_ws
catkin_make 



5、运行测试
roscore  #打开节点管理器  
rosrun text2_tutorials chap2_example1_a  #启动节点A
rosrun text2_tutorials chap2_example1_b  #启动节点B




6、补充
为了防止找不到包，可以在 .bashrc 文件中加入
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/catkin_ws/src

在终端中输入以下内容
echo "export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/catkin_ws/src" >>  ~/.bashrc



同时，如果可以在.bashrc 修改或添加以下这句话（ip地址为ros节点管理器启动的设备，即可多机器通讯,节点便可运行在不同机器上）
export ROS_MASTER_URI=http://192.168.43.38:11311，
rosnode info /[node_name]    #节点信息
rosnode  ping /[node_name]  #节点通讯延时
rosnode kill /[node_name]     #关闭节点
rosnode list #查看运行节点
rostopic list #话题列表



7、创建msg和srv文件，自定义消息
在功能包下创建新文件msg/text2_msg1.msg,添加
int32 A
int32 B
int32 C

并在package.xml中加入
 <build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend> 

然后编辑CMakeList.txt
在find_package下添加message_generation
添加
 add_message_files(
   FILES
   text2_msg1.msg
 )

这时候使用命令 rosmsg show text2_tutorials/text2_msg1 可以看到

同理，创建srv/text2_srv1.srv
添加
int32 A
int32 B
int32 C
---
int32 sum

在CMakeList.txt 添加
catkin_package(
CATKIN_DEPENDS message_runtime
)

为了生成消息，需要在find_package中添加message_generation
并加入
add_service_files(
   FILES
   text2_srv1.srv
 )
这时候使用命令rossrv show text2_tutorials/text2_srv1  可以看到定义的内容


————————————————————————————————

其他内容参考链接

http://note.youdao.com/noteshare?id=266a1b966fc3e7fbe9dd43ae6bc5bc70


