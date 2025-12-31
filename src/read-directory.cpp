#include "read-directory.hpp"

#include <cassert>
#include <stdexcept>

auto Directory::OpenDirectory(const char* music_directory) const 
  -> std::unique_ptr<DIR, decltype(&closedir)>
{
  DIR *found_directory {opendir(music_directory)};
  if (found_directory == nullptr)
    throw std::runtime_error("Failed to open directory!");

  return std::unique_ptr<DIR, decltype(&closedir)>{found_directory, &closedir};
}

auto Directory::GetDirectoryContents() -> std::span<dirent>
{
  return {
    readdir(music_directory_.get()),
    1
  };
}
