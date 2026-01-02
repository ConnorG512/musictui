#include "filesystem/directory-utils.hpp"

#include <cassert>
#include <memory>
#include <dirent.h>
#include <span>

namespace 
{
  auto getEntries(const char* directory_path) noexcept -> 
    std::unique_ptr<DIR, decltype(&closedir)> 
  {
    DIR *found_directory {opendir(directory_path)};
   
    return std::unique_ptr<DIR, decltype(&closedir)>{found_directory, &closedir};
  }
}

auto Filesystem::GetFilePaths(const char* directory_path) noexcept -> std::vector<std::string>
{
  assert(directory_path != nullptr);
  
  auto dir_entry = getEntries(directory_path);
  std::vector<std::string> full_file_path{};
  full_file_path.reserve(5);

  while(struct dirent *result = readdir(dir_entry.get()))
  {
    if(result->d_type != DT_REG)
      continue;

    const auto full_path {std::format("{}{}", directory_path, result->d_name)};
    full_file_path.emplace_back(full_path);
  }

  return full_file_path;
}
