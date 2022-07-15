#include "worker/connection_manager.hpp"
#include <iostream>

namespace thor
{
namespace server
{

ConnectionManager::ConnectionManager()
{
}

void ConnectionManager::start(ConnectionPointer c)
{
    c->start();
    std::lock_guard<std::mutex> m_lock(m_connection_manager_lock);
    m_connections.insert(c);
}

void ConnectionManager::stop(ConnectionPointer c)
{
    c->stop();
    std::lock_guard<std::mutex> m_lock(m_connection_manager_lock);
    m_connections.erase(c);
}

void ConnectionManager::stop_all()
{
    for (auto &c : m_connections)
        c->stop();
    std::lock_guard<std::mutex> m_lock(m_connection_manager_lock);
    m_connections.clear();
}
} // namespace server
} // namespace thor
