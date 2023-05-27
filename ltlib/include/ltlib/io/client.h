#pragma once
#include <ltlib/ltlib.h>
#include <ltlib/io/types.h>
#include <memory>
#include <string>
#include <functional>
#include <google/protobuf/message_lite.h>

namespace ltlib
{

class ClientImpl;
class IOLoop;

class LT_API Client
{
public:
    struct Params
    {
        StreamType stype;
        IOLoop* ioloop;
        std::string pipe_name;
        std::string host;
        uint16_t port;
        bool is_tls;
        std::string cert;
        std::function<void()> on_connected;
        std::function<void()> on_closed;
        std::function<void()> on_reconnecting;
        std::function<void(uint32_t type, const std::shared_ptr<google::protobuf::MessageLite>&)> on_message;
    };
public:
    static std::unique_ptr<Client> create(const Params& params);
    bool send(uint32_t type, const std::shared_ptr<google::protobuf::MessageLite>& msg, const std::function<void()>& callback = nullptr);
    // ����������
    // 1. ��һ�����ڲ����������Է�����
    // 2. �ڶ������ϲ����bool send()���Ƿ���false���������ϲ�������reconnect()
    // ������������������ص�on_reconnecting
    void reconnect();

private:
    std::shared_ptr<ClientImpl> impl_;
};

} // namespace ltlib