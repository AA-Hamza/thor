#pragma once

#include "header.hpp"
#include <string>
#include <vector>

namespace thor
{
namespace http
{

/// A request received from a client.
struct Request
{
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
};

} // namespace http
} // namespace thor
