//
// Created by liang on 25-3-3.
//

#include "BaseCapture.h"

BaseCapture::BaseCapture(const std::string& rtsp_url) : rtsp_url_(rtsp_url), is_running_(false) {}

BaseCapture::~BaseCapture() {}

void BaseCapture::setFrameCallback(const std::function<void(cv::Mat)>& callback)
{
    frame_callback_ = callback;
}
