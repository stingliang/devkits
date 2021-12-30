//
// Created by stingliang on 2021/9/22 16:06.
//
#include "receiver.h"

boost::thread_group Receiver::sm_thread_group;

void Receiver::threadReceive() {
    m_ios = std::make_unique<boost::asio::io_service>();
    m_acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
            *m_ios,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_listen_port));
    accept();
    m_ios->run();
}

void Receiver::accept() {
    boost::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(*m_ios));
    m_acceptor->async_accept(*sock,
                             boost::bind(&Receiver::accept_handler,
                                         this,
                                         boost::asio::placeholders::error,
                                         sock));
}

void Receiver::accept_handler(const boost::system::error_code &error,
                              boost::shared_ptr<boost::asio::ip::tcp::socket> sock) {
    if (!error) {
        RECEIVER_LOG(info) << "accept new connection";
        boost::mutex::scoped_lock ll(m_mutex);
        std::pair<SPSockMap::iterator, bool> rlt = m_socks.insert(std::make_pair(sock, new SPData));
        if (rlt.second) {
            boost::asio::async_read(
                    *sock,
                    boost::asio::buffer(rlt.first->second->m_readHeader._buf,
                                        sizeof(rlt.first->second->m_readHeader._buf)),
                    boost::asio::transfer_all(),
                    boost::bind(&Receiver::handle_read_header,
                                this,
                                boost::asio::placeholders::error,
                                sock,
                                boost::asio::placeholders::bytes_transferred)
                    );
        }
    } else {
        RECEIVER_LOG(error) << "Handshake failed, error: " << error.message().c_str();
    }
    accept();
}

void Receiver::handle_read_header(const boost::system::error_code &error,
                                  boost::shared_ptr<boost::asio::ip::tcp::socket> sock,
                                  std::size_t bytes_transferred) {
    SPSockMap::iterator it;
    {
        boost::mutex::scoped_lock ll(m_mutex);
        it = m_socks.find(sock);
        if (m_socks.end() == it) {
            return;
        }
    }

    if (!error) {
        it->second->m_readHeader._bodyLen = ntohl(it->second->m_readHeader._bodyLen);
        RECEIVER_LOG(trace) << "data says it's length is: " << it->second->m_readHeader._bodyLen;
        if(it->second->m_readHeader._magic != SP_MAGIC_NUMBER_POINTCLOUD ||
           it->second->m_readHeader._bodyLen > SP_MAX_BODY_LEN) {
            RECEIVER_LOG(warning) << "Read invalid msg header (magic: 0x" << std::hex
                                  << it->second->m_readHeader._magic
                                  << "(except: 0x" << SP_MAGIC_NUMBER_POINTCLOUD << ")"
                                  << std::oct << ", len: " << it->second->m_readHeader._bodyLen
                                  << "(except: less than " << SP_MAX_BODY_LEN << ")"
                                  << "), abort.";
            it->first->close();
            boost::mutex::scoped_lock ll(m_mutex);
            m_socks.erase(it);
            return;
        }
        boost::asio::async_read(
                *sock,
                boost::asio::buffer(it->second->m_readBody, it->second->m_readHeader._bodyLen),
                                    boost::asio::transfer_all(),
                                    boost::bind(&Receiver::handle_read_body,
                                                this,
                                                boost::asio::placeholders::error,
                                                sock,
                                                boost::asio::placeholders::bytes_transferred)
                                                );
    } else {
        RECEIVER_LOG(error) <<"Read header failed, error: " << error.message().c_str()
                            << ", readSize: " << (int)bytes_transferred;
        it->first->close();
        boost::mutex::scoped_lock ll(m_mutex);
        m_socks.erase(it);
    }
}

void
Receiver::handle_read_body(const boost::system::error_code &error, boost::shared_ptr<boost::asio::ip::tcp::socket> sock,
                           std::size_t bytes_transferred) {
    SPSockMap::iterator it;
    {
        boost::mutex::scoped_lock ll(m_mutex);
        it = m_socks.find(sock);
        if (m_socks.end() == it) {
            return;
        }
    }

    if (!error) {
        char* data = it->second->m_readBody->data();
        std::string lidarSN(data, LIDAR_SN_LENGTH);
        data += LIDAR_SN_LENGTH;
        uint32_t pointsNum = ntohl(*(uint32_t*)data);

        if(pointsNum > 0) {
            data += sizeof(uint32_t);
            auto* points = (LidarPoint*)data;
            m_lidarMutex.lock();
            RECEIVER_LOG(trace) << "Recv msg size: " << (int)bytes_transferred << ", sn: " << lidarSN.c_str();
        }
        m_lidarMutex.unlock();

        boost::asio::async_read(
                *sock,
                boost::asio::buffer(it->second->m_readHeader._buf, sizeof(it->second->m_readHeader._buf)),
                boost::asio::transfer_all(),
                boost::bind(&Receiver::handle_read_header,
                            this,
                            boost::asio::placeholders::error,
                            sock,
                            boost::asio::placeholders::bytes_transferred)
                );
    } else {
        RECEIVER_LOG(error) << "Read header failed, error: " << error.message().c_str()
                            << ", readSize: " << (int)bytes_transferred;
        it->first->close();
        boost::mutex::scoped_lock ll(m_mutex);
        m_socks.erase(it);
    }
}
