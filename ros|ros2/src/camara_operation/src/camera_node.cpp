#include "rclcpp/rclcpp.hpp"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>

class CameraNode : public rclcpp::Node {
public:
  // 构造函数,有一个参数为节点名称
  CameraNode(std::string name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
    camera_publisher_ = this->create_publisher<   >("camera", 10);
    cv::VideoCapture capture(0);
    if(!capture.isOpened()){
        ROS_ERROR("failed to open camera");
        ros::shutdown();
    }
    while (1) {
	 	cap.read(img);
		imshow("test", img);
		waitKey(1);
	}
  }

private:
	cv::Mat img;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ExampleInterfacesControl>("camera_node");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

