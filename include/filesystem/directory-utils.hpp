#pragma once

#include <string>
#include <vector>

namespace Filesystem 
{
  auto GetFilePaths(const char* directory_path) noexcept -> std::vector<std::string>;
}

