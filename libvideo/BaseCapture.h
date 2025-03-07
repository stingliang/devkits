//
// Created by liang on 25-3-3.
//

#ifndef BASECAPTURE_H
#define BASECAPTURE_H

#include <functional>
#include <opencv2/opencv.hpp>
#include <string>

class BaseCapture
{
public:
    using Ptr = std::shared_ptr<BaseCapture>;
    BaseCapture(const std::string& rtsp_url);
    virtual ~BaseCapture();

    // 启动视频流
    virtual void start() = 0;

    // 停止视频流
    virtual void stop() = 0;

    // 注册回调函数
    void setFrameCallback(const std::function<void(cv::Mat)>& callback);

protected:
    std::string rtsp_url_;
    bool is_running_;
    std::function<void(cv::Mat)> frame_callback_;
};


#endif  // BASECAPTURE_H
