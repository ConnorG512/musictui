#include "read-directory.hpp"

#include <cassert>
#include <stdexcept>
#include <ranges>
#include <cstring>

auto Directory::OpenDirectory(const char* music_directory_path) const 
  -> std::unique_ptr<DIR, decltype(&closedir)>
{
  DIR *found_directory {opendir(music_directory_path)};
  if (found_directory == nullptr)
    throw std::runtime_error("Failed to open directory!");

  return std::unique_ptr<DIR, decltype(&closedir)>{found_directory, &closedir};
}

auto Directory::GetDirectoryContents() -> std::vector<std::string>
{
  std::vector<std::string> file_names{};
  file_names.reserve(5);
  
  while (struct dirent *result = readdir(music_directory_.get())) 
  {
    // first two entries (0 & 1) are . and ..
    if(result->d_type != DT_REG)
      continue;
    file_names.emplace_back(result->d_name);
  }

  return file_names;
}
