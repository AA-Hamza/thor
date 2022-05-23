#include <csignal>
#include <iostream>
#include <master/master.hpp>
#include <worker/worker.hpp>

namespace http
{
namespace server
{

Master::Master(const std::string &address, const std::string &port, const std::string &doc_root,
               const std::size_t num_of_workers)
    //: m_num_of_workers(num_of_workers), m_io_context(1),  m_signals(m_io_context), m_acceptor(m_io_context),
    : m_num_of_workers(num_of_workers), m_io_context(), m_signals(m_io_context), m_acceptor(m_io_context),
      m_request_handler(doc_root)
{
    // Registering program signals
    m_signals.add(SIGINT);
    m_signals.add(SIGINT);

#if defined(SIGQUIT)
    m_signals.add(SIGQUIT);
#endif
    await_stop();
    init_threads();

    asio::ip::tcp::resolver resolver(m_io_context);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();

    accept();
}

void Master::init_threads(void)
{
    /*
    m_workers = new Worker*;
    *m_workers = new Worker();
    */
    m_workers = new Worker *[m_num_of_workers];
    for (std::size_t i = 0; i < m_num_of_workers; ++i)
    {
        m_workers[i] = new Worker();
    }
}

void Master::run()
{
    // The io_context::run() call will block until all asynchronous operations
    // have finished. While the server is running, there is always at least one
    // asynchronous operation outstanding: the asynchronous accept call waiting
    // for new incoming connections.
    m_io_context.run();
}

void Master::await_stop()
{
    m_signals.async_wait([this](std::error_code /*ec*/, int /*signo*/) {
        // The server is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_context::run()
        // call will exit.
        m_acceptor.close();
        for (std::size_t i = 0; i < m_num_of_workers; ++i)
        {
            this->m_workers[i]->stop_connections();
        }
    });
}

void Master::accept()
{
    static int whos_turn = 0;
    // asio::ip::tcp::socket new_socket_ptr = m_workers[whos_turn]->get_new_socket();
    // asio::ip::tcp::socket *worker_new_socket_ptr = m_workers[whos_turn]->new_socket();
    auto worker_new_socket_ptr = m_workers[whos_turn]->new_socket_shared();
    m_acceptor.async_accept(*worker_new_socket_ptr, // Choosing worker io_context right away
                            [this, worker_new_socket_ptr](std::error_code ec) mutable {
                                // Check whether the server was stopped by a signal before this
                                // completion handler had a chance to run.
                                if (!m_acceptor.is_open())
                                {
                                    return;
                                }
                                // std::cout << "worker #" << whos_turn << " took a connection" << std::endl;

                                if (!ec)
                                {
                                    m_workers[whos_turn]->add_connection(worker_new_socket_ptr, m_request_handler);
                                    whos_turn++;
                                    whos_turn %= m_num_of_workers;
                                }

                                accept();
                            });
    // m_acceptor.async_accept(
    /*
m_acceptor.async_accept(m_workers[whos_turn]->get_io_context(), // Choosing worker io_context right away
                    [this](std::error_code ec, asio::ip::tcp::socket socket) {
                        // Check whether the server was stopped by a signal before this
                        // completion handler had a chance to run.
                        if (!m_acceptor.is_open())
                        {
                            return;
                        }
                        //std::cout << "worker #" << whos_turn << " took a connection" << std::endl;

                        if (!ec)
                        {
                            // m_workers[whos_turn].add_connection(std::make_shared<Connection>(std::move(socket)));
                            m_workers[whos_turn]->add_connection(socket, m_request_handler);
                            whos_turn++;
                            whos_turn %= m_num_of_workers;
                            // m_connection_manager.start(std::make_shared<Connection>(
                            // std::move(socket), m_connection_manager, m_request_handler));
                        }

                        accept();
                    });
                    */
}

} // namespace server
} // namespace http
