#pragma once

#include <string>

namespace thor
{
namespace http
{
namespace mime_types
{

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string &extension);

} // namespace mime_types
} // namespace http
} // namespace thor
