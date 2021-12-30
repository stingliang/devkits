//
// Created by stingliang on 2021/9/22 16:06.
//
#ifndef LIDAR_DATA_TRANSPOND_RECEIVER_H
#define LIDAR_DATA_TRANSPOND_RECEIVER_H

#include "libnetwork/common.h"
#include "libnetwork/processor.h"
#include "libdevcore/Log.h"

#define RECEIVER_LOG(SEVERITY) LOGGER("Receiver", SEVERITY)

class LidarData
{
public:
    uint32_t m_lidarType;/* 雷达类型 */
    char m_lidarSN[LIDAR_SN_LENGTH];          /* 雷达SN */
    uint64_t m_timestamp;          /* TIDS系统时间戳 */
    uint64_t m_lidarTimestamp;          /* 雷达时间戳 */
    uint32_t m_pointsNum;          /* 点个数 */
    float m_lastTemperature;
    LidarPoint *m_pPoints;          /* 雷达点云 */
    LidarData();
    virtual ~LidarData();
};

typedef struct {
    uint64_t m_timestamp;          /* TIDS系统时间戳 */
    uint64_t m_lidarTimestamp;          /* 雷达时间戳 */
    float gyro_x;        /**< Gyroscope X axis, Unit:rad/s */
    float gyro_y;        /**< Gyroscope Y axis, Unit:rad/s */
    float gyro_z;        /**< Gyroscope Z axis, Unit:rad/s */
    float acc_x;         /**< Accelerometer X axis, Unit:g */
    float acc_y;         /**< Accelerometer Y axis, Unit:g */
    float acc_z;         /**< Accelerometer Z axis, Unit:g */
}ImuFrame;

typedef struct {
    uint32_t m_frameNum;          /* imu帧数 */
    ImuFrame m_frames[IMU_NUM_MAX];          /* imu帧数组 */
}ImuData;

union MsgHeader {
    char _buf[8];
    struct {
        uint32_t _magic;
        uint32_t _bodyLen;
    };
};

struct SPData {
    MsgHeader m_readHeader;
    std::array<char, SP_MAX_BODY_LEN>* m_readBody;
    SPData(): m_readBody(new std::array<char, SP_MAX_BODY_LEN>) {}
    ~SPData() { delete m_readBody; }
};

class Receiver {
public:
    explicit Receiver(int port):m_listen_port(port) { sm_thread_group.create_thread([this](){threadReceive();}); }
    typedef boost::unordered_map<boost::shared_ptr<boost::asio::ip::tcp::socket>, SPData*> SPSockMap;
    void threadReceive();
    void accept();
    void accept_handler(const boost::system::error_code& error, boost::shared_ptr<boost::asio::ip::tcp::socket> sock);
    void handle_read_header(const boost::system::error_code& error,
                            boost::shared_ptr<boost::asio::ip::tcp::socket> sock,
                            std::size_t bytes_transferred);
    void handle_read_body(const boost::system::error_code& error,
                          boost::shared_ptr<boost::asio::ip::tcp::socket> sock,
                          std::size_t bytes_transferred);
private:
    static boost::thread_group sm_thread_group;
    std::unique_ptr<boost::asio::io_service> m_ios = nullptr;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor = nullptr;
    SPSockMap m_socks;
    boost::mutex m_mutex;
    int m_listen_port;

    boost::mutex m_lidarMutex;
};

#endif //LIDAR_DATA_TRANSPOND_RECEIVER_H