#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "simple_udp.h"

simple_udp udp0("0.0.0.0",4001);

int main(int argc, char **argv){
  udp0.udp_bind();
  int n = 0;
  while (1){
    #define BUFFER_MAX 65000
    char buffer[BUFFER_MAX];
    udp0.udp_recv(buffer, BUFFER_MAX);
    std::vector<unsigned char> data(buffer, buffer + BUFFER_MAX);

    std::string image_name;
    image_name = std::string("recv_images/dimage") + std::to_string(n) + std::string(".jpg");

    cv::Mat dst = cv::imdecode(cv::Mat(data), cv::IMREAD_GRAYSCALE);
    cv::imwrite(image_name, dst);
    std::cout << "saved: " + image_name << std::endl;
    n += 1;
  }
  return 0;
}
