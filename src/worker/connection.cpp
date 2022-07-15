#include "worker/connection.hpp"
#include "worker/connection_manager.hpp"
#include "worker/request_handler.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace thor
{
namespace server
{

Connection::Connection(asio::ip::tcp::socket socket, ConnectionManager &manager, RequestHandler &handler)
    : m_socket(std::move(socket)), m_connection_manager(manager), m_request_handler(handler)
{
}

Connection::~Connection()
{
    stop();
}

void Connection::start()
{
    read();
}

void Connection::stop()
{
    m_socket.close();
}

void Connection::read()
{
    auto self(shared_from_this());
    m_socket.async_read_some(
        asio::buffer(m_buffer), [this, self](std::error_code ec, std::size_t bytes_transferred) {
            if (!ec)
            {
                RequestParser::result_type result;
                std::tie(result, std::ignore) =
                    m_request_parser.parse(m_request, m_buffer.data(), m_buffer.data() + bytes_transferred);

                if (result == RequestParser::good)
                {
                    m_request_handler.handle_request(m_request, m_reply);
                    write();
                }
                else if (result == RequestParser::bad)
                {
                    m_reply = Reply::stock_reply(Reply::bad_request);
                    write();
                }
                else
                {
                    read();
                }
            }
            else if (ec != asio::error::operation_aborted)
            {
                m_connection_manager.stop(shared_from_this());
            }
        });
}

void Connection::write()
{
    auto self(shared_from_this());
    asio::async_write(m_socket, m_reply.to_buffers(), [this, self](std::error_code ec, std::size_t) {
        if (!ec)
        {
            // Initiate graceful Connection closure.
            asio::error_code ignored_ec;
            m_socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }

        if (ec != asio::error::operation_aborted)
        {
            m_connection_manager.stop(shared_from_this());
        }
    });
}

} // namespace server
} // namespace thor
