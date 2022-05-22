#include <worker/worker.hpp>
#include <csignal>
#include <thread>
#include <asio.hpp>
#include <iostream>


namespace http {
namespace server {

Worker::Worker(void)
    //: //m_io_context(1)
{
    worker_thread = new asio::thread([this]() {
                m_io_context_ptr = new asio::io_context(1);
                std::cout << "A Worker Started" << std::endl;
                auto work = asio::make_work_guard(*m_io_context_ptr);
                asio::signal_set m_signals(*m_io_context_ptr);
                m_signals.add(SIGINT);
                //m_signals.add(SIGINT);

#if defined(SIGQUIT)
                m_signals.add(SIGQUIT);
#endif
                m_io_context_ptr->run();
            }
            );
}

void Worker::add_connection(asio::ip::tcp::socket &socket_ref, RequestHandler &req_handler)
{
    m_connection_manager.start(std::make_shared<Connection>( std::move(socket_ref), m_connection_manager, req_handler));
}

void Worker::stop_connections(void)
{
    m_connection_manager.stop_all();
}

asio::io_context &Worker::get_io_context(void)
{
    return *m_io_context_ptr;
}

}
}