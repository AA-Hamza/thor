#pragma once

#include "http/request_parser.hpp"
#include "request_handler.hpp"
#include <asio.hpp>

namespace thor
{
using http::Request;
using http::RequestParser;
namespace server
{
#define BUFFER_SIZE 4096 * 4

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>
{

  public:
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    explicit Connection(asio::ip::tcp::socket socket, ConnectionManager &manager, RequestHandler &handler);

    void start(void);
    void stop(void);

    ~Connection();

  private:
    void read();
    void write();

    //std::shared_ptr<asio::ip::tcp::socket> m_socket;
    asio::ip::tcp::socket m_socket;
    // std::shared_ptr<asio::ip::tcp::socket *>m_socket;
    ConnectionManager &m_connection_manager;
    RequestHandler &m_request_handler;
    std::array<char, BUFFER_SIZE> m_buffer;

    Request m_request;

    RequestParser m_request_parser;

    Reply m_reply;
};

typedef std::shared_ptr<Connection> ConnectionPointer;

} // namespace server
} // namespace thor
