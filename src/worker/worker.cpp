#include <asio.hpp>
#include <csignal>
#include <iostream>
#include <thread>
#include <worker/worker.hpp>

namespace http
{
namespace server
{

Worker::Worker(void)
{
    worker_thread = new asio::thread([this]() {
        m_io_context_ptr = new asio::io_context(1);
        std::cout << "A Worker Started" << std::endl;
        auto work = asio::make_work_guard(*m_io_context_ptr);
        asio::signal_set m_signals(*m_io_context_ptr);
        m_signals.add(SIGINT);
        m_signals.add(SIGTERM);

#if defined(SIGQUIT)
        m_signals.add(SIGQUIT);
#endif
        m_io_context_ptr->run();
    });
}

std::shared_ptr<asio::ip::tcp::socket> Worker::new_socket_shared(void)
{
    return std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(*m_io_context_ptr));
}

void Worker::add_connection(std::shared_ptr<asio::ip::tcp::socket> socket_ptr, RequestHandler &req_handler)
{
    m_connection_manager.start(std::make_shared<Connection>(std::move(*socket_ptr), m_connection_manager, req_handler));
}

void Worker::stop_connections(void)
{
    m_connection_manager.stop_all();
}

asio::io_context &Worker::get_io_context(void)
{
    return *m_io_context_ptr;
}

} // namespace server
} // namespace http
