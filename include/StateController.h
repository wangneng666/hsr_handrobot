#ifndef HANDRB_UI_STATECONTROLLER_H
#define HANDRB_UI_STATECONTROLLER_H

#include <iostream>
#include "ros/ros.h"
#include "RbQthread.h"
#include "MainWindow.h"
#include <QMutex>

//消息类型头文件
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int16.h"
#include "rb_msgAndSrv/rb_DoubleBool.h"
#include "rb_msgAndSrv/rb_string.h"
//#include "rb_msgAndSrv/rb_EmptyAndArray.h"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include "hsr_rosi_device/ClearFaultSrv.h"
#include "hsr_rosi_device/SetEnableSrv.h"
#include "industrial_msgs/RobotStatus.h"
#include "geometry_msgs/Wrench.h"
#include "hsr_rosi_device/setModeSrv.h"
#include "hirop_msgs/robotError.h"
#include "hirop_msgs/connectGripper.h"
using namespace std;

//业务逻辑控制
class StateController {
public:
    StateController();
    ~StateController();

public:
    int mode=0;                     //模式
    int voiceStep=0;                //追踪步序
    controllerState* ctlState;      //状态集合容器
    rosTopicHandle* rosTopicHd;     //ros话题复位数据容器
    bool isStart= false;            //开始运行按钮标志
    bool isStop= false;             //停止按钮标志
    bool assist_funcRunOnce= false; //辅助_运行一次函数
    ros::NodeHandle* Node;          //ros节点
    QMutex mutex_updateCtlState;    //数据更新加锁
    //测试
    QLabel* lable_showinfo;
    QPlainTextEdit* plainTextEdit;
    //线程指针
    vector<rbQthread*> rbQthreadList;     //线程容器集合
    rbQthread* rbQthread_voiceCtl_AutoRun;//声控自动模式主线程
    rbQthread* rbQthread_voiceCtl_modeTask_N1;//声控模式-1任务
    rbQthread* rbQthread_voiceCtl_modeTask_1;//声控模式1任务
    rbQthread* rbQthread_voiceCtl_modeTask_3;//声控模式3任务
    rbQthread* rbQthread_voiceCtl_modeTask_4;//声控模式4任务
    rbQthread* rbQthread_voiceCtl_modeTask_5;//声控模式5任务
    rbQthread* rbQthread_rbGoShakeHandPose;//机器人去到等待点
    rbQthread* rbQthread_spin;//状态监控线程
public:
    /***
     * 获取服务和话题
     * @param _rosTopicHd 服务和话题集合
     */
    void ShareTopicHandle(rosTopicHandle* _rosTopicHd);

    /***
     * 更新状态数据接口
     * @param _ctlState 状态集合
     */
    void updateState(controllerState* _ctlState);

    /***
     * 控制模块开始启动
     */
    void start();

    /***
     * 声音控制自动运行
     */
    void voiceCtl_AutoRun();

    /***
     * 变量初始化
     */
    void initVal();

    /***
     * 模式为-1执行功能函数
     */
    void ContrlMode_N1_task();

    /***
     * 线程任务(模式-1~5)函数
     */
    void thread_voiceCtl_modeTask_N1();
    void thread_voiceCtl_modeTask_1();
    void thread_voiceCtl_modeTask_3();
    void thread_voiceCtl_modeTask_4();
    void thread_voiceCtl_modeTask_5();

    /***
     * 去到机器人握手等待点
     */
    void thread_rbGoShakeHandPose();
    /***
     * 线程循环--显示当前系统状态步数
     */
    void thread_rbQthread_spin();
    /***
     *
     * @param flag 行人检测开关 ,true开发脚本,false关闭脚本
     */
    void PersonDetect_Switch(bool flag);
    /***
     *
     * @param flag 语音检测开关,true开发脚本,false关闭脚本
     */
    void VoiceDetect_Switch(bool flag);


};


#endif //HANDRB_UI_STATECONTROLLER_H
