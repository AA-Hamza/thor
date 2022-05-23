#include "worker/connection_manager.hpp"
#include <iostream>

namespace http {
namespace server {

ConnectionManager::ConnectionManager()
{
}

void ConnectionManager::start(ConnectionPointer c)
{
      m_connections.insert(c);
      c->start();
}

void ConnectionManager::stop(ConnectionPointer c)
{
      c->stop();
      m_connections.erase(c);
}

void ConnectionManager::stop_all()
{
  for (auto &c: m_connections)
    c->stop();
  m_connections.clear();
}
} // namespace server
} // namespace http
