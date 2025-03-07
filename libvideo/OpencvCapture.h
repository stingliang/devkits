#ifndef OPENCVCAPTURE_H
#define OPENCVCAPTURE_H

#include "BaseCapture.h"

class OpencvCapture : public BaseCapture
{
public:
    OpencvCapture(const std::string& rtsp_url) : BaseCapture(rtsp_url) {}
    ~OpencvCapture() override = default;

    // 启动视频流
    void start() override;

    // 停止视频流
    void stop() override;

private:
    cv::VideoCapture capture_;
};

#endif  // OPENCVCAPTURE_H
