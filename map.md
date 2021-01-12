# DropNGo平台回放数据，录制bag包

## 安装与配置DropNGo

### 安装
DropNGo版本：
<br>
- MVP分支：repo init -u ssh://shaitgrt01:29418/zros/manifest -b B_DropnGo -m feature/mvp/dev.xml --repo-url=ssh://shaitgrt01:29418/zros/repo --no-repo-verify
<br>
- 代码编译说明：http://zmwiki.zongmutech.com/index.php/ZROS%E4%BB%A3%E7%A0%81%E7%BC%96%E8%AF%91%E5%92%8C%E8%BF%90%E8%A1%8C


### 配置
修改代码`[DropNGo]/projects/node/avp_nodes/avp_engine/avp_event_hub.cpp`，并重新编译`./mx86`：
```
AVPEventHub():
kTopicTfMapBaselink
->
kTopicTfMapBaselinkEKF

BtoMSubscriber(): [zros::std_msgs::TfToRosOdom(tf, baseToMapOdometry)之后增加]
if (baseToMapOdometry.header.frame_id == "map") {
    std::cout << "ekf state" << std::endl;
    is_locationed_ = true;
} else if (baseToMapOdometry.header.frame_id == "odom") {
    std::cout << "dr state" << std::endl;
}
```

修改代码`[DropNGo]/projects/node/remote_ros/slot_detection_net_server.cpp`和`[DropNGo]/projects/zros_dbg/src/zros_dbg/src/slot_detection_net_client.cpp`，并重新编译`./mx86`：
```
#define USE_JPEG 0
```

编辑`[DropNGo]/out/B_DropnGo_feature_mvp_dev/ubuntu1604_x86_64/res/launcher/launcher_all.xml`文件：
```
MockHost: enable 1
cube_vslam: enable 0
```

编辑`~/.bashrc`文件：
```
export ZROS_CONSOLE_LOG_LEVEL=1
export VIDEO_PLAYBACK_SPEED=10 (试配置情况浮动)
```

## 开始录制

### 修改capture路径
修改`[DropNGo]/out/B_DropnGo_feature_mvp_dev/ubuntu1604_x86_64/res/playback/gstreamer_library.xml`文件：
- 替换`<path>[capture_path]</path>`内`[capture_path]`


### 打开3个Terminal（按顺序）
- [Terminal 1]：zros_dbg，负责接收DropNGo信息
```
cd [DropNGo]/projects/zros_dbg
catkin_make
source devel/setup.bash
roslaunch zros_dbg feature_radar_mapping.launch
```

- [Terminal 2]：接收zros_dbg转发的ros信息
```
cd [bag_folder]
rosbag record -a
```

- [Terminal 3]：DropNGo：回放数据，发布信息给zros_dbg
```
cd [DropNGo]/out/B_DropnGo_feature_mvp_dev/ubuntu1604_x86_64/bin
./launcher
```

### 切换地图并手动输入车辆初始位置，开始录制
- 通过地图切换命令或UI切换地图，确保`DropNGo`界面和`rviz`中地图一致（切图不成功时可切转其他地图再切回来）
- 在`rviz`界面中，使用`2D Pose Estimate`在地图上标出初始位置和朝向，等待几秒后，会在选定点周围出现实时语义分割结果，且`DropNGo`界面中小车位置会设置到手动标定位置，如手动设置不成功，可再次重置
- 待小车运行后，通过`DropNGo`界面和`rviz`观察定位效果，尤其是拐弯处，成功运行则可令程序自行运行
- 视频回放完毕后（`DropNGo`界面静止或变黑），关闭所有窗口，拷贝bag包

### 常用命令
#### 地图切换
*目前DropNGo的UI待优化，之后可以直接切换
```
cd [DropNGo]/out/B_DropnGo_feature_mvp_dev/ubuntu1604_x86_64/bin
./AVPAPITest
查询命令
> ?
查询地图ID
> GetGarageInfoAll
切换地图
> LoadMapID 3334 (地图ID)
```


# 根据EKF 2D轨迹，生成FeatureMap & MRadarMap使用说明

## 1. 配置视频文件、轨迹信息

编辑`[Release]/config_async/video_process.yaml`文件：

- dir:                     视频文件路径
- bag_file:                包含EKF轨迹的bag包
- Tdc:                     车辆后视相机相对于里程计的外参
- ***以下通常无需改动***
- fisheye_distortion_file: 畸变表路径
- generate_trajectory:     1
- use_2d_recover:          1
- ekf_topic:               EKF轨迹对应的topic名称
- save_file:               将bag包里的EKF轨迹信息导出到文件

## 2. 配置FeatureMap建图程序

编辑`[Release]/config_async/feature_map.yaml`文件：

- Tdc:              车辆后视相机相对于里程计的外参，与1中的Tdc要保持一致
- Mask.Name:        对应相机、抬高角度的掩模
- Tdc:              车辆后视相机相对于里程计的外参
- ***以下通常无需改动***
- Map.Name:         生成的特征点地图保存路径
- Distortion.Table: 畸变表路径
- isLoadMap:        0
- ThetaX:           鱼眼展开时需要抬高的角度
- Use2DRecover:     1
- Vocabulary.Name:  词袋名称，使用ORBvoc.txt.bin

## 3. 配置MRadarMap建图程序

编辑`[Release]/config_async/multi_map_config.yaml`文件：
- bag_file: 			   包含毫米波信息的bag包
- map_name:                毫米波地图名称
- ***以下通常无需改动***
- trajectory_file:         特征点地图中关键帧的轨迹文件，与2中的Map.Path相对应
- mradar_pointcloud_topic: 毫米波的topic名称
- map_path:                毫米波地图保存路径

## 4. 建图流程

1. 先根据2D轨迹，生成FeatureMap
```
[3个Terminal]
./1-1.sh
./1-2.sh
./1-3.sh
```

1. 等FeatureMap建图完毕，生成关键帧对应的轨迹文件之后，进行毫米波地图创建
```
[2个Terminal]
./2-1.sh
./2-2.sh
```
