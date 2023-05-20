#pragma once
#include <ltlib/io/types.h>
#include <ltlib/io/ioloop.h>
#include <cstdint>
#include <string>
#include <google/protobuf/message_lite.h>

namespace ltlib
{

class ServerImpl;

//��֧��TLS
class Server
{
public:
	struct Params
	{
		StreamType stype;
		IOLoop* ioloop;
		std::string pipe_name;
		std::string bind_ip;
		uint16_t bind_port;
		std::function<void(uint32_t)> on_accepted;
		std::function<void(uint32_t)> on_closed;
		std::function<void(uint32_t/*fd*/, uint32_t/*type*/, const std::shared_ptr<google::protobuf::MessageLite>&)> on_message;
	};

public:
	static std::unique_ptr<Server> create(const Params& params);
	bool send(uint32_t fd, uint32_t type, const std::shared_ptr<google::protobuf::MessageLite>& msg, const std::function<void()>& callback = nullptr);
	// ���ϲ����send()����falseʱ�����ϲ����close()�ر����fd����ʱon_closed�����ص�
	void close(uint32_t fd);

private:
	std::shared_ptr<ServerImpl> impl_;
};

} // namespace ltlib