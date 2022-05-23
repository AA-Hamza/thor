#pragma once

#include "connection.hpp"
#include <forward_list>
#include <set>
#include <unordered_set>

namespace http
{
namespace server
{

class ConnectionManager
{
  public:
    ConnectionManager(const ConnectionManager &) = delete;
    ConnectionManager &operator=(const ConnectionManager &) = delete;

    ConnectionManager(void);
    void start(ConnectionPointer c_ptr);
    void stop(ConnectionPointer c_ptr);

    void stop_all();

  private:
    // std::set<ConnectionPointer> m_connections;
    std::unordered_set<ConnectionPointer> m_connections;
    // std::forward_list<ConnectionPointer> m_connections;
};

} // namespace server
} // namespace http
