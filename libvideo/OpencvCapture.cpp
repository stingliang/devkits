#include "OpencvCapture.h"
#include "libdevcore/Exceptions.h"

void OpencvCapture::start()
{
    if (is_running_)
    {
        std::cout << "Capture is already running." << std::endl;
        return;
    }

    // 使用硬件加速解码
    // 请确保OpenCV编译时支持FFmpeg和硬件解码器（如CUDA）
    capture_.open(rtsp_url_, cv::CAP_FFMPEG);

    if (!capture_.isOpened())
    {
        BOOST_THROW_EXCEPTION(
            devkits::dev::CaptureError() << devkits::dev::err_str("Failed to open RTSP stream"));
    }

    // 启动视频流
    is_running_ = true;
    cv::Mat frame;

    while (is_running_)
    {
        capture_ >> frame;
        if (frame.empty())
        {
            std::cerr << "Error: Could not grab a frame." << std::endl;
            break;
        }

        // 调用回调函数
        if (frame_callback_)
        {
            frame_callback_(frame);
        }
    }

    stop();  // 停止捕获时释放资源
}

void OpencvCapture::stop()
{
    if (!is_running_)
    {
        std::cout << "Capture is not running." << std::endl;
        return;
    }

    is_running_ = false;

    // 释放VideoCapture资源
    capture_.release();
}
