#pragma once

#include <asio.hpp>
#include "worker/connection.hpp"
#include "worker/connection_manager.hpp"

namespace http {
namespace server {

// The master thread that accepts all incoming requests
class Worker{
public:
    Worker(const Worker &) = delete;
    Worker& operator=(const Worker &) = delete;

    Worker();

    void add_connection(std::shared_ptr<asio::ip::tcp::socket> socket_ptr, RequestHandler &req_handler);
    void stop_connections(void);
    std::shared_ptr<asio::ip::tcp::socket> new_socket_shared(void);

    asio::io_context &get_io_context(void);

private:
    //std::thread *worker_thread;
    asio::thread *worker_thread;
    asio::io_context *m_io_context_ptr;
    ConnectionManager m_connection_manager;
    friend class Master;
};
}
}
